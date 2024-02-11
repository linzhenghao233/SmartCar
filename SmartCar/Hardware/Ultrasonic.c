#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Ultrasonic_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//Trig
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//Echo
	
	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 60000 - 1;	//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;	//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
}

float Ultrasonic_Distance(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	Delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == RESET);
	TIM_Cmd(TIM4, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == SET);
	TIM_Cmd(TIM4, DISABLE);
	float Distance = ((TIM_GetCounter(TIM4) * 1.0 / 10 * 0.34) / 2);	//得出cm
	TIM4->CNT = 0;
	Delay_ms(100);
	
	return Distance;
}
