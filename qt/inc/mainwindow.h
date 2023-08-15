#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qbluetoothlocaldevice.h>

#include <QLabel>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTime>
#include <QTimer>

#include "bluetoothpage.h"
#include "mainpage.h"
#include "settingspage.h"
#include "statusbar.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

#define CURRENT_TIME QTime::currentTime().toString(QString("hh:mm"))

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStackedWidget* getNavigationStack(void);

protected:
    QLabel* timeLabel;
    QTimer* timeUpdate;

    QStackedWidget* navigationStack;

    BluetoothPage *bluetoothPage;
    MainPage* mainPage;
    SettingsPage* settingsPage;
    StatusBar* statusBar;

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;

private slots:
    void updateTimeCallback(void);

public slots:
    void showBluetoothManager(void);
    void showSettings(void);
    void showMainPage(void);

};
#endif // MAINWINDOW_H
