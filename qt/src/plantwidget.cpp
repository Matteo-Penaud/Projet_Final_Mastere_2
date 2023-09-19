#include "plantwidget.h"
#include "commons.h"

PlantWidget::PlantWidget(QWidget *parent)
    : QWidget{parent}
{

}

void PlantWidget::setMoisture(int newMoisture)
{
    moisture = newMoisture;
    update();
}

void PlantWidget::resizeEvent(QResizeEvent *e)
{
    update();
}

void PlantWidget::paintEvent(QPaintEvent *e)
{
    qDebug() << size();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    unsigned char red, green, blue;

//    QPen pen;
//    pen.setWidth(4);
//    pen.setColor(QColor(8, 40, 46));
//    painter.setPen(pen);

    QPen pen;
    pen.setWidth(10);
    pen.setColor(QColor(98, 218, 81));

    painter.setPen(pen);

//    painter.setBrush(QBrush(QColor(98, 218, 81)));

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

    int pixmap_size = 24;

    painter.drawEllipse(origin_x, origin_y, r, r);

    QPixmap leaf(":/icons/fontawesome/solid/leaf.svg");
    painter.drawPixmap(origin_x + (r/2) - (pixmap_size/2), origin_y + r - pixmap_size*2, pixmap_size, pixmap_size, leaf);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(26);
    painter.setFont(font);

    pen.setColor(QColor(8, 40, 46));
    painter.setPen(pen);

    QString moistureText;
    moistureText.sprintf("%.0f%", ((float)moisture / 1400) * 100);
    painter.drawText(QRect(origin_x, origin_y, r, r/2), Qt::AlignHCenter | Qt::AlignBottom, moistureText);

    font.setBold(false);
    font.setPointSize(15);
    painter.setFont(font);
    painter.drawText(QRect(origin_x, origin_y+(r/5), r, r/2), Qt::AlignHCenter | Qt::AlignBottom, "Good");

    painter.end();
}
