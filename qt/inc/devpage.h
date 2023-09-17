#ifndef DEVPAGE_H
#define DEVPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QScrollBar>

class DevPage : public QWidget
{
    Q_OBJECT
public:
    explicit DevPage(QWidget *parent = nullptr);

private:
    QTextEdit *logView;
    QVBoxLayout *mainLayout;
    QPushButton *resetConfiguration;
    QTimer *updateLogsTimer;

private slots:
    void resetConfigurationSlot(void);
    void updateText(void);

signals:

};

#endif // DEVPAGE_H
