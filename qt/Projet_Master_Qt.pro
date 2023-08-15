QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core bluetooth widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bluetoothpage.cpp \
    src/main.cpp \
    src/mainpage.cpp \
    src/mainwindow.cpp \
    src/roomaccessbutton.cpp \
    src/roomwidget.cpp \
    src/settingsmanager.cpp \
    src/settingspage.cpp \
    src/statusbar.cpp

INCLUDEPATH += \
    inc/

HEADERS += \
    inc/bluetoothpage.h \
    inc/commons.h \
    inc/mainpage.h \
    inc/mainwindow.h \
    inc/roomwidget.h \
    inc/settingspage.h \
    inc/statusbar.h \
    inc/settingsmanager.h \
    inc/roomaccessbutton.h

TRANSLATIONS += \
    Projet_Master_Qt_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS +=
