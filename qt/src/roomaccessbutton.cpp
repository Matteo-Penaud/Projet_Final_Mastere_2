#include "roomaccessbutton.h"

RoomAccessButton::RoomAccessButton(QWidget *parent)
    : QPushButton{parent}
{

}

RoomPage *RoomAccessButton::getRoom() const
{
    return this->room;
}

void RoomAccessButton::setRoom(RoomPage *newRoom)
{
    this->room = newRoom;
}
