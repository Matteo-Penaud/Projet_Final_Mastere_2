#include "testspage.h"
#include <QFile>
#include <QBluetoothLocalDevice>
#include "MFRC522.h"
#include "localsettings.h"
#include <bluetoohdevice.h>

TestsWrapper::TestsWrapper(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    /* BLE */
    testFunctions["Bluetooth Enable"] = (FuncPointer)&testBluetoothEnable;
    testFunctions["Bluetooth Disable"] = (FuncPointer)&testBluetoothDisable;

    /* NFC */
    testFunctions["NFC Enable"] = (FuncPointer)&testNfcEnable;

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
        testsList.append(temp);
        qDebug() << testName << testFunctions[testName];

        mainLayout->addWidget(temp);
    }
}

QList<TestWidget *> TestsWrapper::getTestsList() const
{
    return testsList;
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

    runAll = new QPushButton("Run all tests", this);
    connect(runAll, &QPushButton::clicked, this, &TestsPage::runAllTests);
    mainLayout->addWidget(runAll);
}

void TestsPage::resizeEvent(QResizeEvent *e)
{
    wrapper->setMinimumWidth(scrollArea->width() - 20);
}

void TestsPage::runAllTests()
{
    qDebug() << "Running all tests ...";

    foreach(TestWidget *test, wrapper->getTestsList())
    {
        test->lockTest(true);
    }

    foreach(TestWidget *test, wrapper->getTestsList())
    {
        test->execTest();
    }

    foreach(TestWidget *test, wrapper->getTestsList())
    {
        test->lockTest(false);
    }
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

    MFRC522 *nfc_handler = new MFRC522(new CommSPI());
    nfc_handler->PCD_Init();
    byte v = nfc_handler->PCD_ReadRegister(MFRC522::VersionReg);

    if(v != 0xFF && v != 0x00)
    {
        result = TEST_OK;
    }
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

    if(QFile::exists(*logFileName))
    {
        result = TEST_OK;
    }
}

void testSettingsSaving(QString &result)
{
    qDebug() << "Running Settings Saving Test...";

    QSettings settings;

    if(settings.isWritable())
    {
        result = TEST_OK;
    }
}

void testSettingsRestore(QString &result)
{
    qDebug() << "Running Settings Restoring Test...";

    QSettings settings;

    settings.beginGroup("TESTS");
    settings.setValue("get", "true");

    if(settings.value("get") == "true")
    {
        result = TEST_OK;
    }
    settings.endGroup();
}

void testSettingsClear(QString &result)
{
    qDebug() << "Running Settings Clearing Test...";

    QSettings settings;

    settings.beginGroup("TESTS");
    settings.setValue("dummy", "dummy");
    settings.endGroup();

    settings.remove("TESTS");

    if(!settings.childGroups().contains("TESTS"))
    {
        result = TEST_OK;
    }
}

void testScreenCalibration(QString &result)
{
    qDebug() << "Running Screen Calibration Test...";
}
