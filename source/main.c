#include "stm32f4xx.h"                  // Device header

void LED_init(void);
void LED_output(int val);
void delay_ms(int delay_time);

int main(){
	LED_init();
	while(1){
		LED_output(0);
		delay_ms(500);
		LED_output(1);
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
	j=delay_time*0xFFF;
	for(i=0;i<j;i++);
}
