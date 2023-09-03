#include "mainpage.h"
#include "commons.h"
#include "localsettings.h"

static uint8_t widget_count;

MainPage::MainPage(QStackedWidget *navigationStack, QWidget *parent)
    : QWidget{parent}, navigationStack(navigationStack)
{
    widget_count = 0;

    setGeometry(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QGridLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);

    emptyRooms = new QLabel("Create a new room");
    emptyRooms->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(emptyRooms);

    setLayout(this->mainLayout);

    addWidgetButton = new QPushButton("+", this);
    addWidgetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidgetButton->connect(addWidgetButton, SIGNAL(clicked()), this, SLOT(createNewWidget()));
    addWidgetButton->setGeometry(SCREEN_WIDTH-40, SCREEN_HEIGHT-80, 30, 30);

    readSettings();
}

void MainPage::readSettings()
{
    QSettings settings;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
        QStringList roomsId = settings.childKeys();
        roomsId.sort();
        QStringList rooms;
        foreach(const QString &id, roomsId)
        {
            rooms.append(settings.value(id).toString());
        }
    settings.endGroup();

    foreach(const QString &room, rooms)
    {
        settings.beginGroup(room);
            createNewWidget(settings.value(SETTINGS_ROOMS_NAME).toString());
        settings.endGroup();
    }
}

void MainPage::createNewWidget(const QString &roomName)
{
    if(this->widgetsList.length() < 6)
    {
        QString temp_name;

        widget_count += 1;

        if(roomName != nullptr)
        {
            temp_name = roomName;
        }
        else
        {
            temp_name = "ROOM" + QString::number(widget_count);
        }

        RoomAccessButton *temp_button = new RoomAccessButton(this);
        RoomPage *temp_room = new RoomPage(widget_count, this);
        temp_button->setRoom(temp_room);
        temp_button->setText(temp_name);
        temp_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->widgetsList.append(temp_button);
        this->navigationStack->addWidget(temp_room);

        connect(temp_button, &RoomAccessButton::clicked, this->navigationStack,
                [=](){
                    this->navigationStack->setCurrentWidget(temp_button->getRoom());
//                    Q_EMIT updateRoomName(temp_room->getRoomName());
                });

        this->mainLayout->addWidget(temp_button,
                              (this->widgetsList.length()-1)/3,
                              (this->widgetsList.length()-1)%3);

        this->addWidgetButton->raise();
    }

    if(widgetsList.length() > 0)
    {
        emptyRooms->setVisible(false);
    }
}
