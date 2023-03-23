#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <random>

class RoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoomWidget(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent* event);

signals:

};

#endif // ROOMWIDGET_H
