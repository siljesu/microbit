#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define BAUD_RATE 9600
#define UART_BASE 0x40002000
#define UART ((NRF_UART_REG*)UART_BASE)

typedef struct {
volatile uint32_t STARTRX;
volatile uint32_t STOPRX;
volatile uint32_t STARTTX;
volatile uint32_t STOPTX;
volatile uint32_t SUSPEND;

volatile uint32_t RESERVED0[57];

volatile uint32_t CTS;
volatile uint32_t NCTS;
volatile uint32_t RXDRDY;
volatile uint32_t TXDRDY;
volatile uint32_t ERROR;
volatile uint32_t RXTO;

volatile uint32_t RESERVED1[111];

volatile uint32_t INTEN;
volatile uint32_t INTENSET;
volatile uint32_t INTENCLR;
volatile uint32_t ERRORSRC;
volatile uint32_t ENABLE;
volatile uint32_t PSELRTS;
volatile uint32_t PSELTXD;
volatile uint32_t PSELCTS;
volatile uint32_t PSELRXD;
volatile uint32_t RXD;
volatile uint32_t TXD;
volatile uint32_t BAUDRATE;
volatile uint32_t CONFIG;

} NRF_UART_REG;


void uart_init();

void uart_send(char letter);

char uart_read(){

}

