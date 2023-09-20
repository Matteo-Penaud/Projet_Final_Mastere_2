#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QThread>
#include <QTimer>
#include "bluetoohdevice.h"
#include "nfcthread.h"
#include "plantwidget.h"
#include "qdvwidget.h"

class RoomWidget : public QWidget
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit RoomWidget(QString &roomName, unsigned char position = 0, QWidget *parent = nullptr);
    ~RoomWidget();

    QString getRoomName() const;
    void setRoomName(QString &newRoomName);

private:
    bool isConnecting = false;

    QString roomName;
    unsigned char position;

    QVBoxLayout* mainLayout;
    QLabel* datasLabel;
    QWidget* centralWidget = nullptr;
    QWidget* buttonWidget = nullptr;

    QLabel* statusLabel;


    QString deviceMac;
    QString deviceName;
    QString deviceType;
    QString serviceUuid;
    QString characteristicUuid;

    BluetoohDevice *device = nullptr;

    QVBoxLayout *controlsLayout;

    QPushButton *attachDeviceButton;
    QPushButton *detachDeviceButton;

    unsigned char reconnectAttempts = 0;

    NfcThread *worker = nullptr;

public slots:
    void createBluetoohDevice(const QString macAddress = NULL, const QString type = NULL);

private slots:
    void attachModuleSlot(void);
    void moduleAttachedSlot(void);
    void deviceDisconnect(void);

    void saveDeviceConfiguration(void);

    void updateDatasQdv(int, int);
    void updateDatasPlant(int, int);
    void updateBluetoothStatus(QString);

//    bool deviceExists(void);

signals:
    void nfcRead(void);
    void roomButtonUpdate(QWidget*);

};

#endif // ROOMWIDGET_H
