#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include "commons.h"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget(QString &testName,
                        FuncPointer func,
                        QWidget *parent = nullptr);

    void lockTest(bool state);

private:
    QHBoxLayout *mainLayout;
    QPushButton *testButton;
    QString testName;

    QLabel *testLabel;
    QWidget *spacer;

    QString testResult;
    QLabel *resultLabel;

    FuncPointer func;

public slots:
    void execTest(void);

signals:
    void runTest(void);

};

#endif // TESTWIDGET_H
