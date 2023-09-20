#include <QTimer>
#include "roomwidget.h"
#include "localsettings.h"
#include "commons.h"
#include <QBluetoothLocalDevice>

bool isNfcActive = false;

RoomWidget::RoomWidget(QString &roomName, unsigned char position, QWidget *parent)
    : QWidget{parent}, roomName(roomName), position(position)
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

RoomWidget::~RoomWidget()
{
    workerThread.quit();
    workerThread.wait();

    if(device != nullptr)
    {
        delete device;
    }
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
    QBluetoothLocalDevice *test = new QBluetoothLocalDevice();
    if(!isConnecting && test->hostMode() == QBluetoothLocalDevice::HostConnectable)
    {
#ifdef __arm__
    if(!isNfcActive)
    {
        isNfcActive = true;
        worker = new NfcThread;
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
}

void RoomWidget::createBluetoohDevice(const QString macAddress, const QString type)
{
    delete worker;

    isNfcActive = false;

    deviceMac = macAddress;
    deviceType = type;

    qDebug() << "Device on connect :" << device;

#ifdef QT_DEBUG
#ifndef __arm__
    if(deviceMac.isEmpty())
    {
        deviceMac = QInputDialog::getText(this, tr("Get Bluetooth MAC"),
                                          tr("Module MAC :"), QLineEdit::Normal,
                                          nullptr, nullptr);

        if(deviceMac.isEmpty())
        {
            qWarning() << "Device mac and name invalid. Using debug values";
            deviceMac = "DE:EF:58:97:1A:75";
            deviceName = "BlueNRG";
        }
//        qWarning() << "Device mac or name invalid.";
//        return;
    }
#endif
#endif

    if(deviceMac.isEmpty())
    {
        statusLabel->setText("NFC Read error.\nPlease retry");
        return;
    }

    if(deviceName.isEmpty())
    {
        deviceName = "BlueNRG";
    }

    if(deviceType.isEmpty())
    {
        deviceType = "QDV000";
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

//    if(device)
//    {
//        delete device;
//    }

    device = new BluetoohDevice(deviceName, deviceMac, serviceUuid, characteristicUuid);

    if(device != nullptr)
    {
        connect(device, &BluetoohDevice::changeStatus, this, &RoomWidget::updateBluetoothStatus);
        connect(detachDeviceButton, &QPushButton::clicked, device, &BluetoohDevice::disconnectFromDevice);
        connect(device, &BluetoohDevice::deviceConnectedSignal, this, &RoomWidget::moduleAttachedSlot);
        connect(device, &BluetoohDevice::deviceDisconnectedSignal, this, &RoomWidget::deviceDisconnect);
//        connect(device, &BluetoohDevice::deviceConnectionError, this, &RoomWidget::deviceDisconnect);


        if(deviceType == "PLANTE")
        {
            // Central widget
            if(centralWidget)
            {
                centralWidget->hide();
            }
            centralWidget = new PlantWidget();
            centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            mainLayout->insertWidget(0, centralWidget);
            connect(device, &BluetoohDevice::updateDatas, this, &RoomWidget::updateDatasPlant);

            // Button widget
            if(buttonWidget)
            {
                buttonWidget->hide();
            }
            buttonWidget = new PlantWidget();
            buttonWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
        else//(type == "QDV000")
        {
            if(centralWidget)
            {
                centralWidget->hide();
            }
            centralWidget = new QdvWidget();
            centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            mainLayout->insertWidget(0, centralWidget);
            connect(device, &BluetoohDevice::updateDatas, this, &RoomWidget::updateDatasQdv);

            // Button widget
            if(buttonWidget)
            {
                buttonWidget->hide();
            }
            buttonWidget = new QdvWidget();
            buttonWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }

        if(buttonWidget)
        {
            Q_EMIT roomButtonUpdate(buttonWidget);
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
    reconnectAttempts = 0;
}

void RoomWidget::deviceDisconnect(){

    if(centralWidget)
    {
        centralWidget->hide();
    }

    if(buttonWidget)
    {
        buttonWidget->hide();
    }

//    if(reconnectAttempts < 3)
//    {
//        createBluetoohDevice(deviceMac, deviceType);
//        reconnectAttempts++;
//        return;
//    }

    deviceMac.clear();
    deviceName.clear();
    deviceType.clear();

    detachDeviceButton->setVisible(false);

    controlsLayout->removeWidget(detachDeviceButton);
    controlsLayout->insertWidget(0, attachDeviceButton);
    attachDeviceButton->setVisible(true);

//    if(device)
//    {
//        device->deleteLater();
//    }

    QSettings settings;

    settings.beginGroup(roomName);
        settings.beginGroup(SETTINGS_DEVICES_GROUP);
            settings.remove(deviceMac);
        settings.endGroup();
    settings.endGroup();

    isConnecting = false;
    isNfcActive = false;

    qDebug() << "Device by end of remove :" << device;
}

void RoomWidget::saveDeviceConfiguration()
{
    qDebug() << "Writting devices settings...";
    QSettings settings;

    settings.beginGroup(roomName);
        settings.beginGroup(SETTINGS_DEVICES_GROUP);
            settings.setValue(QString::number(position), deviceMac);
            settings.beginGroup(deviceMac);
            settings.setValue("name", deviceName);
            settings.setValue("service", serviceUuid);
            settings.setValue("characteristic", characteristicUuid);
            settings.setValue("type", deviceType);
            settings.endGroup();
        settings.endGroup();
    settings.endGroup();
}

void RoomWidget::updateDatasQdv(int temp, int press)
{
    qobject_cast<QdvWidget*>(centralWidget)->setTemp(temp/10);
    qobject_cast<QdvWidget*>(centralWidget)->setPressure(press/100);

    qobject_cast<QdvWidget*>(buttonWidget)->setTemp(temp/10);
    qobject_cast<QdvWidget*>(buttonWidget)->setPressure(press/100);
}

void RoomWidget::updateDatasPlant(int waterLevel, int moisture)
{
    qobject_cast<PlantWidget*>(centralWidget)->setMoisture(waterLevel);
    qobject_cast<PlantWidget*>(buttonWidget)->setMoisture(waterLevel);
}

void RoomWidget::updateBluetoothStatus(QString status)
{
    statusLabel->setText(status);
}


