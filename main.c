#include <targets/LPC2000.h>
#include "PN532.h"
#include "i2c.h"



int main (void)
{

  i2c_init();
  PN532_init();
  
  //read NFC
  while(1)
  {
      int i = 0;
      while(i < 1)
      {
          debug_printf("Write to NFC:\n");
          if(writeStringToNFC("*9876543210acdb##0123456789abcd*"))
          {
            i = 1;
          }
          i++;
      }
      while (i < 4)
      {
        debug_printf("Read from NFC:\n");
        char string[32];
        if(readStringFromNFC(string))
        {
          debug_printf("Data on Card %s\n", string);
          i = 3;
        }
        i++;
      }
  }

}