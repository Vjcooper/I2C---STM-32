#include "I2C.h"
#include<stdint.h>
uint32_t  i2cSpeed ;
uint32_t  pclk1Freq;
uint32_t *RCC_APB1ENR  = (uint32_t *)(RCC+APB1ENR);
uint32_t *RCC_CR = (uint32_t *) (RCC+CR);
uint32_t *RCC_AHB1 = (uint32_t *)(RCC+AHB1);
void i2cclock_en (void)
{
	*RCC_CR |=(1<<0);
*RCC_APB1ENR |= (1<<21);
	*RCC_AHB1 |=(1<<1);
}

void i2cGPIO_en (void)
{
	
	GPIO->MODER &=~(1u<<12);
	GPIO->MODER |=(1<<13);
	GPIO->MODER &=~(1u<<14);
	GPIO->MODER |=(1<<15);
	GPIO->OTYPER |=(1<<6);
	GPIO->OTYPER |=(1<<7);
	GPIO->PUPDR |=(1<<12);
	GPIO->PUPDR &=~(1u<<13);
	GPIO->PUPDR |=(1<<14);
	GPIO->PUPDR &=~(1u<<15);
	GPIO->AFRL |=(4<<24);
	GPIO->AFRL |=(4<<28);
}
void reset_i2c (void)
{
	I2C1->CR1|=(1<<15);
	I2C1->CR1&=~(1u<<15);
}
void set_i2c (void)
{
 
    uint32_t i2cFreq = 42000000; 
    if (i2cFreq <= 100000)
        i2cSpeed = 100000;  
    else
        i2cSpeed = 400000;  
    uint32_t pclk1Freq = 42000000;  
    uint32_t i2cTiming = 0;
    
    i2cTiming = (pclk1Freq / (i2cSpeed << 1)) & 0xFFF;
    i2cTiming |= (((pclk1Freq / i2cSpeed) + 1) & 0xF) << 28;
	
	
	I2C1->CR2 |= (45<<0);
	I2C1->CR1 &= ~(1U << 0);    
    I2C1->CR2 &= ~(0x3FU << 0);
    I2C1->CR2 |= (42U << 0);    
    I2C1->CCR &= ~(0xFFFU << 0); 
    I2C1->CCR |= (i2cTiming & 0xFFFU);   
    I2C1->TRISE &= ~(0x3FU << 0);
    I2C1->TRISE |= (i2cTiming >> 16);      
    I2C1->CR1 |= (1U << 10);  
    I2C1->CR1 |= (1U << 0);    
}

void I2C1_SendData(uint8_t slaveAddr, uint8_t* data, uint8_t dataSize)
{
	uint8_t i;
    // Generate start condition
    I2C1->CR1 |= (1U << 8);   // I2C_CR1_START
    
    // Wait for start condition to be generated
    while (!(I2C1->SR1 & (1U << 0))) // I2C_SR1_SB
    
    // Send slave address with write bit
    I2C1->DR = (slaveAddr << 1) & ~(1U << 0);  // I2C_DR_DR
    
    // Wait for address to be sent
    while (!(I2C1->SR1 & (1U << 1)));  // I2C_SR1_ADDR
    
    // Clear ADDR flag
    I2C1->SR2;
    
    // Send data
    for ( i = 0; i < dataSize; i++)
    {
        // Wait for data register to be empty
        while (!(I2C1->SR1 & (1U << 7)));  // I2C_SR1_TXE
        
        // Write data to data register
        I2C1->DR = data[i];
    }
    
    // Wait for data transfer to be completed
    while (!(I2C1->SR1 & (1U << 2)));  // I2C_SR1_BTF
    
    // Generate stop condition
    I2C1->CR1 |= (1U << 9);   // I2C_CR1_STOP
}

void I2C1_ReceiveData(uint8_t slaveAddr, uint8_t* data, uint8_t dataSize)
{
	uint8_t i;
    // Generate start condition
    I2C1->CR1 |= (1U << 8);   // I2C_CR1_START
    
    // Wait for start condition to be generated
    while (!(I2C1->SR1 & (1U << 0)));  // I2C_SR1_SB
    
    // Send slave address with read bit
    I2C1->DR = (slaveAddr << 1) | (1 << 0);  // I2C_DR_DR
    
    // Wait for address to be sent
    while (!(I2C1->SR1 & (1U << 1)));  // I2C_SR1_ADDR
    
    // Clear ADDR flag
    I2C1->SR2;
    
    // Receive data
    for ( i = 0; i < dataSize; i++)
    {
        // Wait for data to be received
        while (!(I2C1->SR1 & (1U << 6)));  // I2C_SR1_RXNE
        
        // Read data from data register
        data[i] = I2C1->DR;
    }
    
    // Generate stop condition
    I2C1->CR1 |= (1U << 9);   // I2C_CR1_STOP
}








	