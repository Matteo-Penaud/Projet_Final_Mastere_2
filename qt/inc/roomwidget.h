#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include "bluetoohdevice.h"

class RoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoomWidget(QWidget *parent = nullptr);

    QString getRoomName() const;
    void setRoomName(const QString &newRoomName);

private:
    QGridLayout* mainLayout;
    QLabel* testLabel;
    QLabel* statusLabel;

    QPushButton* addModuleButton;
    QPushButton* removeModuleButton;

    QString roomName;
    QString moduleMac;

    BluetoohDevice *device;

private slots:
    void addModuleSlot(void);
    void updateBluetoothStatus(QString &);

};

#endif // ROOMWIDGET_H
