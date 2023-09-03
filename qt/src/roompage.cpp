#include "roompage.h"
#include "localsettings.h"

RoomPage::RoomPage(int id, QWidget *parent)
    : QWidget{parent}, id(id)
{
    roomName = QString("ROOM" + QString::number(id));

    roomLabel = new QLabel(roomName, this);
    roomLabel->setAlignment(Qt::AlignHCenter);

    a = new RoomWidget(roomName, this);
    b = new RoomWidget(roomName, this);
    c = new RoomWidget(roomName, this);

    mainLayout = new QVBoxLayout(this);
    devicesLayout = new QHBoxLayout();
    setLayout(mainLayout);

    mainLayout->addWidget(roomLabel);
    mainLayout->addLayout(devicesLayout);
    devicesLayout->addWidget(a);
    devicesLayout->addWidget(b);
    devicesLayout->addWidget(c);

    settingsAddRoom();
}

void RoomPage::settingsAddRoom()
{
    QSettings settings;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
    settings.setValue(QString::number(id), roomName);
    settings.endGroup();

    settings.beginGroup(roomName);
    settings.setValue("name", roomName);
    settings.endGroup();
}
