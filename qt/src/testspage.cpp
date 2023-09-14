#include "testspage.h"
#include <QBluetoothLocalDevice>

TestsWrapper::TestsWrapper(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    /* BLE */
    testFunctions["Bluetooth Enable"] = (FuncPointer)&testBluetoothEnable;
    testFunctions["Bluetooth Pairing"] = (FuncPointer)&testBluetoothPairing;
    testFunctions["Bluetooth Get Data"] = (FuncPointer)&testBluetoothGetData;
    testFunctions["Bluetooth Disable"] = (FuncPointer)&testBluetoothDisable;

    /* NFC */
    testFunctions["NFC Enable"] = (FuncPointer)&testNfcEnable;
    testFunctions["NFC Read"] = (FuncPointer)&testNfcRead;
    testFunctions["NFC Disable"] = (FuncPointer)&testNfcDisable;

    /* Widgets */
    testFunctions["Room Creation"] = (FuncPointer)&testRoomCreation;
    testFunctions["Room Reorder"] = (FuncPointer)&testRoomReorder;
    testFunctions["Room Name Modification"] = (FuncPointer)&testRoomNameModification;
    testFunctions["Room Remove"] = (FuncPointer)&testRoomRemove;

    /* General */
    testFunctions["Logging"] = (FuncPointer)&testLog;
    testFunctions["Settings Saving"] = (FuncPointer)&testSettingsSaving;
    testFunctions["Settings Restoring"] = (FuncPointer)&testSettingsRestore;
    testFunctions["Settings Clearing"] = (FuncPointer)&testSettingsClear;
    testFunctions["Screen Calibration"] = (FuncPointer)&testScreenCalibration;


    foreach(QString testName, testFunctions.keys())
    {
        TestWidget *temp = new TestWidget(testName, testFunctions[testName], this);
        qDebug() << testName << testFunctions[testName];

        mainLayout->addWidget(temp);
    }
}

TestsPage::TestsPage(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);


    scrollArea = new QScrollArea(this);
    mainLayout->addWidget(scrollArea);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    wrapper = new TestsWrapper(this);
    scrollArea->setWidget(wrapper);
}

void TestsPage::resizeEvent(QResizeEvent *e)
{
    wrapper->setMinimumWidth(scrollArea->width() - 20);
}

void testBluetoothEnable(QString &result)
{
    qDebug() << "Running Bluetooth Enable Test...";
    QBluetoothLocalDevice *test = new QBluetoothLocalDevice();
    test->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    test->powerOn();

    if(test->hostMode() == QBluetoothLocalDevice::HostConnectable)
    {
        result = TEST_OK;
    }
}

void testBluetoothPairing(QString &result)
{
    qDebug() << "Running Bluetooth Pairing Test...";
}

void testBluetoothGetData(QString &result)
{
    qDebug() << "Running Bluetooth Get Data Test...";
}

void testBluetoothDisable(QString &result)
{
    qDebug() << "Running Bluetooth Disable Test...";

    QBluetoothLocalDevice *test = new QBluetoothLocalDevice();
    test->setHostMode(QBluetoothLocalDevice::HostPoweredOff);

    if(test->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
        result = TEST_OK;
    }
}

void testNfcEnable(QString &result)
{
    qDebug() << "Running NFC Enable Test...";
}

void testNfcRead(QString &result)
{
    qDebug() << "Running NFC Read Test...";
}

void testNfcDisable(QString &result)
{
    qDebug() << "Running NFC Disable Test...";
}

void testRoomCreation(QString &result)
{
    qDebug() << "Running Room Creation Test...";
}

void testRoomReorder(QString &result)
{
    qDebug() << "Running Room Reorder Test...";
}

void testRoomNameModification(QString &result)
{
    qDebug() << "Running Room Name Modification Test...";
}

void testRoomRemove(QString &result)
{
    qDebug() << "Running Room Removing Test...";
}

void testLog(QString &result)
{
    qDebug() << "Running Logging Test...";
}

void testSettingsSaving(QString &result)
{
    qDebug() << "Running Settings Saving Test...";
}

void testSettingsRestore(QString &result)
{
    qDebug() << "Running Settings Restoring Test...";
}

void testSettingsClear(QString &result)
{
    qDebug() << "Running Settings Clearing Test...";
}

void testScreenCalibration(QString &result)
{
    qDebug() << "Running Screen Calibration Test...";
}
