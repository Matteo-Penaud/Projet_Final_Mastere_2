#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QProxyStyle>
#include "commons.h"
#include "stdio.h"

QString *logFileName;

void logMessageReceived(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        txt = QString("%2 Debug: %1").arg(msg, CURRENT_TIME_LOG);
        fprintf(stderr, "%s Debug: %s (%s:%u, %s)\n", CURRENT_TIME_LOG, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        txt = QString("%2 Info: %1").arg(msg, CURRENT_TIME_LOG);
        fprintf(stderr, "%s Info: %s (%s:%u, %s)\n", CURRENT_TIME_LOG, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        txt = QString("%2 Warning: %1").arg(msg, CURRENT_TIME_LOG);
        fprintf(stderr, "%s Warning: %s (%s:%u, %s)\n", CURRENT_TIME_LOG, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        txt = QString("%2 Critical: %1").arg(msg, CURRENT_TIME_LOG);
        fprintf(stderr, "%s Critical: %s (%s:%u, %s)\n", CURRENT_TIME_LOG, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        txt = QString("%2 Fatal: %1").arg(msg, CURRENT_TIME_LOG);
        fprintf(stderr, "%s Fatal: %s (%s:%u, %s)\n", CURRENT_TIME_LOG, localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
    QFile outFile(*logFileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << Qt::endl;
}


int main(int argc, char *argv[])
{
    popen("killall xinput_calibrator", "r");

    QCoreApplication::setOrganizationName(ORGANISATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANISATION_DOMAINE);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QIcon::setThemeName("fontawesome");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    a.setCursorFlashTime(0);

#ifdef __arm__
    QCursor cursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);
#endif

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qInstallMessageHandler(logMessageReceived);

    logFileName = new QString(QDateTime::currentDateTime().toString(QString("yyyy-MM-dd--hh:mm:ss")) + "_logs.txt");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Projet_Master_Qt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
