//小车模块

#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"

void Car_Init(void)
{
	Motor_Init();
}

void Go_Ahead(void)
{
	Motor_SetLeftSpeed(70);
	Motor_SetRightSpeed(70);
}

void Go_Back(void)
{
	Motor_SetLeftSpeed(-70);
	Motor_SetRightSpeed(-70);
}

void Go_Left(void)
{
	Motor_SetLeftSpeed(0);		
	Motor_SetRightSpeed(70);
}

void Go_Right(void)
{
	Motor_SetRightSpeed(0);
	Motor_SetLeftSpeed(70);		
}

//自转左
void Seif_Lefe(void)
{
	Motor_SetLeftSpeed(-70);
	Motor_SetRightSpeed(70);
}

//自转右
void Seif_Right(void)
{
	Motor_SetLeftSpeed(70);
	Motor_SetRightSpeed(-70);
}

void Car_Stop(void)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}
