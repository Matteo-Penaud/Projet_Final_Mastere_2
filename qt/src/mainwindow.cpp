#include "mainwindow.h"
#include "commons.h"

#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), localDevice(new QBluetoothLocalDevice)
{
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

#ifdef __arm__

    setGeometry(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setWindowFlag(Qt::FramelessWindowHint);
//    this->setWindowState(Qt::FramelessWindowHint);
#endif

    timeUpdate = new QTimer(this);
    timeLabel = new QLabel(this);

    navigationStack = new QStackedWidget(this);
    navigationStack->setStyleSheet("background-color: white");

    /* Pages creation */
    mainPage = new MainPage(navigationStack, this);
    mainPage->setStyleSheet("background-color: white");

    bluetoothPage = new BluetoothPage(this);
    bluetoothPage->setStyleSheet("background-color: white");

    settingsPage = new SettingsPage(this);
    settingsPage->setStyleSheet("background-color: white");

    devPage = new DevPage(this);
    devPage->setStyleSheet("background-color: white");

    testsPage = new TestsPage(this);
    testsPage->setStyleSheet("background-color: white");

    statusBar = new StatusBar(this);
    statusBar->setStyleSheet("background-color: white");

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    this->addToolBar(statusBar);

    timeUpdate->setInterval(500);
    connect(timeUpdate, &QTimer::timeout, this, &MainWindow::updateTimeCallback);
    timeUpdate->start();

    timeLabel->setText("hh:mm");
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timeLabel->setGeometry(0.45f*SCREEN_WIDTH, 0, 0, 0);
    timeLabel->setFixedWidth(SCREEN_WIDTH/10);
    timeLabel->setFixedHeight(statusBar->height()+10);
    timeLabel->raise();

    navigationStack->addWidget(mainPage);
    navigationStack->addWidget(bluetoothPage);
    navigationStack->addWidget(settingsPage);
    navigationStack->addWidget(devPage);
    navigationStack->addWidget(testsPage);
    this->showMainPage();
    this->setCentralWidget(navigationStack);

    connect(mainPage, &MainPage::updateRoomName, statusBar, &StatusBar::updateRoomLabel);
}

MainWindow::~MainWindow()
{
    delete discoveryAgent;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
    event->accept();
}

QStackedWidget* MainWindow::getNavigationStack()
{
    return navigationStack;
}

void MainWindow::updateTimeCallback()
{
    timeLabel->setText(CURRENT_TIME);
}

void MainWindow::showSettingsPage()
{
    navigationStack->setCurrentWidget(settingsPage);
}

void MainWindow::showBluetoothManager()
{
    bluetoothPage->updateList();
    navigationStack->setCurrentWidget(bluetoothPage);
}

void MainWindow::showMainPage()
{
    navigationStack->setCurrentWidget(mainPage);
}

void MainWindow::showDevPage()
{
    navigationStack->setCurrentWidget(devPage);
}

void MainWindow::showTestsPage()
{
    navigationStack->setCurrentWidget(testsPage);
}

void MainWindow::writeSettings()
{

}

void MainWindow::readSettings()
{
//    LOCAL_SETTINGS

//    settings.beginGroup("MainWindow");
//    settings.endGroup();
}
