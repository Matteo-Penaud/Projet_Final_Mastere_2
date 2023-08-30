#include "roomwidget.h"
//#include "commons.h"

RoomWidget::RoomWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QGridLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(20);

    this->setLayout(mainLayout);

    statusLabel = new QLabel("No device connected");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(statusLabel);

    addModuleButton = new QPushButton("Add module", this);
    connect(addModuleButton, &QPushButton::clicked, this, &RoomWidget::addModuleSlot);

    removeModuleButton = new QPushButton("Remove module", this);

    mainLayout->addWidget(addModuleButton);
    mainLayout->addWidget(removeModuleButton);
}

QString RoomWidget::getRoomName() const
{
    return roomName;
}

void RoomWidget::setRoomName(const QString &newRoomName)
{
    roomName = newRoomName;
}

void RoomWidget::addModuleSlot()
{
    moduleMac = QInputDialog::getText(this, tr("Get Bluetooth MAC"),
                                         tr("Module MAC :"), QLineEdit::Normal,
                                         nullptr, nullptr);

    QString deviceName = QInputDialog::getText(this, tr("Get Bluetooth name"),
                                               tr("Module name :"), QLineEdit::Normal,
                                               nullptr, nullptr);

    moduleMac = "DE:EF:58:97:1A:75";
    deviceName = "BlueNRG";

    device = new BluetoohDevice(deviceName, moduleMac);
    connect(device, &BluetoohDevice::changeStatus, this, &RoomWidget::updateBluetoothStatus);
    connect(removeModuleButton, &QPushButton::clicked, device, &BluetoohDevice::disconnectFromDevice);
}

void RoomWidget::updateBluetoothStatus(QString &status)
{
    statusLabel->setText(status);
}
