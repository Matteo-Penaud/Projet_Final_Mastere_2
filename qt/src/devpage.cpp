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
    mainLayout->addWidget(logView);

    resetConfiguration = new QPushButton("Reset configuration", this);
    connect(resetConfiguration, &QPushButton::clicked, this, &DevPage::resetConfigurationSlot);
    mainLayout->addWidget(resetConfiguration);
}

void DevPage::resetConfigurationSlot()
{
    QSettings settings;
    settings.remove("");
}
