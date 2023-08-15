#ifndef BLUETOOTHPAGE_H
#define BLUETOOTHPAGE_H

#include <qbluetoothlocaldevice.h>

#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

class BluetoothPage : public QWidget
{
    Q_OBJECT
public:
    explicit BluetoothPage(QBluetoothLocalDevice *localDevice, QWidget *parent = nullptr);

private:
    QLabel *headerLabel;
    QLabel *localAddress;

    QBluetoothLocalDevice *localDevice;

signals:

};

#endif // BLUETOOTHPAGE_H
