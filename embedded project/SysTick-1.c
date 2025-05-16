#include "tm4c123gh6pm.h"
#include <stdint.h>

void SysTick_Init(void) 
	{
    NVIC_ST_CTRL_R = 0;                 // Disable SysTick
    NVIC_ST_RELOAD_R = 16000 - 1;       // 1 ms at 16 MHz
    NVIC_ST_CURRENT_R = 0;              // Clear current
    NVIC_ST_CTRL_R = 0x05;              // Enable SysTick, system clock
}
// function for delay 
void delayMs(uint32_t ms) {
	   uint32_t i ;
    for( i = 0; i < ms; i++) {
        while((NVIC_ST_CTRL_R & 0x10000) == 0); // once count flag becomes 0,move to next millisecond
    }
}
void delayUs(uint32_t us) {
    NVIC_ST_RELOAD_R = 16 * us - 1; // Assuming 16MHz clock
    NVIC_ST_CURRENT_R = 0;
    while((NVIC_ST_CTRL_R & 0x10000) == 0);
}