#ifndef LCD_H_
#define LCD_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>

// LCD Control Pins
#define RS  (*((volatile uint32_t *)0x40005004)) // PB0
#define EN  (*((volatile uint32_t *)0x40005008)) // PB1
#define RW  (*((volatile uint32_t *)0x40005010)) // PB2

// LCD Function Prototypes
void LCD_send_4bits(uint8_t bits);
void LCD_command(uint8_t cmd);
void LCD_data(char data);
void LCD_print(char *str);
void LCD_GPIO_Init(void);
void LCD_init(void);
void LCD_clearScreen(void);
uint8_t LCD_Busy(void);

#endif
