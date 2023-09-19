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

    void setMoisture(int newMoisture);

private:
    int moisture = 0;

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:

};

#endif // PLANTWIDGET_H C5:8A:75:E8:11:34
