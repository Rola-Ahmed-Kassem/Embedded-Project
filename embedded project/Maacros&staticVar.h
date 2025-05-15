#define UART1_BASE 0x4000D000
#define HWREG(x)  (*(volatile unsigned long*) x
#define UART1_FR      (*((volatile unsigned long *)0x4000D018))
#define SCB_BASE 0xE000E000     // register
#define SCB_CPACR 0xE000ED88  // SCB CPACR register address for floats
volatile unsigned long *SCB_CPACR_REG = (volatile unsigned long *)SCB_CPACR;
#define UART0_BASE 0x4000C000

