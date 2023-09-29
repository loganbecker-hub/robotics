#include "lcd.h"

void Lcd_command_4bit(int8_t cmd)
{
  // Get higher nibble
  int8_t temp = (cmd & 0xF0) >> 4;
  // D4 
  if(temp & 1){ gpio_set(&GPIOC, GPIO_PIN_3);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_3);}
  // D5 
  if(temp & 2){ gpio_set(&GPIOB, GPIO_PIN_10);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_10);}
  // D6 
  if(temp & 4){ gpio_set(&GPIOB, GPIO_PIN_11);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_11);}
  // D7
  if(temp & 8){ gpio_set(&GPIOC, GPIO_PIN_2);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_2);}
  // RS and EN 
  gpio_clear(&GPIOC, GPIO_PIN_0);
  gpio_set(&GPIOC, GPIO_PIN_1);
  __NOP();
  gpio_clear(&GPIOC, GPIO_PIN_1);
  delay(1);

  // Get lower nibble
  temp = (cmd & 0x0F);
  // D4 
  if(temp & 1){ gpio_set(&GPIOC, GPIO_PIN_3);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_3);}
  // D5 
  if(temp & 2){ gpio_set(&GPIOB, GPIO_PIN_10);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_10);}
  // D6 
  if(temp & 4){ gpio_set(&GPIOB, GPIO_PIN_11);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_11);}
  // D7
  if(temp & 8){ gpio_set(&GPIOC, GPIO_PIN_2);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_2);}
  // RS and En 
  gpio_set(&GPIOC, GPIO_PIN_1);
  __NOP();
  gpio_clear(&GPIOC, GPIO_PIN_1);
  delay(3);
}

void Lcd_init_4bit(void)
{       
  /* Data Lines D4, D5, D6, D7 */
  // SDO -> PC3
  gpio_pin_t SDO_PC3;
  SDO_PC3.mode = GPIO_MODE_OUTPUT;
  SDO_PC3.speed = GPIO_SPEED_VERY_HIGH;
  SDO_PC3.pin = GPIO_PIN_3;
  gpio_init(&GPIOC, &SDO_PC3);
  // SCK -> PB10
  SDO_PC3.pin = GPIO_PIN_10;
  gpio_init(&GPIOB, &SDO_PC3);
  // CS -> PB11
  SDO_PC3.pin = GPIO_PIN_11;
  gpio_init(&GPIOB, &SDO_PC3);
  // SDI -> PC2
  SDO_PC3.pin = GPIO_PIN_2;
  gpio_init(&GPIOC, &SDO_PC3);
  
  /* Control RS & EN */
  // RX -> PC0
  SDO_PC3.pin = GPIO_PIN_0;
  gpio_init(&GPIOC, &SDO_PC3);
  // TX -> PC1
  SDO_PC3.pin = GPIO_PIN_1;
  gpio_init(&GPIOC, &SDO_PC3);

  /* Clear all the Pins */
  gpio_clear(&GPIOB, GPIO_PIN_10);
  gpio_clear(&GPIOB, GPIO_PIN_11);
  gpio_clear(&GPIOC, GPIO_PIN_0);
  gpio_clear(&GPIOC, GPIO_PIN_1);
  gpio_clear(&GPIOC, GPIO_PIN_2);
  gpio_clear(&GPIOC, GPIO_PIN_3);
  
  delay(15);         // 15 mills, Power-On delay
  Lcd_command_4bit(0x02); // Send for initialization of LCD with nibble method
  Lcd_command_4bit(0x28); // Use 2 line and initialize 5*7 matrix in (4-bit mode)
  Lcd_command_4bit(0x01); // Clear display screen
  Lcd_command_4bit(0x0c); // Display on and cursor off
  Lcd_command_4bit(0x06); // Increment cursor (shift cursor to right)
}

void Lcd_char_4bit(int8_t dat)
{
  // Get higher nibble
  int8_t temp = (dat & 0xF0) >> 4;
  // D4 
  if(temp & 1){ gpio_set(&GPIOC, GPIO_PIN_3);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_3);}
  // D5 
  if(temp & 2){ gpio_set(&GPIOB, GPIO_PIN_10);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_10);}
  // D6 
  if(temp & 4){ gpio_set(&GPIOB, GPIO_PIN_11);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_11);}
  // D7
  if(temp & 8){ gpio_set(&GPIOC, GPIO_PIN_2);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_2);}
  // RS and EN 
  gpio_set(&GPIOC, GPIO_PIN_0);
  gpio_set(&GPIOC, GPIO_PIN_1);
  __NOP();
  gpio_clear(&GPIOC, GPIO_PIN_1);
  delay(1);

  // Get lower nibble
  temp = (dat & 0x0F);
  // D4 
  if(temp & 1){ gpio_set(&GPIOC, GPIO_PIN_3);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_3);}
  // D5 
  if(temp & 2){ gpio_set(&GPIOB, GPIO_PIN_10);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_10);}
  // D6 
  if(temp & 4){ gpio_set(&GPIOB, GPIO_PIN_11);}
  else{ gpio_clear(&GPIOB, GPIO_PIN_11);}
  // D7
  if(temp & 8){ gpio_set(&GPIOC, GPIO_PIN_2);}
  else{ gpio_clear(&GPIOC, GPIO_PIN_2);}
  // RS and En 
  gpio_set(&GPIOC, GPIO_PIN_1);
  __NOP();
  gpio_clear(&GPIOC, GPIO_PIN_1);
  delay(3);
}

void Lcd_string_4bit(const char *msg)
{
  while((*msg)!= 0)
  {		
    Lcd_char_4bit(*msg);
	msg++;	
  }
}

void Lcd_string_xy(uint8_t row,uint8_t pos,const char *msg)
{
  char location=0;
  
  if(row <= 1)
  {
    location = (0x80) | ( (pos) & 0x0f ); // Print message on 1st row and desired location
    Lcd_command_4bit(location);
  }
  else
  {
    location = (0xC0) | ( (pos) & 0x0f); // Print message on 2nd row and desired location
    Lcd_command_4bit(location);    
  }  
  
  Lcd_string_4bit(msg);
}

void Lcd_clear_4bit(void)
{
  Lcd_command_4bit(0x01);
}

void Lcd_setCursor(int row, int column)
{
    // Display, Cursor and CursorBlink On
    Lcd_command_4bit(0x0F);

    // Cursor movement
    uint8_t choice = 0x00;
    choice |= 1U<<4;

    choice |= (1U<<3);
    choice &= ~(1U<<2);
    Lcd_command_4bit(choice);
}
