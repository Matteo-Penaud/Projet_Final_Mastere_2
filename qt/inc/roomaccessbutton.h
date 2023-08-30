#ifndef ROOMACCESSBUTTON_H
#define ROOMACCESSBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "roompage.h"

class RoomAccessButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RoomAccessButton(QWidget *parent = nullptr);

    RoomPage *getRoom() const;
    void setRoom(RoomPage *newRoom);

private:
    RoomPage *room;
};

#endif // ROOMACCESSBUTTON_H
