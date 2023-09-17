#ifndef ROOMPAGE_H
#define ROOMPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "roomwidget.h"

class RoomName : public QWidget
{
    Q_OBJECT

public:
    explicit RoomName(QString &roomName, QWidget *parent = nullptr);

private:
    QHBoxLayout *mainLayout;
    QLineEdit *roomLabel;
    QPushButton *editButton;

private slots:
    void enableEdition(void);
    void saveRoomName(void);

signals:
    void roomNameChanged(QString roomName);

};

class RoomPage : public QWidget
{
    Q_OBJECT
public:
    explicit RoomPage(int id, QWidget *parent = nullptr);

    QString getRoomName() const;

private slots:
    void setRoomName(const QString &newRoomName);

private:
    char id;
    QVBoxLayout *mainLayout;
    QHBoxLayout *devicesLayout;

    QString roomName;
    RoomName *roomLabel;

    RoomWidget *a;
    RoomWidget *b;
    RoomWidget *c;

    void settingsAddRoom();

signals:
    void roomNameChanged(QString roomName);

};

#endif // ROOMPAGE_H
