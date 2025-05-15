#ifndef MY_HEADER_H
#define MY_HEADER_H


#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "Maacros&staticVar.h"
#include <string.h>
#include <stdio.h>	
	
bool gpsDataParser( char gpsStoredData[], char fields[][20] ) ; // get longtitude and latitude from  char[]  gpsStoredData
	
void UART0_SendChar(char data) {
    while ((UART0_FR_R & UART_FR_TXFF));  // Wait until TX FIFO not full
    UART0_DR_R = data;
}

void UART0_SendString(const char* str) {
    while (*str) {
        UART0_SendChar(*str++);
    }
}

char UART1_ReadChar(void) {
    while (UART1_FR_R & UART_FR_RXFE);  // Wait until not empty
    return UART1_DR_R & 0xFF;
}



void enable_fpu(void) {
    *SCB_CPACR_REG |= (0xF << 20);  // Set bits 20–23: full access to CP10 and CP11
}


bool RequiredSentence(volatile char c[])// checks for $GPRMC
  {  if( (c[0] =='$' )&& (c[1] =='G' )&& (c[2] =='P' )&& (c[3] =='R') && (c[4] =='M') && (c[5] =='C'))
			return true;
		else 
			return false;
	}
	
	
	bool IsUartDataAvailable() {
    
    if ((UART1_FR & UART_FR_RXFE) == 0) {
        return true;  // data  available
    }
    return false;  //  data not available
}
	
void UART0_SendFloat(float value) {
    char buffer[32];  // Enough to hold float as string
    snprintf(buffer, sizeof(buffer), "%.3f", value);  // Format float to 3 decimal places

    for (int i = 0; buffer[i] != '\0'; i++) {
        UART0_SendChar( buffer[i]);
    }
	}
#endif // MY_HEADER_H
