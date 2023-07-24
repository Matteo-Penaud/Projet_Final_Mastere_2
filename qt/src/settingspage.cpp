#include "settingspage.h"

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(this->width()/3);
    this->setLayout(mainLayout);

    shutdownButton = new QPushButton("Shutdown", this);
    shutdownButton->connect(shutdownButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    mainLayout->addWidget(shutdownButton);
}
