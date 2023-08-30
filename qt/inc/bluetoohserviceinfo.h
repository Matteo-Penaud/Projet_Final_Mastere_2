#ifndef BLUETOOHSERVICEINFO_H
#define BLUETOOHSERVICEINFO_H
#include <QtBluetooth/QLowEnergyService>

#include <QObject>

class BluetoohServiceInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serviceName READ getName NOTIFY serviceChanged)
    Q_PROPERTY(QString serviceUuid READ getUuid NOTIFY serviceChanged)
    Q_PROPERTY(QString serviceType READ getType NOTIFY serviceChanged)
public:
    BluetoohServiceInfo() = default;
    BluetoohServiceInfo(QLowEnergyService *service);
    QLowEnergyService *service() const;
    QString getUuid() const;
    QString getName() const;
    QString getType() const;

Q_SIGNALS:
    void serviceChanged();

private:
    QLowEnergyService *m_service = nullptr;

};

#endif // BLUETOOHSERVICEINFO_H
