//舵机模块
#include "stm32f10x.h"                  // Device header
#include "PWMServer.h"

void Servo_Init(void)
{
	PWMServer_Init();
}

void Servor_SetAngle(float Angle)
{
	Set_pwmserverccr3(Angle/180*2000+500);
}
