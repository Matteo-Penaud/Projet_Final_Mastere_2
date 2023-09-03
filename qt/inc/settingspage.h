#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

#include <QApplication>
#include "commons.h"

class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

private:
    QPushButton* shutdownButton;

private slots:


};

#endif // SETTINGSPAGE_H
