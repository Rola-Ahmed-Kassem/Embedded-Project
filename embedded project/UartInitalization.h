#ifndef MY_HEADER_H1
#define MY_HEADER_H1

#include "tm4c123gh6pm.h"


void UART1_Init(void) {
    SYSCTL_RCGCUART_R |= 0x02;     // Enable UART1 clock
    SYSCTL_RCGCGPIO_R |= 0x02;     // Enable Port B clock
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);  // Wait until Port B ready

    GPIO_PORTB_AFSEL_R |= 0x03;    // Enable alt functions on PB0, PB1
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0x000000FF) | 0x00000011;
    GPIO_PORTB_DEN_R |= 0x03;      // Enable digital on PB0, PB1
    GPIO_PORTB_DIR_R |= 0x02;      // PB1 output (TX), PB0 input (RX)

    UART1_CTL_R &= ~UART_CTL_UARTEN;    // Disable UART1
    UART1_IBRD_R = 104;    // 9600 baud @ 16 MHz
    UART1_FBRD_R = 11;
    UART1_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;
    UART1_CTL_R = UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE;
	
    // Enable UART1 interrupt
		UART1_ICR_R = UART_ICR_RXIC;     // Clear interrupt flag (recommended)
    UART1_IM_R |= UART_IM_RXIM;
    NVIC_EN0_R |= (1 << 6); // IRQ 6 for UART1


}

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= 0x01;     // Enable UART0
    SYSCTL_RCGCGPIO_R |= 0x01;     // Enable Port A clock
    while ((SYSCTL_PRGPIO_R & 0x01) == 0);  // Wait for GPIOA to be ready

    UART0_CTL_R &= ~0x01;           // Disable UART0
    UART0_IBRD_R = 104;             // 9600 baud with 16 MHz clock
    UART0_FBRD_R = 11;
    UART0_LCRH_R = 0x70;            // 8-bit, no parity, 1 stop bit, enable FIFO
    UART0_CTL_R = 0x301;            // Enable UART0, TXE, RXE

    GPIO_PORTA_AFSEL_R |= 0x03;     // PA0, PA1 alternate function
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | 0x11; // UART
    GPIO_PORTA_DEN_R |= 0x03;       // Digital enable
    GPIO_PORTA_DIR_R |= 0x02;       // PA1 output (TX)
}
#endif // MY_HEADER_H1
