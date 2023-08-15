#include "bluetoothpage.h"

BluetoothPage::BluetoothPage(QBluetoothLocalDevice *localDevice, QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(this->width()/3);
    this->setLayout(mainLayout);

    headerLabel = new QLabel("Bluetooth Manager", this);
    headerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    localAddress = new QLabel("Local address : " + localDevice->address().toString(), this);
    localAddress->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(localAddress);
}
