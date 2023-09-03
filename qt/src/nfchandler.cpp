#include "nfchandler.h"
#ifdef __arm__
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#endif

NFCHandler::NFCHandler(QObject *parent)
    : QObject{parent}
{

}
