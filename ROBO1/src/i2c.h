#ifndef I2C_H
#define I2C_H


/*                  I2C protocol Working
    
    Synchronous Communication - Uses the clock to synchronize
    data between the source and destination. (SCL)

    Half-Duplex mode - It has only 1 data line (SDA)

    Speeds - SM(100 kbit/s), FM(400 kbit/s), FM+(1 Mbit/s)
    Open Collector / Open Drain - BJT or MOSFET switch 
                                - Can turn on / off.
                                - Thats why pull-up resistors are needed 
                                  on Collector terminal. 
    -------------------
    I2C Frame Structure
    -------------------
    
    Start bit
    ---------
    
    Device Address
    --------------
    7 bit mode - 128 devices can be connected
    10 bit mode - 1024 devices can be connected

    Write/Read
    ----------
    0 - Write data to slave
    1 - Read data from slave
    
    Slave ACK
    ---------
    0 - If the slave exists on the line it will respond with an ACK of '0'
    1 - If the slave does not exist on the line it will respond with an ACK of '1'

    Data (8 bits)
    -------------------
    Data transmit or receive depending on Write / Read bit

    Mater / Slave (ACK)
    -------------------
    After each 8 bit data transmission from Master, slave responds with ACK(0)
    OR
    After each 8 bit data reception from Slave, Master responds with ACK(0)

    Complete Flow
    -------------
    START bit | Device address(7/10) | Write/Read(0 or 1) | Slave_ACK(0) | Data(8) | ACK(0) | Data(8) | ACK(0),... | STOP bit


    -----------
    Arbitration
    -----------
    Process to get the bus access. (SDA line association)
    If multiple masters attempt to communicate with the slave device, the one that sends a '0' start bit first 
    when the other devices sends a '1' WINS.

    ----------------
    Clock stretching
    ----------------
    Process to slow down the communication(SCL line association)
    The slave device may hold a clock line low after receiving a byte to indicate that its not ready to 
    process more data, and therefore the master can wait until the SCL line is pulled high again.

    Advantages
    ----------
    Supports multi-master, multi-slave communications.
    Due to device addressing no chip select pin (SPI) is required. Hence reduce number of pins.
    Better error handling is available with ACK bit.
    Due to clock stretching, it can work well with both slow and fast IC's.

    Disadvantages
    -------------
    Slow transmission speed due to frame overhead because of device address bits and ACK bits.
    It works in half duplex mode.
    The hardware complexity increases when more number of master/slave devices are added.

    -----------------------------------
    IMU Example for writing and reading
    -----------------------------------
    
    Write to registers in IMU
    -------------------------
    START | ADDRESS | WRITE[0] | ACK | REGISTER | ACK | DATA_1 | ACK | DATA_2 | ACK | STOP
    - NOTE: DATA_2 will be sequentially sent to the next memory location in REGISTER to (REGISTER+1) and so on...

    Read to registers in IMU
    ------------------------
    START | ADDRESS | WRITE[0] | ACK | REGISTER | ACK | REPEATED START | ADDRESS | READ[1] | ACK | DATA_1 | ACK | DATA_2 | NACK | STOP
    - NOTE: Repeated start condition to now read the data at that specific register location.
            DATA_2 will be sequential data read from the next memory location (REGISTER+1) and so on...        

*/

/*
    FM+ : Output Current driving capability in SYSCFG register
    ACK : can be enabled or disabled (We will enable it to determine if slave device exists)
    NOISE : When I2C is enabled, you cannot configure the ANALOG and DIGITAL FILTERS
            The noise filters if enabled, must comply with specific conditions in order for 
            I2C clocking to function correctly. 
    CLOCKING : Hold and Setup times - Use STM32CUBEmx to determine I2C_TIMINGR content
               Select I2C clocking from HSI(16MHZ) - 0x00303D5B (SM-100khz) with Analog Filter enabled(0), and digital filter disabled(0)
    
    RECEPTION: RXNE bit is set -> Data moved from shift register into I2Cx_RXDR and ready to read
               if not read yet than Clock stretching(SCL) occurs between 8th and 9th clock pulse 
               between the DATA and ACK response until data is read. Therefore, read it fast. 

    TRANSMISSION: 

    I2C Master mode Initialization
    ------------------------------
    1. Before peripheral enabled(PE=0) write data to I2C_TIMINGR register. (Determine value with STM32cubemx Tool)
    2. 
 */

#include "main.h"

void i2c_start(void);
void i2c_address(uint8_t device_address);
void i2c_write(uint8_t reg_data);
void i2c_read(uint8_t address, uint8_t buffer, int length);
void i2c_stop(void);

/**
 * @brief 
 * 
 * @param I2Cx Handle
 */
void i2c_master_init(I2C_TypeDef *I2Cx);

/**
 * @brief Write data to a specified memory address of a slave device
 * 
 * @param dev_addr Slave address of the device
 * @param data     Data to write to that slave memory address
 */
void i2c_master_write(uint8_t dev_addr, uint8_t *data, uint8_t num_of_bytes);

/**
 * @brief Reads data from a memory address in a slave device
 * 
 * @param dev_addr Slave address of the device
 * @param dev_mem  Memory Address in the slave device to read from  
 * @param data     Data to read from the specified memory address in the slave device
 * @return uint8_t is the returned data read from slave memory
 */
uint8_t i2c_master_read(uint8_t dev_addr, uint8_t dev_mem, uint8_t *data);


#endif // I2C_H
