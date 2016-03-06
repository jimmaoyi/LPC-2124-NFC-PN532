#include <targets/LPC2000.h>

#define STA     0x20
#define SIC     0x08
#define SI      0x08
#define STO     0x10
#define STAC    0x20
#define AA      0x04

#define R       1


void i2c_Init(void);

static void i2c_WaitForSI(void);

int i2c_Start(int addr);

int i2c_Write(unsigned char *buf, unsigned count);

int i2c_Read(void);

int i2c_ReadLast(void);

void i2c_Stop(void);