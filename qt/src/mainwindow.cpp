#include "commons.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    timeUpdate = new QTimer(this);
    timeLabel = new QLabel(this);

    mainPage = new MainPage(this);
    statusBar = new StatusBar(this);

    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

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

    this->setCentralWidget(mainPage);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateTimeCallback()
{
    timeLabel->setText(CURRENT_TIME);
}

