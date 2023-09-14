#ifndef TESTSPAGE_H
#define TESTSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMap>
#include "testwidget.h"
#include "commons.h"

class TestsWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit TestsWrapper(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;

    QList<TestWidget *> testsList;
    QMap<QString, FuncPointer> testFunctions;

signals:

};

class TestsPage : public QWidget
{
    Q_OBJECT
public:
    explicit TestsPage(QWidget *parent = nullptr);

private:
    QScrollArea *scrollArea;
    QVBoxLayout *mainLayout;
    TestsWrapper *wrapper;



private slots:
    void resizeEvent(QResizeEvent *);

signals:

};

#endif // TESTSPAGE_H
