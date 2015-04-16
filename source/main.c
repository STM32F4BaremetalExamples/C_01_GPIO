#include "stm32f4xx.h"                  // Device header

void LED_init(void);
void LED_output(int val);
void delay_ms(int delay_time);
void BUTTON_init(void);
int BUTTON_read(void);

int main(){
	LED_init();
	BUTTON_init();
	while(1){
		LED_output(BUTTON_read());
		delay_ms(500);
	}
	//return 0;
}

void LED_init(void){
	RCC->AHB1ENR|=(0x1<<0);//Enable GPIOA
	
	GPIOA->MODER&=~(0x3<<10);
	GPIOA->MODER|=(0x1<<10);
}
void LED_output(int val){
	if(val==0){
		GPIOA->BSRRH=(0x1<<5);//Pone en bajo el pin A5
	}else{
		GPIOA->BSRRL=(0x1<<5);//Pone en alto el pin A5
	}
}
void delay_ms(int delay_time){
	int i;
	int j;
	j=delay_time*0x4FF;
	for(i=0;i<j;i++);
}

void BUTTON_init(void){
	RCC->AHB1ENR|=(0x1<<2);//Enable GPIOC
	
	GPIOC->MODER&=~(0x3<<26);//MODER 00 entrada en pin C13
	GPIOC->PUPDR&=~(0x3<<26);
	GPIOC->PUPDR|=(0x1<<26);//habilitar pull-ups en pin C13
}
int BUTTON_read(void){
	if((GPIOC->IDR)&(0x1<<13)){
		return 1;
	}
	return 0;
}
