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

#define TEST_OK "TEST_OK"
#define TEST_KO "TEST_KO"

extern bool isNfcActive;

extern QString *logFileName;
typedef void (*FuncPointer)(QString&);

/* BLE */
void testBluetoothEnable(QString &result);
void testBluetoothPairing(QString &result);
void testBluetoothGetData(QString &result);
void testBluetoothDisable(QString &result);

/* NFC */
void testNfcEnable(QString &result);
void testNfcRead(QString &result);
void testNfcDisable(QString &result);

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
