#ifndef LCD
#define LCD
//#include "gpio.h"
#include "tm4c123gh6pm.h"

#define LCD_Clear()
                      
#define LCD_OutString(str)



void delay(long d);
void printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcdin(void);
void lcd_string( char *str,int len);
void LCDSystem(void);

#endif // LCD_H_INCLUDED

