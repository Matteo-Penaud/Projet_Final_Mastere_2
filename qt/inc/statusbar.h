#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QAction>
#include <QWidget>
#include <QToolBar>
#include <QLabel>

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
    //left part
    QAction* homeAction;
    QAction* backAction;
    QAction* editAction;

    //right part
    QAction* devAction;
    QAction* bluetoothAction;
    QAction* notificationAction;
    QAction* settingsAction;

    QLabel* roomLabel;

public slots:
    void updateRoomLabel(const QString &roomName);


};

#endif // STATUSBAR_H
