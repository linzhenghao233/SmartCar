#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Car.h"
#include "BlueTooth.h"
#include "Servo.h"
#include "Ultrasonic.h"

float Distance;

int main(void){
	OLED_Init();
	Car_Init();
	BlueTooth_Init();
	Servo_Init();
	Ultrasonic_Init();

	while(1){
		Distance = Ultrasonic_Distance();
		OLED_ShowNum(1, 1, Distance, 3);
		//BlueTooth_SendNumber(Distance, 3);
		if(Distance < 20){
			Car_Stop();
		}
		Delay_ms(1000);
	}
}

void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET){
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxData == 0x30)Car_Stop();
		else if(RxData == 0x31)Car_Advance();
		else if(RxData == 0x32)Car_Retreat();
		else if(RxData == 0x33)Car_TurnLeft();
		else if(RxData == 0x34)Car_TurnRight();
		else if(RxData == 0x35)Car_Rotation_Left();
		else if(RxData == 0x36)Car_Rotation_Right();
		else if(RxData == 0x37)Servo_SetAngle(0);
		else if(RxData == 0x38)Servo_SetAngle(90);
		else if(RxData == 0x39)Servo_SetAngle(180);
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
