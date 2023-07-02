#include "commons.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    timeUpdate = new QTimer(this);
    timeLabel = new QLabel(this);

    navigationStack = new QStackedWidget(this);

    /* Pages creation */
    mainPage = new MainPage(navigationStack);
    settingsPage = new SettingsPage(navigationStack);

    statusBar = new StatusBar(this);

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
    navigationStack->addWidget(settingsPage);
    this->showMainPage();
    this->setCentralWidget(navigationStack);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateTimeCallback()
{
    timeLabel->setText(CURRENT_TIME);
}

void MainWindow::showSettings()
{
    navigationStack->setCurrentWidget(settingsPage);
}

void MainWindow::showMainPage()
{
    navigationStack->setCurrentWidget(mainPage);
}

