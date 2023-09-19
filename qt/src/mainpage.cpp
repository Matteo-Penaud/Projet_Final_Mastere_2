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
    addWidgetButton->setStyleSheet("\
                                    background-color: gray;\
                                    border-radius: 25px;\
                                    color: white; \
                                    font-weight: bold\
                                    ");


    addWidgetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidgetButton->connect(addWidgetButton, SIGNAL(clicked()), this, SLOT(createNewWidget()));
    addWidgetButton->setGeometry(SCREEN_WIDTH-60, SCREEN_HEIGHT-100, 50, 50);

    readSettings();
}

MainPage::~MainPage()
{

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
            qDebug() << settings.value(SETTINGS_ROOMS_NAME).toString();
            createNewWidget(settings.value(SETTINGS_ROOMS_NAME).toString());
        settings.endGroup();
    }
}

unsigned char MainPage::smallestRoomIdAvailable(void)
{
    QSettings settings;
    unsigned char i = 0;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
        QStringList roomsId = settings.childKeys();
        roomsId.sort();
        for(i = 1; i < 7; i++)
        {
            if(roomsId.contains(QString::number(i)) == false)
            {
                break;
            }
        }
    settings.endGroup();

    qDebug() << "Room id available :" << i;
    return i;
}

void MainPage::createNewWidget(const QString &roomName)
{
    unsigned char roomId = 0;
    if(this->widgetsList.length() < 6)
    {
        QString temp_name;

        if(roomName != nullptr)
        {
            roomId = roomName.split("ROOM")[1].toInt();
            temp_name = roomName;
        }
        else
        {
            roomId = smallestRoomIdAvailable();
            temp_name = "ROOM" + QString::number(roomId);
        }

        RoomPage *temp_room = new RoomPage(roomId, this);
        RoomAccessButton *temp_button = new RoomAccessButton(temp_room, roomId, this);
        connect(temp_button, &RoomAccessButton::roomRemoved, this, &MainPage::removeWidget);
        temp_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(temp_room, &RoomPage::roomNameChanged, temp_button, &RoomAccessButton::setRoomName);
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

void MainPage::removeWidget(void)
{
    RoomAccessButton *obj = qobject_cast<RoomAccessButton*>(sender());

    for(unsigned char i = widgetsList.length()-1; i > widgetsList.indexOf(obj); i--)
    {
        if(widgetsList.at(i-1) != nullptr)
        {
            mainLayout->replaceWidget(widgetsList.at(i-1), widgetsList.at(i));
        }
    }

    widgetsList.removeOne(obj);

    if(widgetsList.empty())
    {
        emptyRooms->setVisible(true);
    }

    QSettings settings;
    settings.remove(SETTINGS_GROUP_ROOMS);

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
    for(unsigned char i=0; i < widgetsList.length(); i++)
    {
        settings.setValue(QString::number(i+1), widgetsList.at(i)->getRoom()->getRoomName());
    }
    settings.endGroup();
}
