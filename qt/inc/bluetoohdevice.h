#ifndef BLUETOOHDEVICE_H
#define BLUETOOHDEVICE_H

#include <QWidget>
#include <QLowEnergyController>
#include <QString>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QTimer>

#include "bluetoothdeviceinfo.h"

class BluetoohDevice : public QWidget
{
    Q_OBJECT
public:
    explicit BluetoohDevice(QString name, QString macAddress, QString serviceUuid, QString characteristicUuid, QWidget *parent = nullptr);
    ~BluetoohDevice();

    // Fonctions du discoveryAgent (permet de recuperer la cible)
    void scanServices();
    bool isRandomAddress() const;

    bool connected = false;

private:
    QString m_macAddress;
    QString m_name;
    QString m_serviceUuid;
    QString m_characteristicUuid;

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    BluetoothDeviceInfo currentDevice;
    QLowEnergyController *controller = nullptr;

    QList<QObject *> m_services;
    QList<QObject *> m_characteristics;
    QLowEnergyService *m_service;
    QLowEnergyCharacteristic m_characteristic;

    bool randomAddress = false;

    void serviceDetailsDiscovered(QLowEnergyService::ServiceState newState);

private slots:
    /* Bluetooth discovery related slots */
    void addDevice(const QBluetoothDeviceInfo&);
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);
    void deviceScanFinished(void);

    /* Device related slots */
    void addLowEnergyService(const QBluetoothUuid &uuid);
    void deviceConnected();
    void deviceDisconnected();
    void serviceScanDone();

    void errorReceived(QLowEnergyController::Error);
    void characteristicUpdated(const QLowEnergyCharacteristic &ch, const QByteArray &newValue);

public slots:
    void startDeviceDiscovery(void);
    void disconnectFromDevice(void);
    void connectToService(const QString &uuid);

signals:
    void deviceFound(void);
    void changeStatus(QString);
    void updateDatas(int, int);

    void deviceConnectedSignal(void);
    void deviceDisconnectedSignal(void);
};

#endif // BLUETOOHDEVICE_H
