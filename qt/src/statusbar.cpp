#include "statusbar.h"
#include <QIcon>

StatusBar::StatusBar(QWidget *parent)
    : QToolBar{parent}
{
    setMovable(IS_MOVABLE);
    setAllowedAreas(Qt::TopToolBarArea);
    setContextMenuPolicy(Qt::PreventContextMenu);

    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    homeAction = new QAction(QIcon::fromTheme("home"), NULL, this);
    homeAction->connect(homeAction, SIGNAL(triggered()), this->parent(), SLOT(showMainPage()));

    backAction = new QAction(QIcon::fromTheme("angle-left"), NULL, this);
//    backAction->connect(backAction, SIGNAL(triggered()), this->parent(), SLOT(showDevPage()));

    editAction = new QAction(QIcon::fromTheme("pen"), NULL, this);
//    editAction->connect(editAction, SIGNAL(triggered()), this->parent(), SLOT(showDevPage()));

    roomLabel = new QLabel("", this);
    roomLabel->setMaximumWidth(350);
    roomLabel->setContentsMargins(10, 0, 20, 0);

#ifdef QT_DEBUG
    testsAction = new QAction(QIcon::fromTheme("book-open"), NULL, this);
    testsAction->connect(testsAction, SIGNAL(triggered()), this->parent(), SLOT(showTestsPage()));
#endif

    devAction = new QAction(QIcon::fromTheme("wrench"), NULL, this);
    devAction->connect(devAction, SIGNAL(triggered()), this->parent(), SLOT(showDevPage()));

    bluetoothAction = new QAction(QIcon::fromTheme("bluetooth-b"), NULL, this);
    bluetoothAction->connect(bluetoothAction, SIGNAL(triggered()), this->parent(), SLOT(showBluetoothManager()));

//    notificationAction = new QAction(QIcon::fromTheme("bell"), NULL, this);

    settingsAction = new QAction(QIcon::fromTheme("cog"), NULL, this);
    settingsAction->connect(settingsAction, SIGNAL(triggered()), this->parent(), SLOT(showSettingsPage()));

    addAction(homeAction);
//    addAction(backAction);
//    addAction(editAction);
    addWidget(roomLabel);

    addWidget(spacer);

#ifdef QT_DEBUG
    addAction(testsAction);
#endif
    addAction(devAction);
    addAction(bluetoothAction);
//    addAction(notificationAction);
    addAction(settingsAction);
}

void StatusBar::updateRoomLabel(const QString &roomName)
{
    roomLabel->setText(roomName);
}
