#include "roompage.h"

RoomPage::RoomPage(int id, QWidget *parent)
    : QWidget{parent}
{
    roomName = QString("ROOM" + QString::number(id));

    roomLabel = new QLabel(roomName, this);
    roomLabel->setAlignment(Qt::AlignHCenter);

    a = new RoomWidget(this);
    b = new RoomWidget(this);
    c = new RoomWidget(this);

    mainLayout = new QVBoxLayout(this);
    devicesLayout = new QHBoxLayout();
    setLayout(mainLayout);

    mainLayout->addWidget(roomLabel);
    mainLayout->addLayout(devicesLayout);
    devicesLayout->addWidget(a);
    devicesLayout->addWidget(b);
    devicesLayout->addWidget(c);
}

