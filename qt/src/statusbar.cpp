#include "statusbar.h"
#include "mainwindow.h"
#include <QIcon>

StatusBar::StatusBar(QWidget *parent)
    : QToolBar{parent}
{
    this->setMovable(IS_MOVABLE);
    this->setAllowedAreas(Qt::TopToolBarArea);
    this->setContextMenuPolicy(Qt::PreventContextMenu);

    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    homeAction = new QAction(QIcon::fromTheme("go-home-symbolic"), NULL, this);
    homeAction->connect(homeAction, SIGNAL(triggered()), this->parent(), SLOT(showMainPage()));

    energyAction = new QAction(QIcon::fromTheme("battery-good-symbolic"), NULL, this);

    networkAction = new QAction(QIcon::fromTheme("network-wireless-signal-ok-symbolic"), NULL, this);

    notificationAction = new QAction(QIcon::fromTheme("dialog-error-symbolic"), NULL, this);

    settingsAction = new QAction(QIcon::fromTheme("preferences-system-symbolic"), NULL, this);
    settingsAction->connect(settingsAction, SIGNAL(triggered()), this->parent(), SLOT(showSettings()));

    this->addAction(homeAction);
    this->addWidget(spacer);
    this->addAction(energyAction);
    this->addAction(networkAction);
    this->addAction(notificationAction);
    this->addAction(settingsAction);
}
