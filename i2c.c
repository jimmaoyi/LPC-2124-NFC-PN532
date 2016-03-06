#include "i2c.h"


/**
    Initialize I2C
*/
void i2c_Init(void)
{
    PINSEL0 |= 0x50;
    I2SCLL = I2SCLH = 400; // 75kBits @ 58,98 <MHz
    I2CONSET = 0x40; // enable I2C bus interface
}


/**
    Handle timeouts and interrupt action
*/
static void i2c_WaitForSI(void)
{
    unsigned long timeout = 1600000;
    I2CONCLR = 8; // clear SI starts action
    while (timeout-- && !(I2CONSET & 8)); // check SI with timeout
}


/**
    Send "START" condition
*/
int i2c_start(int addr)
{
    I2CONCLR = 0x14; // clear STO, AA
    I2CONSET = 0x28; // set STA, SI
    i2c_WaitForSI();

    I2CONCLR = 0x20; // clear STA

    if (I2STAT > 0x10) { // bus is busy
        return -1;
    }
    I2DAT = addr; // set address
    i2c_WaitForSI();

    return (I2STAT != 0x40 && I2STAT != 0x18); // no acknowledge
}


/**
    Write to I2C bus
*/
int i2c_Write(unsigned char *buf, unsigned count)
{
    while (count--) {
        I2DAT = *buf++; // load data into I2DAT register
        i2c_WaitForSI();

        if (I2STAT != 0x28) {
            return 1;  // no acknowledge
        }
    }
    return 0;
}


/**
    Read from I2C bus
*/
int i2c_Read(void)
{
    I2CONSET = AA; // assert Acknowledge
    i2c_WaitForSI();

    if (I2STAT != 0x50 && I2STAT != 0x40) {
        return -1; // not OK
    }
    return I2DAT;
}


/**
    Read last byte from I2C Bus
*/
int i2c_ReadLastByte(void)
{
  I2CONCLR = AA; // assert Acknowledge
  i2c_WaitForSI();

    if (I2STAT != 0x58){
        return -1; // not OK
    }
    return I2DAT;
}


/**
    Send "STOP" condition
*/
void i2c_stop(void)
{
    I2CONSET = 0x40; // re-enable I2C bus interface
}