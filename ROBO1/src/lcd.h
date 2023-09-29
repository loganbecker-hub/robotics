#ifndef LCD_H
#define LCD_H

#include "gpio.h"
#include "main.h"
#include <stdio.h>

/* Function declarations */
void Lcd_command_4bit(int8_t cmd);
void Lcd_init_4bit(void);
void Lcd_char_4bit(int8_t dat);
void Lcd_string_4bit(const char *msg);
void Lcd_string_xy(uint8_t row,uint8_t pos,const char *msg);
void Lcd_clear_4bit(void);
void Lcd_setCursor(int row, int column);

#endif // LCD_H
