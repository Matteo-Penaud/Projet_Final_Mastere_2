#include <QMetaEnum>
#include <QTimer>
#include "bluetoohdevice.h"
#include "bluetoohserviceinfo.h"
#include "characteristicinfo.h"
#include "commons.h"

BluetoohDevice::BluetoohDevice(QString name, QString macAddress, QString serviceUuid, QString characteristicUuid, QWidget *parent)
    : QWidget{parent},
    m_macAddress(macAddress), m_name(name),
    m_serviceUuid(serviceUuid), m_characteristicUuid(characteristicUuid)
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoohDevice::addDevice);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BluetoohDevice::deviceScanError);
    connect(this, &BluetoohDevice::deviceFound, discoveryAgent, &QBluetoothDeviceDiscoveryAgent::stop);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoohDevice::deviceScanFinished);

    qDebug() << m_serviceUuid << m_characteristicUuid;
}

BluetoohDevice::~BluetoohDevice()
{
    delete discoveryAgent;
    delete controller;
}

void BluetoohDevice::startDeviceDiscovery()
{
    QString temp;

    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    if (discoveryAgent->isActive()) {
        temp = "Discovering devices...";
        Q_EMIT changeStatus(temp);
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

    if (controller != NULL && controller->state() != QLowEnergyController::UnconnectedState)
        controller->disconnectFromDevice();
    else
        deviceDisconnected();
}


void BluetoohDevice::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    QString temp;

    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
    {
        qInfo() << "The Bluetooth adaptor is powered off, power it on before doing discovery.";

        temp = QString("Error : Bluetooth adapter is not powerd on");
    }
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        qInfo() << "Writing or reading from the device resulted in an error.";
    else {
        static QMetaEnum qme = discoveryAgent->metaObject()->enumerator(
            discoveryAgent->metaObject()->indexOfEnumerator("Error"));
        qInfo() << "Error: " + QLatin1String(qme.valueToKey(error));
    }

    if(!temp.isEmpty())
    {
        Q_EMIT changeStatus(temp);
    }
}

void BluetoohDevice::deviceScanFinished()
{
    qInfo() << "Discover ended.";
    QString temp = "Device not found";
    Q_EMIT changeStatus(temp);
}

void BluetoohDevice::scanServices()
{
    if (!currentDevice.getDevice().isValid()) {
        qInfo() << m_macAddress + " : Not a valid device";
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

    if(controller)
    {
        if (isRandomAddress())
            controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
        else
            controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

        controller->connectToDevice();
    }
}

void BluetoohDevice::addLowEnergyService(const QBluetoothUuid &serviceUuid)
{
    //! [les-service-1]
    QLowEnergyService *service = controller->createServiceObject(serviceUuid);
    if (!service) {
        qWarning() << m_macAddress + " : Cannot create service for uuid";
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
    qInfo() << m_macAddress + " : Services discovered, seeking viable datas...";

    connectToService(m_serviceUuid);
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
        qWarning() << m_macAddress + " : Error : Unable to find seeked service";
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
        if(cInfo->getUuid() == m_characteristicUuid)
        {
            m_characteristic = ch;
        }
    }

//    QTimer::singleShot(0, this, &BluetoohDevice::characteristicsUpdated);
}

void BluetoohDevice::characteristicUpdated(const QLowEnergyCharacteristic &ch, const QByteArray &newValue)
{
    auto cInfo = new CharacteristicInfo(ch);

    if(cInfo->getUuid() == m_characteristicUuid)
    {
        QString data = QString(cInfo->getValue());
        QString temp = QString(data[7*2 + 1]) + data[6*2] + data[6*2 +1];

        QString press = QString(data[4*2 + 1]) + data[3*2] + data[3*2 + 1] + data[2*2] + data[2*2 + 1];

        Q_EMIT updateDatas(
            temp.toInt(nullptr, 16),
            press.toInt(nullptr, 16)
        );

        qInfo() << m_macAddress + " : " + data << "Found temp:" << temp.toUInt(nullptr, 16);
    }
}


void BluetoohDevice::serviceDetailsDiscovered(QLowEnergyService::ServiceState newState)
{
    switch(newState)
    {
    case (QLowEnergyService::ServiceDiscovered) :
        const QList<QLowEnergyCharacteristic> chars = m_service->characteristics();
        for (const QLowEnergyCharacteristic &ch : chars) {
            if(ch.uuid().toString() == QString("{%1}").arg(m_characteristicUuid))
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
//            qWarning() << ch.properties();
//        }
//    }
    //! [les-chars]
}

void BluetoohDevice::deviceConnected()
{
    QString temp = QString("Connected to ") + currentDevice.getAddress();

    qInfo() << m_macAddress +  " : Connected to device";
    Q_EMIT changeStatus(temp);
    connected = true;

    controller->discoverServices();

    Q_EMIT deviceConnectedSignal();
}

void BluetoohDevice::errorReceived(QLowEnergyController::Error /*error*/)
{
    QString temp = QString("Disconnected due to error :\n" + controller->errorString());
    qWarning() << m_macAddress + " : Error: " << controller->errorString();

    Q_EMIT changeStatus(temp);
    Q_EMIT deviceConnectionError();
}

void BluetoohDevice::deviceDisconnected()
{
    QString temp = QString("Disconnected from device");
    Q_EMIT changeStatus(temp);

    qInfo() << m_macAddress + " : Disconnected from device";

    Q_EMIT deviceDisconnectedSignal();
}

bool BluetoohDevice::isRandomAddress() const
{
    return randomAddress;
}
