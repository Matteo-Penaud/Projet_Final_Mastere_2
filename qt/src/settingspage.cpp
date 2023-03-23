#include "settingspage.h"

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    test = new QPushButton("Caca", this);
    test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
