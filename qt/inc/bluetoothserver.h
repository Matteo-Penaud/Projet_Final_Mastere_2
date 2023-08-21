#ifndef BLUETOOTHSERVER_H
#define BLUETOOTHSERVER_H

#include <QtBluetooth/qbluetoothaddress.h>
#include <QtBluetooth/qbluetoothserviceinfo.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

#include <QObject>

class BluetoothServer : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothServer(QObject *parent = nullptr);
    ~BluetoothServer();

    void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
    void stopServer();

public slots:
    void sendMessage(const QString &message);
    void restartServer();

signals:
    void messageReceived(const QString &sender, const QString &message);
    void clientConnected(const QString &name);
    void clientDisconnected(const QString &name);

private slots:
    void clientConnected();
    void clientDisconnected();
    void readSocket();

private:
    QBluetoothServer *rfcommServer = nullptr;
    QBluetoothServiceInfo serviceInfo;
    QList<QBluetoothSocket *> clientSockets;
};
//! [declaration]

#endif // BLUETOOTHSERVER_H
