#include "i2c.h"

void i2c_start(void)
{
    // Start / Restart generation
    I2C1.CR2 |= I2C_CR2_START;
}

void i2c_address(uint8_t device_address)
{

}

void i2c_write(uint8_t reg_data)
{
    // Clear NACK flag by setting this bit 
    I2C1.ISR |= I2C_ISR_NACKF;
    // Wait for Transmit Register to become empty
    while ( !(I2C1.ISR & I2C_ISR_TXE) )
    ;
    // Write the data
    I2C1.TXDR = reg_data;
    // Wait for the byte to be transmitted and a response
    // 0 Means ACK was received from slave device
    while ( (I2C1.ISR & I2C_ISR_NACKF) )
    ;
}
void i2c_read(uint8_t address, uint8_t buffer, int length)
{

}
void i2c_stop(void)
{

}


// PB6 -> SCL
// PB7 -> SDA
// NOTE: You can maybe remove external pull up resistors
// Stm32l0 has internal pull up resistor options in software
// if SCL and SDA require it
void i2c_master_init(I2C_TypeDef *I2Cx)
{
    if(I2Cx == &I2C1)
    {
        // Enable I2C1 clock
        RCC.APB1ENR |= RCC_APB1ENR_I2C1EN;
        // Enable GPIOB clock
        RCC.IOPENR |= RCC_IOPENR_GPIOBEN;
        // Configure PB6 to Alternate mode
        GPIOB.MODER &= bit_clear(12);
        GPIOB.MODER |= bit_set(13);
        // Configure PB7 to Alternate mode
        GPIOB.MODER &= bit_clear(14);
        GPIOB.MODER |= bit_set(15);
        // Configure PB6 and PB7 to OPEN DRAIN
        GPIOB.OTYPER |= bit_set(6);
        GPIOB.OTYPER |= bit_set(7);
        // PB6 to Very High Speed 
        GPIOB.OSPEEDR |= bit_set(12) | bit_set(13);
        // PB7 to Very High Speed 
        GPIOB.OSPEEDR |= bit_set(14) | bit_set(15);

        // Enable internal Pull-up Resistors for PB6 and PB7
        // I already have external Pull-up Resistors
        // GPIOB.PUPDR |= bit_set(12);
        // GPIOB.PUPDR |= bit_set(14);

        // Reset to no pull
        GPIOB.PUPDR &= bit_clear(12);
        GPIOB.PUPDR &= bit_clear(14);


        // Alternate Function PB6 to I2C1_CLK [AF1]
        GPIOB.AFR[0] |= bit_set(24);
        // Alternate Function PB7 to I2C1_SDA [AF1]
        GPIOB.AFR[0] |= bit_set(28);

        // Lock Register PB6 and PB7 if required


        // ** Noise Filters PG 594 **
        // Analog filter enabled by default 
        // Digital filter disabled by default

        // TIMING for 16MHZ HSI with Filters
        I2Cx->TIMINGR = 0x00303D5B;

        // 7 bit or 10 bit address! 7 bit address selected
        I2Cx->CR2 &= bit_clear(11);

        // Enable I2C1
        I2Cx->CR1 |= I2C_CR1_PE;
    }
}

void i2c_master_write(uint8_t dev_addr, uint8_t *data, uint8_t num_of_bytes)
{
    // Keep track of number of data sent
    uint8_t i = 0U;
 
    // Device address
    I2C1.CR2 |= dev_addr<<0;

    // Master Write Transfer
    I2C1.CR2 &= bit_clear(10);

    // Number of bytes to Transmit
    I2C1.CR2 |= ((uint32_t)(num_of_bytes))<<16;

    // Reload mode says after total bytes are sent
    // then transfter is completed, thus it works with AUTOEND
    I2C1.CR2 &= bit_clear(24);

    // AUTOEND disabled, TC bit will notify when NBYTES data are 
    // transfered
    I2C1.CR2 &= bit_clear(25);

    // Flush out Transmit Data Register
    I2C1.ISR |= I2C_ISR_TXE;

    // Start / Restart generation
    I2C1.CR2 |= bit_set(13);

    // Wait for Transmit Register to become empty, should go to 1
    while ( !(I2C1.ISR & I2C_ISR_TXE) )
    ;
    
    // Data to transmit 
    while (i < num_of_bytes )
    {
        // Moves the data into Transmit data register
        I2C1.TXDR = *data;
         // Increments to the next data
        data++;
        i++;
        // Wait for Transmit Register to become empty, should go to 1
        while ( !(I2C1.ISR & I2C_ISR_TXE) )
        ;
    }

    // Check if NBYTES are transfered, should go to 1
    while( !(I2C1.ISR & I2C_ISR_TC) )
    ;

    // STOP generation
    I2C1.CR2 |= I2C_CR2_STOP; 
    
}

uint8_t i2c__master_read(uint8_t dev_addr, uint8_t dev_mem, uint8_t *data)
{
    // data obtained from MPU9250
    uint8_t data_read = 0U;
 
    // Device address
    I2C1.CR2 |= dev_addr<<1;

    // Master Write Transfer
    I2C1.CR2 &= bit_clear(10);

    // Number of bytes to Transmit
    I2C1.CR2 |= 1<<16;

    // Reload mode - Transfer complete RESTART / STOP bit follows
    I2C1.CR2 &= bit_clear(24);

    // TC flag is set when byte is transfered
    I2C1.CR2 &= bit_clear(25);

    // Flush out Transmit Data Register
    I2C1.ISR |= I2C_ISR_TXE;
    // Memory location to access on MPU9250
    I2C1.TXDR = dev_mem;

    // Start generation
    I2C1.CR2 |= bit_set(13);
    
    // Wait for byte to transfer, may need to be skipped
    //while ( !(I2C1.ISR & I2C_ISR_TC) );

    // Change to Master Read mode
    I2C1.CR2 |= bit_set(10);

    // Restart generation
    I2C1.CR2 |= bit_set(13);

    // Wait for data to be copied into RXDR
    while ( !(I2C1.ISR & I2C_ISR_RXNE) )
    ;
    
    data_read = (uint8_t)I2C1.RXDR;

    // Stop generation
    I2C1.CR2 |= bit_set(14);

    return data_read;
}