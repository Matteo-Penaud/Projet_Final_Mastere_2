#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTime>
#include <QTimer>

#include "mainpage.h"
#include "settingspage.h"
#include "statusbar.h"

#define CURRENT_TIME QTime::currentTime().toString(QString("hh:mm"))

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QLabel* timeLabel;
    QTimer* timeUpdate;

    QStackedWidget* navigationStack;

    MainPage* mainPage;
    SettingsPage* settingsPage;
    StatusBar* statusBar;

private slots:
    void updateTimeCallback(void);

public slots:
    void showSettings(void);
    void showMainPage(void);

};
#endif // MAINWINDOW_H
