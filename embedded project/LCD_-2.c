#include "LCD_-1.h"
#include "SysTick-1.h"

// PB4–PB7 for 4-bit data, PB0 for RS, PB1 for EN, PB2 for RW
// RW is used for Busy Flag checking

/** ? Enable Pulse Function */
static void LCD_enable(void) {
    GPIO_PORTB_DATA_R |= 0x02;  // Set EN HIGH
    delayUs(2);
    GPIO_PORTB_DATA_R &= ~0x02; // Set EN LOW
    delayUs(2);
}

/** ? Check Busy Flag */
uint8_t LCD_Busy(void) {
    uint8_t status;

    // Set RS = 0 (Command Mode), RW = 1 (Read Mode)
    GPIO_PORTB_DATA_R &= ~0x01; // RS = 0
    GPIO_PORTB_DATA_R |= 0x04;  // RW = 1

    // Set PB4-PB7 as INPUT
    GPIO_PORTB_DIR_R &= ~0xF0;

    // Read upper nibble (Busy Flag is PB7)
    GPIO_PORTB_DATA_R |= 0x02;   // EN = HIGH
    delayUs(1);
    status = GPIO_PORTB_DATA_R;  // Read LCD status
    GPIO_PORTB_DATA_R &= ~0x02;  // EN = LOW

    // Restore PB4-PB7 as OUTPUT for normal LCD communication
    GPIO_PORTB_DIR_R |= 0xF0;
    GPIO_PORTB_DATA_R &= ~0x04;  // RW = 0 (Write Mode)

    return (status & 0x80); // Return Busy Flag (1 = busy, 0 = ready)
}

/** ? Clear LCD Screen */
void LCD_clearScreen(void) {
    LCD_command(0x01); // Clear display
    delayMs(10);
}

/** ? Send 4-bit Data */
void LCD_send_4bits(uint8_t bits) {
    GPIO_PORTB_DATA_R &= ~0xF0;  // Clear PB4-PB7
    GPIO_PORTB_DATA_R |= (bits << 4) & 0xF0; // Mask & shift to PB4-PB7
    LCD_enable();  // Pulse EN
}

/** ? Send Command */
void LCD_command(uint8_t cmd) {
    while(LCD_Busy());  // Wait if LCD is busy
    GPIO_PORTB_DATA_R &= ~0x05; // RW = 0, RS = 0
    LCD_send_4bits(cmd >> 4);  // High nibble
    LCD_send_4bits(cmd & 0x0F); // Low nibble
    delayMs(2);
}

/** ? Send Character Data */
void LCD_data(char data) {
    while (LCD_Busy());  // Wait until LCD is ready
    GPIO_PORTB_DATA_R &= ~0x04; // RW = 0 (Write Mode)
    GPIO_PORTB_DATA_R |= 0x01;  // RS = 1 (Data Mode)
    LCD_send_4bits(data >> 4);  // Upper nibble
    LCD_send_4bits(data & 0x0F);  // Lower nibble
    delayMs(1);
}

/** ? Print String to LCD */
void LCD_print(char *str) {
    uint8_t count = 0;
    while (*str) {
        LCD_data(*str++);
        count++;
        if (count == 16) {
            LCD_command(0xC0); // Move to second line after 16 characters
        }
    }
}

/** ? GPIO Initialization for LCD */
void LCD_GPIO_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02; // Enable Port B
    while ((SYSCTL_PRGPIO_R & 0x02) == 0); // Wait for activation

    // Configure PB0 (RS), PB1 (EN), PB2 (RW), and PB4–PB7 (Data)
    GPIO_PORTB_DIR_R |= 0xFF;  // Set all PB0–PB7 as outputs
    GPIO_PORTB_DEN_R |= 0xFF;  // Enable digital function
    GPIO_PORTB_AFSEL_R &= ~0xFF; // Disable alternate functions
    GPIO_PORTB_AMSEL_R &= ~0xFF; // Disable analog function
}

/** ? LCD Initialization */
void LCD_init(void) {
    LCD_GPIO_Init();  // Initialize GPIO
    SysTick_Init();   // Initialize delay functions

    delayMs(50); // Allow LCD power-on

    // Set 4-bit mode (following HD44780 datasheet)
    LCD_send_4bits(0x03); delayMs(5);
    LCD_send_4bits(0x03); delayMs(1);
    LCD_send_4bits(0x03); delayMs(1);
    LCD_send_4bits(0x02); delayMs(1);

    // Configure LCD
    LCD_command(0x28); // 4-bit, 2-line, 5x8 font
    delayMs(5);
    LCD_command(0x0C); // Display ON, cursor OFF
    delayMs(5);
    LCD_command(0x01); // Clear display
    delayMs(10);
    LCD_command(0x06); // Entry mode: increment cursor
}


