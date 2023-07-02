#include "mainpage.h"

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
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
        QPushButton* temp_button = new QPushButton("W", this);
        temp_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        widgetsList.append(temp_button);

        mainLayout->addWidget(temp_button,
                              (widgetsList.length()-1)/3,
                              (widgetsList.length()-1)%3
                              );

        addWidgetButton->raise();
    }
}

