#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>


class RoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoomWidget(int id, QWidget *parent = nullptr);

private:
    QGridLayout* mainLayout;
    QLabel* testLabel;

    QString roomName;

signals:

};

#endif // ROOMWIDGET_H
