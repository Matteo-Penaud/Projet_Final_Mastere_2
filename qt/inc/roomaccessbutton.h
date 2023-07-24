#ifndef ROOMACCESSBUTTON_H
#define ROOMACCESSBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "roomwidget.h"

class RoomAccessButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RoomAccessButton(QWidget *parent = nullptr);

    RoomWidget *getRoom() const;
    void setRoom(RoomWidget *newRoom);

private:
    RoomWidget *room;

signals:

};

#endif // ROOMACCESSBUTTON_H
