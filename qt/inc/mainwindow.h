#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qbluetoothlocaldevice.h>

#include <QLabel>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTime>
#include <QTimer>
#include <QCloseEvent>

#include "mainpage.h"
#include "settingspage.h"
#include "bluetoothpage.h"
#include "statusbar.h"
#include "devpage.h"
#include "testspage.h"

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

    MainPage* mainPage;
    BluetoothPage* bluetoothPage;
    SettingsPage* settingsPage;
    DevPage* devPage;
    TestsPage* testsPage;
    StatusBar* statusBar;

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;

    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent *event);

private slots:
    void updateTimeCallback(void);

public slots:
    void showSettingsPage(void);
    void showBluetoothManager(void);
    void showMainPage(void);
    void showDevPage(void);
    void showTestsPage(void);
    void resetConfig(void);

};
#endif // MAINWINDOW_H
