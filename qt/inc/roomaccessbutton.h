#ifndef ROOMACCESSBUTTON_H
#define ROOMACCESSBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QDateTime>
#include <QVBoxLayout>
#include "roompage.h"

class RoomAccessButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RoomAccessButton(RoomPage *room, QWidget *parent = nullptr);

    RoomPage *getRoom() const;
    void setRoom(RoomPage *newRoom);

    quint64 mLastPressTime=0;
    static const quint64 MY_LONG_PRESS_THRESHOLD=500;


private:
    RoomPage *room;
    QVBoxLayout *mainLayout;

    QLabel *roomName;

private slots:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void onLongPressed(void);

public slots:
    void setRoomName(QString newRoomName);

signals:
    void longPressEvent();

};

#endif // ROOMACCESSBUTTON_H
