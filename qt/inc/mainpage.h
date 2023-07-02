#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QGridLayout>
#include <QList>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

#include "roomwidget.h"
#include "commons.h"

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

protected:
    QGridLayout* mainLayout;
    QList<QWidget*> widgetsList;

    QPushButton* addWidgetButton;

signals:

private slots:
    void createNewWidget(void);

};

#endif // MAINPAGE_H
