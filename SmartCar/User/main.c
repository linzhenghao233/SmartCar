#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Car.h"

int main(void){
	OLED_Init();
	Car_Init();
	
	Car_Advance();
	
	while(1){
		
	}
}
