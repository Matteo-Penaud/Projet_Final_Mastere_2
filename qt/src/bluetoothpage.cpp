#include "bluetoothpage.h"
#include "commons.h"

BluetoothPage::BluetoothPage(QBluetoothLocalDevice *localDevice, QWidget *parent)
    : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->setMargin(this->width()/3);
    this->setLayout(mainLayout);

    headerLabel = new QLabel("Bluetooth Manager", this);
    headerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    localAddress = new QLabel("Local address : " + localDevice->address().toString(), this);
    localAddress->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    subscribersList = new QListWidget(this);

    restartServerButton = new QPushButton("Restart server", this);

    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(localAddress);
    mainLayout->addWidget(subscribersList);
    mainLayout->addWidget(restartServerButton);

    bluetoothServer = new BluetoothServer(this);
    connect(restartServerButton, &QPushButton::clicked, bluetoothServer, &BluetoothServer::restartServer);
    connect(bluetoothServer, QOverload<const QString &>::of(&BluetoothServer::clientConnected),
            this, &BluetoothPage::clientConnected);
    connect(bluetoothServer, QOverload<const QString &>::of(&BluetoothServer::clientDisconnected),
            this,  QOverload<const QString &>::of(&BluetoothPage::clientDisconnected));
    connect(bluetoothServer, &BluetoothServer::messageReceived,
            this,  &BluetoothPage::showMessage);
    bluetoothServer->startServer();
}

BluetoothPage::~BluetoothPage()
{
    delete bluetoothServer;
}

void BluetoothPage::clientConnected(const QString &name)
{
    subscribersList->addItem(name);
    DEBUG_OUT(name + " is connected.");
}

void BluetoothPage::clientDisconnected(const QString &name)
{
    foreach (QListWidgetItem *item, subscribersList->findItems(name, Qt::MatchContains)) {
        delete item;
    }
    DEBUG_OUT(name + " is disconnected.");
}

void BluetoothPage::showMessage(const QString &sender, const QString &message)
{
    DEBUG_OUT(sender + " : " + message);
}

