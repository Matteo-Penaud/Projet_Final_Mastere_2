#include "roomaccessbutton.h"
#include "localsettings.h"

RoomAccessButton::RoomAccessButton(RoomPage *room, unsigned char id, QWidget *parent)
    : QPushButton{parent}, room(room), id(id)
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    setStyleSheet("\
    QPushButton { \
        background-color: rgba(175, 175, 175, 15%); \
        border: 3px solid rgba(50, 50, 50, 255);\
        border-radius: 20px; \
    }; \
    background-color: rgba(0, 0, 0, 0%); \
    ");
    connect(this, &RoomAccessButton::longPressEvent, this, &RoomAccessButton::onLongPressed);
    connect(room, &RoomPage::updateButtonWidgetSignal, this, &RoomAccessButton::updateCentralWidget);

    roomName = new QLabel(room->getRoomName(), this);
    roomName->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(roomName);
    mainLayout->setAlignment(Qt::AlignTop);

}

RoomAccessButton::~RoomAccessButton()
{
    if(room != nullptr)
    {
        delete room;
    }
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

void RoomAccessButton::updateCentralWidget(QWidget *centralWidget)
{
    if(centralWidget != nullptr)
    {
        mainLayout->addWidget(centralWidget);
//        centralWidget->setMaximumSize(QSize())
    }
}

void RoomAccessButton::mousePressEvent(QMouseEvent *e)
{
    mLastPressTime=QDateTime::currentMSecsSinceEpoch();
}

void RoomAccessButton::onLongPressed()
{
    qWarning() << "Removing room" << id;

    QSettings settings;
    QString blockName;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
    blockName = settings.value(QString::number(id)).toString();
    settings.remove(QString::number(id));
    settings.endGroup();

    settings.remove(blockName);

    Q_EMIT roomRemoved();

    delete this;
}

void RoomAccessButton::mouseReleaseEvent(QMouseEvent *e)
{
    // Calculate for how long the button has been pressed upon release
    const quint64 pressTime = QDateTime::currentMSecsSinceEpoch() - mLastPressTime;
    // The press time exceeds our "threshold" and this constitutes a longpress
    if( pressTime > MY_LONG_PRESS_THRESHOLD){
        // We pass the original mouse event in case it is useful (it contains all sorts of goodies like mouse posittion, which button was pressed etc).
        if(isRemoving)
        {
            emit longPressEvent();
        }
        else
        {
            setStyleSheet("\
            QPushButton { \
                background-color: rgba(220, 50, 50, 15%); \
                border: 3px solid rgba(50, 50, 50, 255);\
                border-radius: 20px; \
            }; \
            background-color: rgba(0, 0, 0, 0%); \
            ");

            isRemoving = true;
        }
    }
    else
    {
        if(isRemoving)
        {
            setStyleSheet("\
            QPushButton { \
                background-color: rgba(175, 175, 175, 15%); \
                border: 3px solid rgba(50, 50, 50, 255);\
                border-radius: 20px; \
            }; \
            background-color: rgba(0, 0, 0, 0%); \
            ");

            isRemoving = false;
        }
        emit clicked();
    }
}
