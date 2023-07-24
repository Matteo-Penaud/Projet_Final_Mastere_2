#include "mainpage.h"
#include "commons.h"

static uint8_t widget_count;

MainPage::MainPage(QStackedWidget *navigationStack, QWidget *parent)
    : QWidget{parent}, navigationStack(navigationStack)
{
    widget_count = 0;

    this->setGeometry(0, 0, 0, 0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QGridLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);

    this->setLayout(mainLayout);

    addWidgetButton = new QPushButton("+", this);
    addWidgetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidgetButton->connect(addWidgetButton, SIGNAL(clicked()), this, SLOT(createNewWidget()));
    addWidgetButton->setGeometry(SCREEN_WIDTH-40, SCREEN_HEIGHT-80, 30, 30);
}

void MainPage::createNewWidget()
{
    if(widgetsList.length() < 6)
    {
        widget_count += 1;

        QString temp_name = "W" + QString::number(widget_count);

        RoomAccessButton *temp_button = new RoomAccessButton(this);
        RoomWidget *temp_room = new RoomWidget(widget_count, this);
        temp_button->setRoom(temp_room);
        temp_button->setText(temp_name);
        temp_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        widgetsList.append(temp_button);
        navigationStack->addWidget(temp_room);

        connect(temp_button, &QPushButton::clicked, [this, temp_button]() {
                    switchRoom(temp_button->getRoom());
                });


        mainLayout->addWidget(temp_button,
                              (widgetsList.length()-1)/3,
                              (widgetsList.length()-1)%3);

        addWidgetButton->raise();
    }
}

void MainPage::switchRoom(RoomWidget *room)
{
    navigationStack->setCurrentWidget(room);
}


