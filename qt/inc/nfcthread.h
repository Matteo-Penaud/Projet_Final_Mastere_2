#ifndef NFCTHREAD_H
#define NFCTHREAD_H

#include <QObject>

class NfcThread : public QObject
{
    Q_OBJECT
public:
    explicit NfcThread(QObject *parent = nullptr);

private:
    bool isNFCReading = false;

public slots:
    void doWork(void);
    void resetNfcReading(void);

signals:
    void resultReady(const QString macAddress, const QString type);
    void updateStatus(QString);
};

#endif // NFCTHREAD_H
