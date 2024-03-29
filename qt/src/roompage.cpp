#include "roompage.h"
#include "localsettings.h"
#include "stdio.h"

RoomName::RoomName(QString &roomName, QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);

    roomLabel = new QLineEdit(roomName, this);
    roomLabel->setText(roomName);
    roomLabel->setReadOnly(true);
    roomLabel->setStyleSheet("border: none");
    roomLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(roomLabel);


//    editButton = new QPushButton(this);
//    editButton->setIcon(QIcon::fromTheme("pen"));
//    editButton->setFlat(true);
//    mainLayout->addWidget(editButton);

//    connect(editButton, &QPushButton::clicked, this, &RoomName::enableEdition);
    connect(roomLabel, &QLineEdit::returnPressed, this, &RoomName::saveRoomName);
}

RoomName::~RoomName()
{

}

void RoomName::enableEdition()
{
    roomLabel->setReadOnly(false);
    roomLabel->setFocus();

//    keyboard->start("matchbox-keyboard");
}

void RoomName::saveRoomName()
{
    roomLabel->setReadOnly(true);
    emit roomNameChanged(roomLabel->text());
//    keyboard->close();
}

RoomPage::RoomPage(int id, QWidget *parent)
    : QWidget{parent}, id(id)
{
    QSettings settings;
    settings.beginGroup("ROOM" + QString::number(id));
    if(settings.childKeys().contains("name"))
    {
        roomName = settings.value("name").toString();
    }
    else
    {
        roomName = QString("ROOM" + QString::number(id));
    }
    settings.endGroup();

    roomLabel = new RoomName(roomName, this);
    connect(roomLabel, &RoomName::roomNameChanged, this, &RoomPage::setRoomName);

    a = new RoomWidget(roomName, 0, this);
    b = new RoomWidget(roomName, 1, this);
    c = new RoomWidget(roomName, 2, this);

    mainLayout = new QVBoxLayout(this);
    devicesLayout = new QHBoxLayout();
    setLayout(mainLayout);

    mainLayout->addWidget(roomLabel);
    mainLayout->addLayout(devicesLayout);
    devicesLayout->addWidget(a);
    devicesLayout->addWidget(b);
    devicesLayout->addWidget(c);

    connect(a, &RoomWidget::roomButtonUpdate, this, &RoomPage::updateButtonWidgetSlot);

    settingsAddRoom();

    // F4:62:8E:A0:EC:F9
}

RoomPage::~RoomPage()
{
    delete a;
    delete b;
    delete c;
}

void RoomPage::restoreSettings(void)
{
    QSettings settings;
    settings.beginGroup("ROOM" + QString::number(id));
    settings.beginGroup(SETTINGS_DEVICES_GROUP);
    if(settings.contains(QString::number(0)))
    {
        QString mac = settings.value(QString::number(0)).toString();
        settings.beginGroup(mac);
        a->createBluetoohDevice(mac, settings.value("type").toString());
        settings.endGroup();
    }
    if(settings.contains(QString::number(1)))
    {
        QString mac = settings.value(QString::number(1)).toString();
        settings.beginGroup(mac);
        b->createBluetoohDevice(mac, settings.value("type").toString());
        settings.endGroup();
    }
    if(settings.contains(QString::number(2)))
    {
        QString mac = settings.value(QString::number(2)).toString();
        settings.beginGroup(mac);
        c->createBluetoohDevice(mac, settings.value("type").toString());
        settings.endGroup();
    }
    settings.endGroup();
    settings.endGroup();
}

QString RoomPage::getRoomName() const
{
    return roomName;
}

void RoomPage::setRoomName(const QString &newRoomName)
{
    emit roomNameChanged(newRoomName);
    roomName = newRoomName;

    QSettings settings;
    settings.beginGroup("ROOM" + QString::number(id));
    settings.setValue("name", roomName);
    settings.endGroup();
}

void RoomPage::settingsAddRoom()
{
    QSettings settings;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
    settings.setValue(QString::number(id), "ROOM" + QString::number(id));
    settings.endGroup();

    settings.beginGroup("ROOM" + QString::number(id));
    settings.setValue("name", roomName);
    settings.endGroup();
}

void RoomPage::updateButtonWidgetSlot(QWidget *w)
{
    Q_EMIT updateButtonWidgetSignal(w);
}
