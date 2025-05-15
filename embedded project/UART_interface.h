#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "STD_TYPES.h"

typedef enum { UART0 = 0, UART1 } UART_Number;
typedef enum { _5BIT = 5, _6BIT, _7BIT, _8BIT } UART_DataLen;
typedef enum { _1STOPBIT = 1, _2STOPBIT } UART_StopBits;
typedef enum { DISABLE_PARITY = 0, ENABLE_PARITY } UART_Parity;

typedef struct {
    UART_Number UART_NUM;
    u32 BAUD_RATE;
    UART_DataLen DataLen;
    UART_StopBits StopBits;
    UART_Parity Parity;
} UART_CONFIG_t;

void UART_Init(UART_CONFIG_t* config);
void UART_SendString(const char* str);
void UART_PrintFloat(f64 value);
u8 UART_ReceiveByte(UART_CONFIG_t* uart, u8* byte);

#endif
