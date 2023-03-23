#include "mainpage.h"

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    for(uint8_t i=0; i < 1; i++)
    {
        RoomWidget* temp_room = new RoomWidget(this);

        mainLayout->addWidget(temp_room);
    }
}
