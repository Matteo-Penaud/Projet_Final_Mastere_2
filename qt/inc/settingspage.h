#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QBluetoothLocalDevice>
#include <QApplication>
#include "commons.h"

class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

private:
    QPushButton* bluetoothToggle;
    QPushButton* screenCalibrationButton;
    QPushButton* restartButton;
    QPushButton* shutdownButton;

    void getBluetoothState(void);

private slots:
    void toggleBluetooth(void);
    void screenCalibration(void);

    void shutdown(void);

};

#endif // SETTINGSPAGE_H
