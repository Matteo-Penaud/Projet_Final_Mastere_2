#include "mainpage.h"
#include "commons.h"

static uint8_t widget_count;

MainPage::MainPage(QStackedWidget *navigationStack, QWidget *parent)
    : QWidget{parent}, navigationStack(navigationStack)
{
    widget_count = 0;

    this->setGeometry(0, 0, 0, 0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(10);
    this->mainLayout->setMargin(20);

    this->setLayout(this->mainLayout);

    this->addWidgetButton = new QPushButton("+", this);
    this->addWidgetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->addWidgetButton->connect(this->addWidgetButton, SIGNAL(clicked()), this, SLOT(createNewWidget()));
    this->addWidgetButton->setGeometry(SCREEN_WIDTH-40, SCREEN_HEIGHT-80, 30, 30);
}

void MainPage::createNewWidget()
{
    if(this->widgetsList.length() < 6)
    {
        widget_count += 1;

        QString temp_name = "W" + QString::number(widget_count);

        RoomAccessButton *temp_button = new RoomAccessButton(this);
        RoomWidget *temp_room = new RoomWidget(widget_count, this);
        temp_button->setRoom(temp_room);
        temp_button->setText(temp_name);
        temp_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->widgetsList.append(temp_button);
        this->navigationStack->addWidget(temp_room);

        connect(temp_button, &RoomAccessButton::clicked, this->navigationStack,
                [=](){
                    this->navigationStack->setCurrentWidget(temp_button->getRoom());
                });


        this->mainLayout->addWidget(temp_button,
                              (this->widgetsList.length()-1)/3,
                              (this->widgetsList.length()-1)%3);

        this->addWidgetButton->raise();
    }
}

