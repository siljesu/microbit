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

void sendCharIfButton(){
	if (((GPIO->IN)&(1 << __BUTTON_B_PIN__))==0x0){
		uart_send('B');
	}

	if (((GPIO->IN)&(1 << __BUTTON_A_PIN__))==0x0){
		uart_send('A');
	}
}

int matrixToggled;
int toggleMatrixIfInput(int toggled){
	int slep = 10000;
	if (uart_read() != '\0'){
		if(toggled == 0){
			for (int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
			toggled = 1;
			while(!slep){
				slep--;
			}
		}
		else if(toggled == 1){
			for (int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}
			toggled = 0;
			while(!slep){
				slep--;
			}
		}
	}
	return toggled;
}
int main(){

	uart_init();

		// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	matrixToggled = 0;
	
		//Set to ground
	for (int i = 4; i <= 12; i++){
		GPIO->OUTCLR = (1 << i);
	}

	while(1){

		sendCharIfButton();

		matrixToggled = toggleMatrixIfInput(matrixToggled); //Doesn't work

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}