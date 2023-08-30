#include "../inc/bluetoohserviceinfo.h"

BluetoohServiceInfo::BluetoohServiceInfo(QLowEnergyService *service):
    m_service(service)
{
    m_service->setParent(this);
}

QLowEnergyService *BluetoohServiceInfo::service() const
{
    return m_service;
}

QString BluetoohServiceInfo::getName() const
{
    if (!m_service)
        return QString();

    return m_service->serviceName();
}

QString BluetoohServiceInfo::getType() const
{
    if (!m_service)
        return QString();

    QString result;
    if (m_service->type() & QLowEnergyService::PrimaryService)
        result += QStringLiteral("primary");
    else
        result += QStringLiteral("secondary");

    if (m_service->type() & QLowEnergyService::IncludedService)
        result += QStringLiteral(" included");

    result.prepend('<').append('>');

    return result;
}

QString BluetoohServiceInfo::getUuid() const
{
    if (!m_service)
        return QString();

    const QBluetoothUuid uuid = m_service->serviceUuid();
    bool success = false;
    quint16 result16 = uuid.toUInt16(&success);
    if (success)
        return QStringLiteral("0x") + QString::number(result16, 16);

    quint32 result32 = uuid.toUInt32(&success);
    if (success)
        return QStringLiteral("0x") + QString::number(result32, 16);

    return uuid.toString().remove(QLatin1Char('{')).remove(QLatin1Char('}'));
}
