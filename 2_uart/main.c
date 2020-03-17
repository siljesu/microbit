#include "uart.h"

#define __GPIO_BASE_ADDRESS__ 0x50000000
#define __BUTTON_B_PIN__ 26 //26
#define __BUTTON_A_PIN__ 17 //17

#define GPIO ((NRF_GPIO_REGS*)__GPIO_BASE_ADDRESS__)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;

	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		if (((GPIO->IN)&(1 << __BUTTON_B_PIN__))==0x0){
			uart_send('B');
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		if (((GPIO->IN)&(1 << __BUTTON_A_PIN__))==0x0){
			uart_send('A');
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}