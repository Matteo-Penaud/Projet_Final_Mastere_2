#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QGridLayout>
#include <QList>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>

#include "roompage.h"
#include "roomaccessbutton.h"

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QStackedWidget *navigationStack, QWidget *parent = nullptr);

protected:
    QGridLayout *mainLayout;
    QList<RoomAccessButton*> widgetsList;
    QList<RoomPage*> roomsList;

    QPushButton *addWidgetButton;

    QStackedWidget *navigationStack;

signals:
    void updateRoomName(const QString &);

private slots:
    void createNewWidget(void);
};

#endif // MAINPAGE_H
