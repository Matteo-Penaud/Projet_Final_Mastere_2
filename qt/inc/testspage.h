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

    QList<TestWidget *> getTestsList() const;

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
    QPushButton *runAll;

private slots:
    void resizeEvent(QResizeEvent *);
    void runAllTests(void);

signals:

};

#endif // TESTSPAGE_H
