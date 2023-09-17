#ifndef PLANTWIDGET_H
#define PLANTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class PlantWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlantWidget(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:

};

#endif // PLANTWIDGET_H
