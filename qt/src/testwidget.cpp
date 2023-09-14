#include "testwidget.h"

TestWidget::TestWidget(QString &testName, FuncPointer func, QWidget *parent)
    : QWidget{parent}, func(func), testName(testName)
{
    mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    testLabel = new QLabel(testName);
    mainLayout->addWidget(testLabel);

    testButton = new QPushButton("Run");
    connect(testButton, &QPushButton::clicked, this, &TestWidget::execTest);
    mainLayout->addWidget(testButton);

    testResult = TEST_KO;
}

void TestWidget::execTest()
{
    func(testResult);
    qDebug() << testName << testResult;
}
