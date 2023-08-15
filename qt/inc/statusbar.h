#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QAction>
#include <QWidget>
#include <QToolBar>

#include "commons.h"

#define IS_MOVABLE false

class StatusBar : public QToolBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

protected:
    QWidget* spacer;

private:
    QAction* homeAction;
    QAction* energyAction;
    QAction* bluetoothAction;
    QAction* notificationAction;
    QAction* settingsAction;

signals:

};

#endif // STATUSBAR_H
