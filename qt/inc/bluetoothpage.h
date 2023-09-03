#ifndef BLUETOOTHPAGE_H
#define BLUETOOTHPAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include "localsettings.h"

class BluetoothPage : public QWidget
{
    Q_OBJECT
public:
    explicit BluetoothPage(QWidget *parent = nullptr);

    void updateList(void);
    void updateGroup(QSettings &settings, QGroupBox *group);

private:
    QVBoxLayout *mainLayout;
    QList<QGroupBox *> roomGroupsList;

signals:

};

#endif // BLUETOOTHPAGE_H
