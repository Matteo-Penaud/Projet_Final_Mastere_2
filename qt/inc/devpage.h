#ifndef DEVPAGE_H
#define DEVPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

class DevPage : public QWidget
{
    Q_OBJECT
public:
    explicit DevPage(QWidget *parent = nullptr);

private:
    QTextEdit *logView;
    QVBoxLayout *mainLayout;
    QPushButton *resetConfiguration;

private slots:
    void resetConfigurationSlot(void);

signals:

};

#endif // DEVPAGE_H
