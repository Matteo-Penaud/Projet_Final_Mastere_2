#include "nfcthread.h"
#include "MFRC522.h"
#include <unistd.h>
#include <QTimer>
#include "commons.h"

NfcThread::NfcThread(QObject *parent)
    : QObject{parent}
{

}

void NfcThread::doWork()
{
    QString macAddress;
    MFRC522 *nfc_handler = new MFRC522(new CommSPI());
    nfc_handler->PCD_Init();
    nfc_handler->PCD_DumpVersionToSerial();

    qInfo() << "NFC Seeking tag ...";

    QTimer::singleShot(15000, this, &NfcThread::resetNfcReading);

    isNFCReading = true;

    emit updateStatus("NFC Quick Pairing :\nSeeking NFC tag...");

    printf("\nScan PICC to see UID, SAK, type, and data blocks...\n");
    while(isNFCReading)
    {
        MFRC522::StatusCode status;
        byte byteCount;
        byte buffer[18];
        byte i;


        usleep(1000);

        // Look for new cards
        if (!nfc_handler->PICC_IsNewCardPresent())
        {
            continue;
        }

        // Select one of the cards
        if (!nfc_handler->PICC_ReadCardSerial())
        {
            continue;
        }

        qInfo() << nfc_handler->uid.sak;

        if (nfc_handler->uid.sak == 0)
        {
            qDebug() << "Reading NFC";

            QString test;
            QString temp;
            QString tempMac;

            for(byte page = 0; page < 16; page += 4)
            {
                byteCount = sizeof(buffer);
                status = nfc_handler->MIFARE_Read(page, buffer, &byteCount);
                qDebug() << nfc_handler->GetStatusCodeName(status);

                for (byte offset = 0; offset < 4; offset++) {
                    for (byte index = 0; index < 4; index++) {
                        i = 4 * offset + index;
                        temp.sprintf("%x ", buffer[i]);
                        test.append(temp);
                    }
                }
            }

            for(int i=0; i < 12; i++)
            {
                tempMac.append(QByteArray::fromHex(test.split(' ')[30+i].toLocal8Bit()));
                if(i > 0 && i % 2 && i < 11)
                {
                    tempMac.append(':');
                }
            }

                if(tempMac.count(':') == 5 && tempMac.length() == 17)
                {
                    qInfo() << "NFC Reader found MAC : " << tempMac;
                    macAddress = tempMac;
                }
                else
                {
                    qWarning() << "NFC Reader error : no valid MAC found.";
                }

            isNFCReading = false;
            break;
        }
        nfc_handler->PICC_HaltA();
    }

    qDebug() << "End of NFC Thread";

    emit resultReady(macAddress);
}

void NfcThread::resetNfcReading()
{
    isNFCReading = false;
}

