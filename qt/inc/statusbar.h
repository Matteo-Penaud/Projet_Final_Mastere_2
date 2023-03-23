#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QToolBar>

#define IS_MOVABLE false

class StatusBar : public QToolBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

protected:
    QWidget* spacer;

signals:

};

#endif // STATUSBAR_H
