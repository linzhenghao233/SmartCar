#include "stm32f10x.h"                  // Device header
#include "Motor.h"

void Car_Init(void){
	Motor_Init();
}

void Car_Advance(void){
	Motor_SetLeftSpeed(70);
	Motor_SetRightSpeed(70);
}

void Car_Retreat(void){
	Motor_SetLeftSpeed(-70);
	Motor_SetRightSpeed(-70);
}

void Car_TurnLeft(void){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(70);	
}

void Car_TurnRight(void){
	Motor_SetLeftSpeed(70);
	Motor_SetRightSpeed(0);	
}

void Car_Rotation_Left(void){
	Motor_SetLeftSpeed(-70);
	Motor_SetRightSpeed(70);	
}

void Car_Rotation_Right(void){
	Motor_SetLeftSpeed(70);
	Motor_SetRightSpeed(-70);	
}

void Car_Stop(void){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}
