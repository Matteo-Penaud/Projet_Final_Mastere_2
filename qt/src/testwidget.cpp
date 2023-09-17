#include "testwidget.h"

TestWidget::TestWidget(QString &testName, FuncPointer func, QWidget *parent)
    : QWidget{parent}, func(func), testName(testName)
{
    mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    testLabel = new QLabel(testName);
    mainLayout->addWidget(testLabel);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(spacer);

    testButton = new QPushButton("Run");
    connect(testButton, &QPushButton::clicked, this, &TestWidget::execTest);
    mainLayout->addWidget(testButton);

    resultLabel = new QLabel("N/A");
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setMinimumWidth(150);
    mainLayout->addWidget(resultLabel);

    testResult = TEST_KO;

    connect(this, &TestWidget::runTest, this, &TestWidget::execTest);
}

void TestWidget::lockTest(bool state)
{
    testButton->setEnabled(!state);
}

void TestWidget::execTest()
{
    func(testResult);
    qDebug() << testName << testResult;

    if(testResult == TEST_OK)
    {
        resultLabel->setText("Test succeeded");
        resultLabel->setStyleSheet("color: green");
    }
    else
    {
        resultLabel->setText("Test failed");
        resultLabel->setStyleSheet("color: red");
    }
}
