#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QThread>
#include "bluetoohdevice.h"
#include "nfcthread.h"

class RoomWidget : public QWidget
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit RoomWidget(QString &roomName, QWidget *parent = nullptr);
    ~RoomWidget(){
        workerThread.quit();
        workerThread.wait();
    }

    QString getRoomName() const;
    void setRoomName(QString &newRoomName);

private:
    QVBoxLayout* mainLayout;
    QLabel* datasLabel;
    QLabel* statusLabel;

    QString roomName;

    QString deviceMac;
    QString deviceName;
    QString serviceUuid;
    QString characteristicUuid;

    BluetoohDevice *device;

    QVBoxLayout *controlsLayout;

    QPushButton *attachDeviceButton;
    QPushButton *detachDeviceButton;

private slots:
    void attachModuleSlot(void);
    void createBluetoohDevice(const QString macAddress = NULL);
    void moduleAttachedSlot(void);
    void detachModuleSlot(void);

    void saveDeviceConfiguration(void);

    void updateDatas(QString);
    void updateBluetoothStatus(QString &);

    void resetAll(void);

signals:
    void nfcRead(void);

};

#endif // ROOMWIDGET_H
