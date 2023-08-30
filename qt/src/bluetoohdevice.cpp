#include <QMetaEnum>
#include <QTimer>
#include "bluetoohdevice.h"
#include "bluetoohserviceinfo.h"
#include "characteristicinfo.h"
#include "commons.h"

BluetoohDevice::BluetoohDevice(QString name, QString macAddress, QWidget *parent)
    : QWidget{parent}, m_macAddress(macAddress), m_name(name)
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoohDevice::addDevice);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BluetoohDevice::deviceScanError);
    connect(this, &BluetoohDevice::deviceFound, discoveryAgent, &QBluetoothDeviceDiscoveryAgent::stop);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoohDevice::deviceScanFinished);

    startDeviceDiscovery();
}

BluetoohDevice::~BluetoohDevice()
{
    delete discoveryAgent;
    delete controller;
}

void BluetoohDevice::startDeviceDiscovery()
{
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    QString temp = QString("Discovering devices...");
    Q_EMIT changeStatus(temp);

    if (discoveryAgent->isActive()) {
        DEBUG_OUT("Discovering...");
    }
}

void BluetoohDevice::addDevice(const QBluetoothDeviceInfo &info)
{
    QString temp = QString("Connecting to device...");
    Q_EMIT changeStatus(temp);

    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        if(info.address().toString() == m_macAddress && info.name() == m_name)
        {
            DEBUG_OUT("Device found");
            currentDevice.setDevice(info);
            Q_EMIT deviceFound();
            scanServices();
        }
        else
        {
            DEBUG_OUT(info.address().toString());
        }
    }
}

void BluetoohDevice::disconnectFromDevice()
{
    // UI always expects disconnect() signal when calling this signal
    // TODO what is really needed is to extend state() to a multi value
    // and thus allowing UI to keep track of controller progress in addition to
    // device scan progress

    QString temp = QString("User requested disconnect...");
    Q_EMIT changeStatus(temp);

    if (controller->state() != QLowEnergyController::UnconnectedState)
        controller->disconnectFromDevice();
    else
        deviceDisconnected();
}


void BluetoohDevice::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        DEBUG_OUT("The Bluetooth adaptor is powered off, power it on before doing discovery.");
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        DEBUG_OUT("Writing or reading from the device resulted in an error.");
    else {
        static QMetaEnum qme = discoveryAgent->metaObject()->enumerator(
            discoveryAgent->metaObject()->indexOfEnumerator("Error"));
        DEBUG_OUT("Error: " + QLatin1String(qme.valueToKey(error)));
    }
}

void BluetoohDevice::deviceScanFinished()
{
    DEBUG_OUT("Discover ended.");
}

void BluetoohDevice::scanServices()
{
    if (!currentDevice.getDevice().isValid()) {
        qWarning() << "Not a valid device";
        return;
    }

    if (!controller) {
        // Connecting signals and slots for connecting to LE services.
        controller = QLowEnergyController::createCentral(currentDevice.getDevice());
        connect(controller, &QLowEnergyController::connected,
                this, &BluetoohDevice::deviceConnected);
        connect(controller, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),
                this, &BluetoohDevice::errorReceived);
        connect(controller, &QLowEnergyController::disconnected,
                this, &BluetoohDevice::deviceDisconnected);
        connect(controller, &QLowEnergyController::serviceDiscovered,
                this, &BluetoohDevice::addLowEnergyService);
        connect(controller, &QLowEnergyController::discoveryFinished,
                this, &BluetoohDevice::serviceScanDone);
    }

    if (isRandomAddress())
        controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
    else
        controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

    controller->connectToDevice();
}

void BluetoohDevice::addLowEnergyService(const QBluetoothUuid &serviceUuid)
{
    //! [les-service-1]
    QLowEnergyService *service = controller->createServiceObject(serviceUuid);
    if (!service) {
        qWarning() << "Cannot create service for uuid";
        return;
    }
    //! [les-service-1]
    auto serv = new BluetoohServiceInfo(service);
    m_services.append(serv);
}

void BluetoohDevice::serviceScanDone()
{
    // force UI in case we didn't find anything
//    if (m_services.isEmpty())
//        emit servicesUpdated();
    qWarning() << "Services discovered, seeking viable datas...";

    connectToService("00000000-0001-11e1-9ab4-0002a5d5c51b");
}

void BluetoohDevice::connectToService(const QString &uuid)
{
//    QLowEnergyService *service = nullptr;
    for (auto s: qAsConst(m_services)) {
        auto serviceInfo = qobject_cast<BluetoohServiceInfo *>(s);
        if (!serviceInfo)
            continue;

        if (serviceInfo->getUuid() == uuid) {
            m_service = serviceInfo->service();
            break;
        }
    }

    if (!m_service)
    {
        qWarning() << "Error : Unable to find seeked service";
        return;
    }

    qDeleteAll(m_characteristics);
    m_characteristics.clear();

    if (m_service->state() == QLowEnergyService::DiscoveryRequired) {
        //! [les-service-3]
        connect(m_service, &QLowEnergyService::stateChanged,
                this, &BluetoohDevice::serviceDetailsDiscovered);
        connect(m_service, &QLowEnergyService::characteristicChanged,
                this, &BluetoohDevice::characteristicUpdated);
        m_service->discoverDetails();
        //! [les-service-3]
        return;
    }

    //discovery already done
    const QList<QLowEnergyCharacteristic> chars = m_service->characteristics();
    for (const QLowEnergyCharacteristic &ch : chars) {
        auto cInfo = new CharacteristicInfo(ch);
        m_characteristics.append(cInfo);
        if(cInfo->getUuid() == "00140000-0001-11e1-ac36-0002a5d5c51b")
        {
            m_characteristic = ch;
        }
    }

//    QTimer::singleShot(0, this, &BluetoohDevice::characteristicsUpdated);
}

void BluetoohDevice::characteristicUpdated(const QLowEnergyCharacteristic &ch, const QByteArray &newValue)
{
    auto cInfo = new CharacteristicInfo(ch);
    if(cInfo->getUuid() == "00140000-0001-11e1-ac36-0002a5d5c51b")
    {
        qWarning() << cInfo->getValue();
    }
}


void BluetoohDevice::serviceDetailsDiscovered(QLowEnergyService::ServiceState newState)
{
    if (newState == QLowEnergyService::ServiceDiscovered) {
        // do not hang in "Scanning for characteristics" mode forever
        // in case the service discovery failed
        // We have to queue the signal up to give UI time to even enter
        // the above mode
//        if (newState != QLowEnergyService::DiscoveringServices) {
//            QMetaObject::invokeMethod(this, "characteristicsUpdated",
//                                      Qt::QueuedConnection);
//        }

        qWarning() << "Mega prout";

        const QList<QLowEnergyCharacteristic> chars = m_service->characteristics();
        for (const QLowEnergyCharacteristic &ch : chars) {
            if(ch.uuid().toString() == "{00140000-0001-11e1-ac36-0002a5d5c51b}")
            {
                m_characteristic = ch;
            }
        }

        QLowEnergyDescriptor notificationDesc = m_characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if (notificationDesc.isValid())
            m_service->writeDescriptor(notificationDesc, QByteArray::fromHex("0100"));

        return;
    }

//    auto service = qobject_cast<QLowEnergyService *>(sender());
//    if (!service)
//        return;

//    //! [les-chars]
//    const QList<QLowEnergyCharacteristic> chars = service->characteristics();
//    for (const QLowEnergyCharacteristic &ch : chars) {
//        auto cInfo = new CharacteristicInfo(ch);
//        m_characteristics.append(cInfo);
//        if(cInfo->getUuid() == "00140000-0001-11e1-ac36-0002a5d5c51b")
//        {
////            qWarning() << cInfo->getValue();
////            service->writeCharacteristic(ch, ch.value()  0x10);
//            qWarning() << "Caca";
//            qWarning() << ch.properties();
//        }
//    }
    //! [les-chars]
}

void BluetoohDevice::deviceConnected()
{
    QString temp = QString("Connected to ") + currentDevice.getAddress();

    qWarning() << "Connected to device";
    Q_EMIT changeStatus(temp);
    connected = true;

    controller->discoverServices();
}

void BluetoohDevice::errorReceived(QLowEnergyController::Error /*error*/)
{
    QString temp = QString("Disconnected due to error : " + controller->errorString());
    Q_EMIT changeStatus(temp);

    qWarning() << "Error: " << controller->errorString();
}

void BluetoohDevice::deviceDisconnected()
{
    QString temp = QString("Disconnected from device");
    Q_EMIT changeStatus(temp);

    qWarning() << "Disconnect from device";
}

bool BluetoohDevice::isRandomAddress() const
{
    return randomAddress;
}
