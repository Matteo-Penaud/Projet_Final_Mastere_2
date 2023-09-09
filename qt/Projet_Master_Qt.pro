QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core bluetooth widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bluetoohdevice.cpp \
    src/bluetoohserviceinfo.cpp \
    src/bluetoothdeviceinfo.cpp \
    src/bluetoothpage.cpp \
    src/characteristicinfo.cpp \
    src/devpage.cpp \
    src/main.cpp \
    src/mainpage.cpp \
    src/mainwindow.cpp \
    src/roomaccessbutton.cpp \
    src/roompage.cpp \
    src/roomwidget.cpp \
    src/settingspage.cpp \
    src/statusbar.cpp \
    src/nfc/CommI2C.cpp \
    src/nfc/CommSPI.cpp \
    src/nfc/CommUART.cpp \
    src/nfc/MFRC522.cpp \

INCLUDEPATH += \
    inc/ \
    inc/nfc/

HEADERS += \
    inc/bluetoohdevice.h \
    inc/bluetoohserviceinfo.h \
    inc/bluetoothdeviceinfo.h \
    inc/bluetoothpage.h \
    inc/characteristicinfo.h \
    inc/commons.h \
    inc/devpage.h \
    inc/localsettings.h \
    inc/mainpage.h \
    inc/mainwindow.h \
    inc/roomwidget.h \
    inc/settingspage.h \
    inc/statusbar.h \
    inc/roomaccessbutton.h \
    inc/roompage.h \
    inc/nfc/Comm.h \
    inc/nfc/MFRC522.h \

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
