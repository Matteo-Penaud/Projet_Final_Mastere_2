#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QGridLayout>
#include <QList>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>

#include "roomwidget.h"
#include "roomaccessbutton.h"

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QStackedWidget *navigationStack, QWidget *parent = nullptr);

protected:
    QGridLayout *mainLayout;
    QList<RoomAccessButton*> widgetsList;
    QList<RoomWidget*> roomsList;

    QPushButton *addWidgetButton;

    QStackedWidget *navigationStack;

signals:

private slots:
    void createNewWidget(void);
    void switchRoom(RoomWidget *room);
};

#endif // MAINPAGE_H
