#include "statusbar.h"
#include <QIcon>

StatusBar::StatusBar(QWidget *parent)
    : QToolBar{parent}
{
    this->setMovable(IS_MOVABLE);
    this->setAllowedAreas(Qt::TopToolBarArea);

    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->addAction(QIcon::fromTheme("go-home-symbolic"), NULL);
    this->addWidget(spacer);
    this->addAction(QIcon::fromTheme("battery-good-symbolic"), NULL);
    this->addAction(QIcon::fromTheme("network-wireless-signal-ok-symbolic"), NULL);
    this->addAction(QIcon::fromTheme("dialog-error-symbolic"), NULL);
    this->addAction(QIcon::fromTheme("preferences-system-symbolic"), NULL);
}
