#include "stm32f10x.h"                  // Device header

void Servo_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	Tim_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructure.TIM_Period = 20000 - 1;	//ARR
	Tim_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;	//PSC
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &Tim_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	//CCR
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

void Servo_SetAngle(float Angle){
	TIM_SetCompare3(TIM3, Angle / 180 * 2000 + 500);
}
