#include<stdint.h>
#include<inttypes.h>
#include"I2C.h"

int main() {
   
  
	uint8_t sendData[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t receiveData[4] = {0};
		I2C1_SendData(0x50, sendData, 4);
		for (volatile int i = 0; i < 100000; i++);
    
    I2C1_ReceiveData(0x50, receiveData, 4);
    
    while (1)
    {
        i2cclock_en ();
 i2cGPIO_en ();
 reset_i2c ();
  set_i2c ();
    }
}

