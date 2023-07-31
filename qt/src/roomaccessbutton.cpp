#include "roomaccessbutton.h"

RoomAccessButton::RoomAccessButton(QWidget *parent)
    : QPushButton{parent}
{

}

RoomWidget *RoomAccessButton::getRoom() const
{
    return this->room;
}

void RoomAccessButton::setRoom(RoomWidget *newRoom)
{
    this->room = newRoom;
}
