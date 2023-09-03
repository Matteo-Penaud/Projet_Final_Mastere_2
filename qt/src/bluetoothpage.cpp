#include "bluetoothpage.h"
#include "commons.h"

BluetoothPage::BluetoothPage(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
}

void BluetoothPage::updateList()
{
    roomGroupsList.clear();

    delete(mainLayout);
    mainLayout = new QVBoxLayout(this);

    QSettings settings;

    settings.beginGroup(SETTINGS_GROUP_ROOMS);
    QStringList roomsId = settings.childKeys();
    roomsId.sort();
    QStringList rooms;
    foreach(const QString &id, roomsId)
    {
        rooms.append(settings.value(id).toString());
    }
    settings.endGroup();

    foreach(const QString &room, rooms)
    {
        settings.beginGroup(room);
        QGroupBox *roomGroup = new QGroupBox(settings.value(SETTINGS_ROOMS_NAME).toString());

        roomGroupsList.append(roomGroup);
        updateGroup(settings, roomGroup);
        settings.endGroup();
    }

    foreach(QGroupBox *room, roomGroupsList)
    {
        mainLayout->addWidget(room);
    }
}

void BluetoothPage::updateGroup(QSettings &settings, QGroupBox *group)
{

    settings.beginGroup(SETTINGS_DEVICES_GROUP);

    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    groupLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    group->setLayout(groupLayout);

    group->setTitle(group->title() + QString(" : %1 device(s) connected").arg(settings.childGroups().length()));

    foreach(QString device, settings.childGroups())
    {
        settings.beginGroup(device);
        groupLayout->addWidget(new QLabel(
            QString("Device %1 :"
                    "\n\tname : %2"
                    "\n\tService UUID : %3"
                    "\n\tCharacteristic UUID : %4").arg(
                device,
                settings.value("name").toString(),
                settings.value("service").toString(),
                settings.value("characteristic").toString()
                )
            ));
        settings.endGroup();
    }

    settings.endGroup();
}

