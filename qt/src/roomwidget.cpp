#include <QTimer>
#include "roomwidget.h"
#include "localsettings.h"
#include "commons.h"

bool isNfcActive = false;

RoomWidget::RoomWidget(QString &roomName, QWidget *parent)
    : QWidget{parent}, roomName(roomName)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);
    mainLayout->setAlignment(Qt::AlignBottom);

    this->setLayout(mainLayout);

//    datasLabel = new QLabel("");
//    datasLabel->setAlignment(Qt::AlignCenter);
//    datasLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    mainLayout->addWidget(datasLabel);

    statusLabel = new QLabel("No device connected");
    statusLabel->setAlignment(Qt::AlignHCenter);
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

void RoomWidget::attachModuleSlot()
{
#ifdef __arm__
    if(!isNfcActive)
    {
        isNfcActive = true;
        NfcThread *worker = new NfcThread;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &RoomWidget::nfcRead, worker, &NfcThread::doWork);
        connect(worker, &NfcThread::resultReady, this, &RoomWidget::createBluetoohDevice);
        connect(worker, &NfcThread::updateStatus, this, &RoomWidget::updateBluetoothStatus);

        qDebug() << "Starting NFC Reader";
        workerThread.start();

        emit nfcRead();
    }
    else
    {
        qInfo() << "NFC Deamon already in use";
    }
#else
    createBluetoohDevice();
#endif
}

void RoomWidget::createBluetoohDevice(const QString macAddress, const QString type)
{
    isNfcActive = false;

    deviceMac = macAddress;

    if(deviceMac.isEmpty() || deviceName.isEmpty())
    {
        deviceMac = QInputDialog::getText(this, tr("Get Bluetooth MAC"),
                                          tr("Module MAC :"), QLineEdit::Normal,
                                          nullptr, nullptr);

        deviceName = QInputDialog::getText(this, tr("Get Bluetooth name"),
                                           tr("Module name :"), QLineEdit::Normal,
                                           nullptr, nullptr);

#ifdef QT_DEBUG
        if(deviceMac.isEmpty() && deviceName.isEmpty())
        {
            qWarning() << "Device mac and name invalid. Using debug values";
            deviceMac = "DE:EF:58:97:1A:75";
            deviceName = "BlueNRG";
        }
#else
        qWarning() << "Device mac or name invalid.";
        return;
#endif
    }
    else if(deviceName.isEmpty())
    {
        deviceName = "BlueNRG";
    }

    qDebug() << deviceMac << deviceName;
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
        connect(device, &BluetoohDevice::deviceConnectedSignal, this, &RoomWidget::moduleAttachedSlot);
        connect(device, &BluetoohDevice::deviceDisconnectedSignal, this, &RoomWidget::detachModuleSlot);

        if(type == "QDV000" || type.isEmpty())
        {
            if(centralWidget != nullptr)
            {
                delete centralWidget;
            }
            centralWidget = new QdvWidget();
//            centralWidget = new PlantWidget();
            centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            mainLayout->insertWidget(0, centralWidget);
            connect(device, &BluetoohDevice::updateDatas, this, &RoomWidget::updateDatasQdv);
        }

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

void RoomWidget::updateDatasQdv(int temp, int press)
{
    qobject_cast<QdvWidget*>(centralWidget)->setTemp(temp/10);
    qobject_cast<QdvWidget*>(centralWidget)->setPressure(press/100);
}

void RoomWidget::updateBluetoothStatus(QString status)
{
    statusLabel->setText(status);
}


