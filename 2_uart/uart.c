#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define BAUD_RATE 9600
#define UART_BASE 0x40002000
#define TGT_RXD_PIN 25
#define TGT_TXD_PIN 24
#define BUTTON_B_PIN 26
#define BUTTON_A_PIN 17
#define UART ((NRF_UART_REG*)UART_BASE)

typedef struct {
volatile uint32_t STARTRX;
volatile uint32_t STOPRX;
volatile uint32_t STARTTX;
volatile uint32_t STOPTX;
volatile uint32_t RESERVED0[3];
volatile uint32_t SUSPEND;

volatile uint32_t RESERVED1[56];

volatile uint32_t CTS;
volatile uint32_t NCTS;
volatile uint32_t RXDRDY;
volatile uint32_t RESERVED2[4];
volatile uint32_t TXDRDY;
volatile uint32_t RESERVED3[1];
volatile uint32_t ERROR;
volatile uint32_t RESERVED4[7];
volatile uint32_t RXTO;

volatile uint32_t RESERVED5[110];

volatile uint32_t INTEN;
volatile uint32_t INTENSET;
volatile uint32_t INTENCLR;
volatile uint32_t RESERVED6[94];
volatile uint32_t ERRORSRC;
volatile uint32_t RESERVED7[7];
volatile uint32_t ENABLE;
volatile uint32_t RESERVED8[1];
volatile uint32_t PSELRTS;
volatile uint32_t PSELTXD;
volatile uint32_t PSELCTS;
volatile uint32_t PSELRXD;
volatile uint32_t RXD;
volatile uint32_t TXD;
volatile uint32_t RESERVED9[1];
volatile uint32_t BAUDRATE;
volatile uint32_t RESERVED10[17];
volatile uint32_t CONFIG;

} NRF_UART_REG;


void uart_init(){
	//Flytt buttons til annen funksjon
	//GPIO->PIN_CNF[BUTTON_A_PIN] = 0; //Button A som input
	//GPIO->PIN_CNF[BUTTON_B_PIN] = 0; //Button B som input
	GPIO->PIN_CNF[TGT_TXD_PIN] = 1;
	GPIO->PIN_CNF[TGT_RXD_PIN] = 0;
	UART->PSELTXD = TGT_TXD_PIN;
	UART->PSELRXD = TGT_RXD_PIN;
	UART->BAUDRATE = BAUD_RATE;
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->ENABLE = 4;
	UART->STARTRX = 1;

}

void uart_send(char letter);

char uart_read(){

}

