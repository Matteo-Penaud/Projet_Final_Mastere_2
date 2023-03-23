#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class SettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

private:
    QPushButton* test;

signals:

};

#endif // SETTINGSPAGE_H
