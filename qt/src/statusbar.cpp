#include "statusbar.h"
#include <QIcon>

StatusBar::StatusBar(QWidget *parent)
    : QToolBar{parent}
{
    QIcon::setThemeName("fontawesome");
    this->setMovable(IS_MOVABLE);
    this->setAllowedAreas(Qt::TopToolBarArea);
    this->setContextMenuPolicy(Qt::PreventContextMenu);

    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    homeAction = new QAction(QIcon::fromTheme("home"), NULL, this);
    homeAction->connect(homeAction, SIGNAL(triggered()), this->parent(), SLOT(showMainPage()));

    roomLabel = new QLabel("", this);
    roomLabel->setMaximumWidth(350);
    roomLabel->setContentsMargins(10, 0, 20, 0);

    devAction = new QAction(QIcon::fromTheme("wrench"), NULL, this);

    bluetoothAction = new QAction(QIcon::fromTheme("bluetooth-b"), NULL, this);
//    bluetoothAction->connect(bluetoothAction, SIGNAL(triggered()), this->parent(), SLOT(showBluetoothManager()));

    notificationAction = new QAction(QIcon::fromTheme("bell"), NULL, this);

    settingsAction = new QAction(QIcon::fromTheme("cog"), NULL, this);
    settingsAction->connect(settingsAction, SIGNAL(triggered()), this->parent(), SLOT(showSettings()));

    this->addAction(homeAction);
    this->addWidget(roomLabel);
    this->addWidget(spacer);
    this->addAction(devAction);
    this->addAction(bluetoothAction);
    this->addAction(notificationAction);
    this->addAction(settingsAction);
}

void StatusBar::updateRoomLabel(const QString &roomName)
{
    roomLabel->setText(roomName);
}
