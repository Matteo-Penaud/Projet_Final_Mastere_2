#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QGridLayout>
#include <QList>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QCloseEvent>

#include "roompage.h"
#include "roomaccessbutton.h"

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QStackedWidget *navigationStack, QWidget *parent = nullptr);

private:
    QGridLayout *mainLayout;
    QList<RoomAccessButton*> widgetsList;
    QList<RoomPage*> roomsList;
    QLabel *emptyRooms;

    QPushButton *addWidgetButton;

    QStackedWidget *navigationStack;

    void readSettings();

signals:
    void updateRoomName(const QString &);

private slots:
    void createNewWidget(const QString &roomName = nullptr);
};

#endif // MAINPAGE_H
