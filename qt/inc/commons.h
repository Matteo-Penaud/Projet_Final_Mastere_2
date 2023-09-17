#ifndef COMMONS_H
#define COMMONS_H

#include <QDebug>
#include <QString>

#define SCREEN_HEIGHT   480UL
#define SCREEN_WIDTH    800UL

#define ORGANISATION_NAME    "WatiCorp"
#define ORGANISATION_DOMAINE "waticorp.com"
#define APPLICATION_NAME     "WatiHouse"

#define DEBUG_OUT(s) (qDebug() << (s))
#define CURRENT_TIME_LOG QDateTime::currentDateTime().toString(QString("[yyyy-MM-dd--hh:mm:ss]")).toLocal8Bit().constData()

#define TEST_OK "TEST_OK"
#define TEST_KO "TEST_KO"

extern bool isNfcActive;

extern QString *logFileName;
typedef void (*FuncPointer)(QString&);

/* BLE */
void testBluetoothEnable(QString &result);
void testBluetoothDisable(QString &result);

/* NFC */
void testNfcEnable(QString &result);

/* Widgets */
void testRoomCreation(QString &result);
void testRoomReorder(QString &result);
void testRoomNameModification(QString &result);
void testRoomRemove(QString &result);

/* General */
void testLog(QString &result);
void testSettingsSaving(QString &result);
void testSettingsRestore(QString &result);
void testSettingsClear(QString &result);
void testScreenCalibration(QString &result);

#endif // COMMONS_H
