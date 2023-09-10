#include "roomwidget.h"
#include "localsettings.h"
#include "MFRC522.h"
#include <unistd.h>
#include <QCoreApplication>
//#include "commons.h"

RoomWidget::RoomWidget(QString &roomName, QWidget *parent)
    : QWidget{parent}, roomName(roomName)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);

    this->setLayout(mainLayout);

    datasLabel = new QLabel("");
    datasLabel->setAlignment(Qt::AlignCenter);
    datasLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(datasLabel);

    statusLabel = new QLabel("No device connected");
    statusLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    mainLayout->addWidget(statusLabel);

    attachDeviceButton = new QPushButton("Attach module", this);

    detachDeviceButton = new QPushButton("Detach module", this);
    detachDeviceButton->setVisible(false);

    connect(attachDeviceButton, &QPushButton::clicked, this, &RoomWidget::attachModuleSlot);

    controlsLayout = new QVBoxLayout();

    controlsLayout->addWidget(attachDeviceButton);

    mainLayout->addLayout(controlsLayout);
}

QString RoomWidget::getRoomName() const
{
    return roomName;
}

void RoomWidget::setRoomName(QString &newRoomName)
{
    roomName = newRoomName;
}

void RoomWidget::resetNFCReading()
{
    isNFCReading = false;
}

void RoomWidget::requestNFCTag()
{
#ifdef __arm__
    MFRC522 *nfc_handler = new MFRC522(new CommSPI());
    nfc_handler->PCD_Init();
    nfc_handler->PCD_DumpVersionToSerial();
#endif

    QTimer::singleShot(30000, this, &RoomWidget::resetNFCReading);

    datasLabel->setText("NFC Quick Pairing :\napproach module tag...");

#ifdef __arm__
    isNFCReading = true;
    while(isNFCReading)
    {
        MFRC522::StatusCode status;
        byte byteCount;
        byte buffer[18];

        usleep(1000);

        // Look for new cards
        if (!nfc_handler->PICC_IsNewCardPresent())
        {
            continue;
        }

        // Select one of the cards
        if (!nfc_handler->PICC_ReadCardSerial())
        {
            continue;
        }

        nfc_handler->PICC_DumpDetailsToSerial(&(nfc_handler->uid));

        if (nfc_handler->uid.sak == nfc_handler->PICC_TYPE_MIFARE_UL)
        {
            for(byte page = 0; page < 16; page += 4)
            {
                status = nfc_handler->MIFARE_Read(page, buffer, &byteCount);
                qInfo() << nfc_handler->GetStatusCodeName(status);
            }

            isNFCReading = false;
            break;
        }

        QCoreApplication::processEvents();
    }
#endif
}

void RoomWidget::attachModuleSlot()
{   
    requestNFCTag();

    datasLabel->clear();

    if(deviceMac.isEmpty() || deviceName.isEmpty())
    {
        deviceMac = QInputDialog::getText(this, tr("Get Bluetooth MAC"),
                                             tr("Module MAC :"), QLineEdit::Normal,
                                             nullptr, nullptr);

        deviceName = QInputDialog::getText(this, tr("Get Bluetooth name"),
                                                   tr("Module name :"), QLineEdit::Normal,
                                                   nullptr, nullptr);

#ifdef QT_DEBUG
        qWarning() << "Device mac or name invalid. Using debug values";
        deviceMac = "DE:EF:58:97:1A:75";
        deviceName = "BlueNRG";
#else
        qWarning() << "Device mac or name invalid.";
        return;
#endif
    }

    serviceUuid = "00000000-0001-11e1-9ab4-0002a5d5c51b";
    characteristicUuid = "00140000-0001-11e1-ac36-0002a5d5c51b";

    if(serviceUuid.isEmpty() || characteristicUuid.isEmpty())
    {
        qWarning() << "Service UUID or Characteristic UUID empty";
        return;
    }

//F9:03:31:DC:D1:DE

    device = new BluetoohDevice(deviceName, deviceMac, serviceUuid, characteristicUuid);

    if(device)
    {
        connect(device, &BluetoohDevice::changeStatus, this, &RoomWidget::updateBluetoothStatus);
        connect(detachDeviceButton, &QPushButton::clicked, device, &BluetoohDevice::disconnectFromDevice);
        connect(device, &BluetoohDevice::updateDatas, this, &RoomWidget::updateDatas);
        connect(device, &BluetoohDevice::deviceConnectedSignal, this, &RoomWidget::moduleAttachedSlot);
        connect(device, &BluetoohDevice::deviceDisconnectedSignal, this, &RoomWidget::detachModuleSlot);

        device->startDeviceDiscovery();
    }
    else
    {
        QString temp = QString("Error in device creation : device empty.");
        qWarning() << temp;
        statusLabel->setText(temp);
    }
}

void RoomWidget::moduleAttachedSlot()
{
    attachDeviceButton->setVisible(false);

    controlsLayout->removeWidget(attachDeviceButton);
    controlsLayout->insertWidget(0, detachDeviceButton);
    detachDeviceButton->setVisible(true);

    saveDeviceConfiguration();
}

void RoomWidget::detachModuleSlot()
{
    detachDeviceButton->setVisible(false);

    controlsLayout->removeWidget(detachDeviceButton);
    controlsLayout->insertWidget(0, attachDeviceButton);
    attachDeviceButton->setVisible(true);

    deviceMac.clear();
    deviceName.clear();
    delete device;
}

void RoomWidget::saveDeviceConfiguration()
{
    qDebug() << "Writting devices settings...";
    QSettings settings;

    settings.beginGroup(roomName);
        settings.beginGroup(SETTINGS_DEVICES_GROUP);
            settings.beginGroup(deviceMac);
            settings.setValue("name", deviceName);
            settings.setValue("service", serviceUuid);
            settings.setValue("characteristic", characteristicUuid);
            settings.endGroup();
        settings.endGroup();
            settings.endGroup();
}

void RoomWidget::updateDatas(QString datas)
{
    datasLabel->setText(datas);
}

void RoomWidget::updateBluetoothStatus(QString &status)
{
    statusLabel->setText(status);
}

void RoomWidget::resetAll()
{
    deviceMac.clear();
    deviceName.clear();
    serviceUuid.clear();
    characteristicUuid.clear();
    delete device;
}


