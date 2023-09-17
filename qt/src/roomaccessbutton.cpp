#include "roomaccessbutton.h"

RoomAccessButton::RoomAccessButton(RoomPage *room, QWidget *parent)
    : QPushButton{parent}, room(room)
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    setStyleSheet("\
    QPushButton { \
        background-color: rgba(175, 196, 227, 30%); \
        border: 3px solid rgba(50, 50, 50, 120);\
        border-radius: 20px; \
    }; \
    background-color: rgba(0, 0, 0, 0%); \
    ");
    connect(this, &RoomAccessButton::longPressEvent, this, &RoomAccessButton::onLongPressed);

    roomName = new QLabel(room->getRoomName(), this);
    roomName->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(roomName);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(spacer);
}

RoomPage *RoomAccessButton::getRoom() const
{
    return this->room;
}

void RoomAccessButton::setRoom(RoomPage *newRoom)
{
    this->room = newRoom;
}

void RoomAccessButton::setRoomName(QString newRoomName)
{
    roomName->setText(newRoomName);
}

void RoomAccessButton::mousePressEvent(QMouseEvent *e)
{
    mLastPressTime=QDateTime::currentMSecsSinceEpoch();
}

void RoomAccessButton::onLongPressed()
{
    qDebug() << "User right clicked me";
}

void RoomAccessButton::mouseReleaseEvent(QMouseEvent *e)
{
    // Calculate for how long the button has been pressed upon release
    const quint64 pressTime = QDateTime::currentMSecsSinceEpoch() - mLastPressTime;
    // The press time exceeds our "threshold" and this constitutes a longpress
    if( pressTime > MY_LONG_PRESS_THRESHOLD){
        // We pass the original mouse event in case it is useful (it contains all sorts of goodies like mouse posittion, which button was pressed etc).
        emit longPressEvent();
    }
    else
    {
        emit clicked();
    }
}
