#include "qdvwidget.h"
#include "commons.h"
#include "math.h"

QdvWidget::QdvWidget(QWidget *parent)
    : QWidget{parent}
{

}

QdvWidget::~QdvWidget()
{

}

void QdvWidget::setTemp(int newTemp)
{
    temperature = newTemp;
    update();
}

void QdvWidget::setPressure(float newPressure)
{
    pressure = newPressure;
    update();
}

void QdvWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    unsigned char red, green, blue;

    if(temperature >= tempMax)
    {
        red = redMax;
        green = greenMax;
        blue = blueMax;
    }
    else if(temperature <= tempMin)
    {
        red = redMin;
        green = greenMin;
        blue = blueMin;
    }
    else if(temperature > threshold)
    {
        red = redMedium + (redMax - redMedium) * ((float)(temperature - threshold) / (tempMax - threshold));
        green = greenMedium + (greenMax - greenMedium) * ((float)(temperature - threshold) / (tempMax - threshold));
        blue = blueMedium + (blueMax - blueMedium) * ((float)(temperature - threshold) / (tempMax - threshold));
    }
    else
    {
        red = redMin + (redMedium - redMin) * ((float)temperature/threshold);
        green = greenMin + (greenMedium - greenMin) * ((float)temperature/threshold);
        blue = blueMin + (blueMedium - blueMin) * ((float)temperature/threshold);
    }

    QPen pen;
    pen.setWidth(10);
    pen.setColor(QColor(red, green, blue));

    painter.setPen(pen);

    QSize taille = size();
    int r;
    if(taille.width() > taille.height())
    {
        r = height() - 10;
    }
    else
    {
        r = width() - 10;
    }
    int origin_x = (width() - r)/ 2;
    int origin_y = (height() - r)/ 2;

    painter.drawEllipse(origin_x, origin_y, r, r);

    int pixmap_size = 24;
    QPixmap leaf(":/icons/fontawesome/solid/cloud-sun.svg");
    painter.drawPixmap(origin_x + (r/2) - (pixmap_size/2), origin_y + r - pixmap_size*2, pixmap_size, pixmap_size, leaf);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(26);
    painter.setFont(font);

    pen.setColor(QColor(8, 40, 46));
    painter.setPen(pen);

    QString tempText = QString("%1°C").arg(QString::number(temperature));
    painter.drawText(QRect(origin_x, origin_y, r, r/2), Qt::AlignHCenter | Qt::AlignBottom, tempText);

    font.setBold(false);
    font.setPointSize(15);
    painter.setFont(font);

    QString pressText = QString("%1 hPa").arg(QString::number(pressure));
    painter.drawText(QRect(origin_x, origin_y+r/2, r, r/2), Qt::AlignHCenter | Qt::AlignTop, pressText);


    double humidite_relative = 0.5; //valeur qu'on admet

    double Pvs = 6.1078 * exp((7.5 * temperature) / (237.3 + temperature));
    double Pv = humidite_relative * Pvs;
    humidity = (Pv / pressure) * 10000.0; //VALEUR HUMIDITE DANS L'AIR
    QString humText;
    humText.sprintf("%.2f%", humidity/1.5);
    painter.drawText(QRect(origin_x, origin_y+((2*r)/3), r, r/3), Qt::AlignHCenter | Qt::AlignTop, humText);

    painter.end();
}

