#include "Comm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

CommI2C::CommI2C(char * i2cBusDevice)
{
  this->i2cBusDevice = i2cBusDevice;
}

CommI2C::~CommI2C()
{
  close(fd);
}

// initialization
void CommI2C::initComm()
{
  fd = open(i2cBusDevice, O_RDWR);

  if (fd < 0)
  {
    fprintf(stderr, "CommI2C::initComm(): opening the i2c bus '%s' failed", i2cBusDevice);
    return;
  }

  if (ioctl(fd, I2C_SLAVE, rc522_addr) < 0)
    fprintf(stderr, "CommI2C::initComm(): i2c device init failed for bus '%s'", i2cBusDevice);

  usleep(1000);

  return;
}

// write count bytes from values
void CommI2C::writeBytes(byte reg,
                         byte count,
                         byte *values)
{
  byte *buf;
  ssize_t len = count + 1;

  buf = (byte *)malloc(len);
  buf[0] = reg;
  memcpy(buf + 1, values, count);

  if (write(fd, buf, len) != len)
    fprintf(stderr, "CommI2C::writeBytes(): i2c transaction error on bus '%s'", i2cBusDevice);
  /* 
        printf("write reg %x values buf",reg);
        for (int i=0;i<count;i++) printf(" %x %x",values[i],buf[i+1]);
        printf(" len %d\n",count);
   */

  free(buf);

  usleep(1000);

  return;
}

// read count bytes into values
void CommI2C::readBytes(byte reg,
                        byte count,
                        byte *values,
                        byte rxAlign)
{
  byte value0 = values[0];
  values[0] = reg;

  if (write(fd, values, 1) != 1)
  {
    fprintf(stderr, "CommI2C::readBytes(): write access, i2c transaction error on bus '%s'", i2cBusDevice);
    return;
  }

  usleep(1000);

  if (read(fd, values, count) != count)
    fprintf(stderr, "CommI2C::readBytes(): read values, i2c transaction error on bus '%s'", i2cBusDevice);

  usleep(1000);

  if (rxAlign)
  { // Only update bit positions rxAlign..7 in values[0]
    // Create bit mask for bit positions rxAlign..7
    byte mask = (0xFF << rxAlign) & 0xFF;
    // Apply mask to both current value of values[0] and the new data in value.
    values[0] = (value0 & ~mask) | (values[0] & mask);
  }
  /* 
    printf("read reg %02x values ", reg);
    for (int i=0;i<count;i++) printf(" %x",values[i]);
         printf(" len %d\n",count);
   */
  return;
}
