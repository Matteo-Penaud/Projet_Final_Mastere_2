#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include "bluetoohdevice.h"

class RoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoomWidget(QString &roomName, QWidget *parent = nullptr);

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

    bool isNFCReading = false;

private slots:
    void resetNFCReading(void);
    void requestNFCTag(void);

    void attachModuleSlot(void);
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
