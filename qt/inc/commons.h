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

extern QString *logFileName;

#endif // COMMONS_H
