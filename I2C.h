#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "inttypes.h"
uint32_t extern i2cSpeed ;
uint32_t extern pclk1Freq;
#define RCC 0x40023800
#define CR 0x00
#define AHB1 0x30
#define APB1ENR 0x40
#define GPIOA_Base 0x40020000
#define GPIOB_Base 0x40020400 
#define GPIOC_Base 0x40020800 
#define GPIOD_Base 0x40020C00
#define GPIOE_Base 0x40021000
#define GPIOF_Base 0x40021400
#define GPIOG_Base 0x40021800
#define GPIOH_Base 0x40021C00
#define GPIOI_Base 0x40022000
#define GPIOJ_Base 0x40022400
#define GPIOK_Base 0x40022800

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_x;
	

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_x;

extern uint32_t  *RCC_APB1ENR;
extern uint32_t  *RCC_CR;
extern uint32_t  *RCC_AHB1;
#define GPIO ((GPIO_x *) GPIOB_Base)


#define I2C1_BASE    0x40005400
#define I2C1 ((I2C_x  *)I2C1_BASE)

void i2cclock_en (void);
void i2cGPIO_en (void);
void reset_i2c (void);
void set_i2c (void);
void I2C1_SendData(uint8_t slaveAddr, uint8_t* data, uint8_t dataSize);
void I2C1_ReceiveData(uint8_t slaveAddr, uint8_t* data, uint8_t dataSize);

#endif /* I2C_DRIVER_H */
