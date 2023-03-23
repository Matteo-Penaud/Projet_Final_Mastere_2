#include "roomwidget.h"

#include "commons.h"

RoomWidget::RoomWidget(QWidget *parent)
    : QWidget{parent}
{
}

void RoomWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    uint16_t margin = 100;

    uint16_t correctWidth = (uint16_t)this->width() - margin*2;
    uint16_t correctHeight = (uint16_t)this->height() - margin*2;

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QBrush(QColor(Qt::black)), 5));

    painter.fillRect(0, 0, this->width(), this->height(), QBrush(QColor(rand()%255, rand()%255, rand()%255)));

    if(correctWidth > correctHeight)
    {
        uint16_t offset = ((correctWidth - correctHeight) / 2) + margin;

        painter.drawEllipse(offset, margin, correctHeight, correctHeight);
    }
    else
    {
        uint16_t offset = ((correctHeight - correctWidth) / 2) + margin;

        painter.drawEllipse(margin, offset, correctWidth, correctWidth);
    }
}
