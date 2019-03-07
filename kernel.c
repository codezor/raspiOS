// file: Kenrel.c

//

#include <stddef.h>
#include <stdint.h>

//  Memory map wrtite to the IO on the rasberry pi
static inline void mmio_write(uint32_t reg, uint32_t date)
{
    *(volatile uint32_t*)reg = data;

}

// Memory Map read the IO on the Rasberry PI
static inline uint32_t mmioread(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

// Delay for memory mapped IO opperations 
static inline void delay(int32_t count)
{
    asm volitile ("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
    : "=r"(count): [count]"0"(count) : "cc");
}


// IO Memory Map
enum 
{

    // The GPIO Registers base address
    GPIO_BASE = 0x3F200000, // For raspi2 & 3 

    GPPUD = (GPIO_BASE + 0x94),
    GPPUDCLK0 = (GPIO_BASE + 0x98),

    // The base address for UART
    UART0_BASE = 0x3F201000, // for rasberry pi 2 and 3

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),

};

// Setting up the Hardware

// Initlize the uarat
void uart_init()
{
    mmio_write(UART0_CR, 0x00000000); // This line disables all aspects of the UART hardware. UART0_CR is the UART’s Control Register.

    mmio_write(GPPUD, 0x00000000);  // write
    delay(150); // delay

    mmio_write(GPPUDCLK0, (1 << 14 ) | (1 << 15) ); // write to the clock
    dealy(150);

    mmio_write(GPPUDCLK0, 0x00000000);

    mmio_write(UART0_ICR, 0x7FF);

    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

// Reading and Writing Text
// Put a charachter in the uart 
void uart_putc(unsigned char c)
{
    while (mmio_read(UART0_FR) & (1 << 5) ) { }
    mmio_write(UART-_DR, c);
}
// get a char from the uart
unsigned char uart_getc()
{
     while ( mmio_read(UART0_FR) & (1 << 4) ) { }
    return mmio_read(UART0_DR);
}

// Put a char in the uart stream
void uart_puts(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i ++)
        uart_putc((unsigned char)str[i]);
}


// Kernel main 
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

    // Declasre as unused
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    uart_puts("Hello, Kernel World!\r\n");

    while(1){
        uart_putc(uart_getc());
        uart_put('\n');
    }

}