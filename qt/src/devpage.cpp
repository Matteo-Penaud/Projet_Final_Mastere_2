#include <QFile>
#include "devpage.h"
#include "localsettings.h"
#include "commons.h"

extern QString *logFileName;

DevPage::DevPage(QWidget *parent)
    : QWidget{parent}
{
    QFile inputFile(*logFileName);

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    logView = new QTextEdit(this);
    logView->setReadOnly(true);
    mainLayout->addWidget(logView);

    resetConfiguration = new QPushButton("Reset configuration", this);
    connect(resetConfiguration, &QPushButton::clicked, this, &DevPage::resetConfigurationSlot);
    mainLayout->addWidget(resetConfiguration);

    updateLogsTimer = new QTimer(this);
    updateLogsTimer->setInterval(100);
    connect(updateLogsTimer, &QTimer::timeout, this, &DevPage::updateText);

    updateLogsTimer->start();
}

void DevPage::resetConfigurationSlot()
{
    QSettings settings;
    settings.remove("");

    Q_EMIT resetConfigSignal();
}

void DevPage::updateText()
{
    QFile logFile(*logFileName);
    logFile.open(QIODevice::ReadOnly);

    QString fileContent = logFile.readAll();
    if(fileContent != logView->toPlainText())
    {
        logView->clear();
        logView->insertPlainText(fileContent);

        QScrollBar *sb = logView->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}

