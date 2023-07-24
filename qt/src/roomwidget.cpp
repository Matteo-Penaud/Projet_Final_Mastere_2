#include "roomwidget.h"
#include "commons.h"

RoomWidget::RoomWidget(int id, QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QGridLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);

    this->setLayout(mainLayout);

    testLabel = new QLabel("ROOM" + QString::number(id), this);
    testLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(testLabel);

}
