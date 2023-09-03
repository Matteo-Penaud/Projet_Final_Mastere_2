#include <qbluetoothuuid.h>

#include "bluetoothdeviceinfo.h"

BluetoothDeviceInfo::BluetoothDeviceInfo(const QBluetoothDeviceInfo &d)
{
    device = d;
}

QString BluetoothDeviceInfo::getAddress() const
{
#ifdef Q_OS_MAC
    // On OS X and iOS we do not have addresses,
    // only unique UUIDs generated by Core Bluetooth.
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

QString BluetoothDeviceInfo::getName() const
{
    return device.name();
}

QBluetoothDeviceInfo BluetoothDeviceInfo::getDevice()
{
    return device;
}

void BluetoothDeviceInfo::setDevice(const QBluetoothDeviceInfo &dev)
{
    device = QBluetoothDeviceInfo(dev);
    Q_EMIT deviceChanged();
}