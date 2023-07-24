#include "roomaccessbutton.h"

RoomAccessButton::RoomAccessButton(QWidget *parent)
    : QPushButton{parent}
{

}

RoomWidget *RoomAccessButton::getRoom() const
{
    return room;
}

void RoomAccessButton::setRoom(RoomWidget *newRoom)
{
    room = newRoom;
}


