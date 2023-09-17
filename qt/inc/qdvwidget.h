#ifndef QDVWIDGET_H
#define QDVWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class QdvWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QdvWidget(QWidget *parent = nullptr);

    void setTemp(int newTemp);

    void setPressure(float newPressure);

private:
    int temperature = 0;
    int threshold = 20;
    int tempMax = 40;
    int tempMin = 0;

    /* Color at max temp */
    unsigned char redMax = 231;
    unsigned char greenMax = 5;
    unsigned char blueMax = 5;

    /* Color at breaking point */
    unsigned char redMedium = 34;
    unsigned char greenMedium = 221;
    unsigned char blueMedium = 136;

    /* Color at min temp */
    unsigned char redMin = 27;
    unsigned char greenMin = 160;
    unsigned char blueMin = 227;

    float pressure = 1013.2;
    double humidity = 50.0;

private slots:
    void paintEvent(QPaintEvent *e);


signals:

};

#endif // QDVWIDGET_H
