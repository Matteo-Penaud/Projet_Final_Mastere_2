#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "commons.h"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget(QString &testName,
                        FuncPointer func,
                        QWidget *parent = nullptr);

private:
    QHBoxLayout *mainLayout;
    QPushButton *testButton;
    QString testName;

    QLabel *testLabel;
    QWidget *spacer;

    QString testResult;

    FuncPointer func;

private slots:
    void execTest(void);

signals:


};

#endif // TESTWIDGET_H
