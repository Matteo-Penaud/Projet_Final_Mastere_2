#ifndef BLUETOOTHPAGE_H
#define BLUETOOTHPAGE_H

#include <qbluetoothlocaldevice.h>
#include <bluetoothserver.h>

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QWidget>

class BluetoothPage : public QWidget
{
    Q_OBJECT
public:
    explicit BluetoothPage(QBluetoothLocalDevice *localDevice, QWidget *parent = nullptr);
    ~BluetoothPage();

private:
    QLabel *headerLabel;
    QLabel *localAddress;
    QListWidget *subscribersList;
    QPushButton *restartServerButton;

    BluetoothServer *bluetoothServer;
    QBluetoothLocalDevice *localDevice;

private slots:
    void clientConnected(const QString &name);
    void clientDisconnected(const QString &name);
    void showMessage(const QString &sender, const QString &message);

signals:


};

#endif // BLUETOOTHPAGE_H
