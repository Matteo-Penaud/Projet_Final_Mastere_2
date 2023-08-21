#include "statusbar.h"
#include <QIcon>

StatusBar::StatusBar(QWidget *parent)
    : QToolBar{parent}
{
    QIcon::setThemeName("zafiro-light");
    this->setMovable(IS_MOVABLE);
    this->setAllowedAreas(Qt::TopToolBarArea);
    this->setContextMenuPolicy(Qt::PreventContextMenu);

    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    homeAction = new QAction(QIcon::fromTheme("go-home"), NULL, this);
    homeAction->connect(homeAction, SIGNAL(triggered()), this->parent(), SLOT(showMainPage()));

//    energyAction = new QAction(QIcon::fromTheme("battery-good-symbolic"), NULL, this);

    bluetoothAction = new QAction(QIcon::fromTheme("bluetooth-active"), NULL, this);
    bluetoothAction->connect(bluetoothAction, SIGNAL(triggered()), this->parent(), SLOT(showBluetoothManager()));

//    notificationAction = new QAction(QIcon::fromTheme("dialog-error-symbolic"), NULL, this);

    settingsAction = new QAction(QIcon::fromTheme("preferences-system"), NULL, this);
    settingsAction->connect(settingsAction, SIGNAL(triggered()), this->parent(), SLOT(showSettings()));

    this->addAction(homeAction);
    this->addWidget(spacer);
//    this->addAction(energyAction);
    this->addAction(bluetoothAction);
//    this->addAction(notificationAction);
    this->addAction(settingsAction);
}
