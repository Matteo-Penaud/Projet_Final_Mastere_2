#include "settingspage.h"

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(this->width()/3);
    this->setLayout(mainLayout);

    bluetoothToggle = new QPushButton(this);
    getBluetoothState();
    connect(bluetoothToggle, &QPushButton::clicked, this, &SettingsPage::toggleBluetooth);

    mainLayout->addWidget(bluetoothToggle);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(spacer);

    shutdownButton = new QPushButton("Shutdown", this);
    shutdownButton->connect(shutdownButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    mainLayout->addWidget(shutdownButton);
}

void SettingsPage::getBluetoothState()
{
    QBluetoothLocalDevice *BLE = new QBluetoothLocalDevice();
    if(BLE->hostMode() == QBluetoothLocalDevice::HostConnectable)
    {
        bluetoothToggle->setText("Disable Bluetooth");
    }
    else if(BLE->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
        bluetoothToggle->setText("Enable Bluetooth");
    }
    else
    {
        bluetoothToggle->setText("Bluetooth Error");
        bluetoothToggle->setEnabled(false);
    }
}

void SettingsPage::toggleBluetooth()
{
    QBluetoothLocalDevice *test = new QBluetoothLocalDevice();

    if(test->hostMode() == QBluetoothLocalDevice::HostConnectable)
    {
        test->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    }
    else
    {
        test->powerOn();
    }

    getBluetoothState();
}
