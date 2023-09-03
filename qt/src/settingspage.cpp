#include "settingspage.h"

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(this->width()/3);
    this->setLayout(mainLayout);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(spacer);

    shutdownButton = new QPushButton("Shutdown", this);
    shutdownButton->connect(shutdownButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    mainLayout->addWidget(shutdownButton);
}
