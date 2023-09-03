#ifndef ROOMPAGE_H
#define ROOMPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "roomwidget.h"

class RoomPage : public QWidget
{
    Q_OBJECT
public:
    explicit RoomPage(int id, QWidget *parent = nullptr);

private:
    char id;
    QVBoxLayout *mainLayout;
    QHBoxLayout *devicesLayout;

    QString roomName;
    QLabel *roomLabel;

    RoomWidget *a;
    RoomWidget *b;
    RoomWidget *c;

    void settingsAddRoom();

signals:

};

#endif // ROOMPAGE_H
