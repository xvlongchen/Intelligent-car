#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Car.h"
#include "Serial.h"
#include "Servo.h"
#include "Chaoshengbo.h"
#include "Delay.h"

uint8_t RXData;

int main()
{
	Car_Init();
	Serial_Init();		//蓝牙初始化
	Servo_Init();		//舵机初始化
	Chaoshengbo_Init();   //超声波初始化
	while(1)
	{
//		uint16_t a;
//		a=Test_Distance();
//		Send_Num(a,3);
//		if(a<20)
//		{
//			Car_Stop();
//		}
//		Delay_ms(1000);
		
		Go_Ahead();
		uint16_t a=Test_Distance();
		Send_Num(a,3);
		if(a<15)
		{
			Car_Stop();
			Servor_SetAngle(0);
			Delay_ms(1000);
			uint16_t b=Test_Distance();
			Send_Num(b,3);
			if(b>15)
			{
				Servor_SetAngle(90);
				Delay_ms(1000);
				Seif_Right();
				Delay_ms(1000);
				Go_Ahead();
			}
			else
			{
				Servor_SetAngle(180);
				Delay_ms(1000);
				uint16_t c=Test_Distance();
				Send_Num(c,3);
				if(c>15)
				{
					Servor_SetAngle(90);
					Delay_ms(1000);
					Seif_Lefe();
					Delay_ms(1000);
					Go_Ahead();
				}
				else
				{
					Servor_SetAngle(90);
					while(1);
				}
			}
		}
		Delay_ms(1000);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		RXData=USART_ReceiveData(USART1);
		if(RXData==0x30)Car_Stop();
		if(RXData==0x31)Go_Ahead();		
		if(RXData==0x32)Go_Back();		
		if(RXData==0x33)Go_Left();		
		if(RXData==0x34)Go_Right();		
		if(RXData==0x35)Seif_Lefe();	
		if(RXData==0x36)Seif_Right();
		if(RXData==0x37)
		{
			Car_Stop();
			Servor_SetAngle(0);
		}
		if(RXData==0x38)
		{
			Car_Stop();
			Servor_SetAngle(90);
		}
		if(RXData==0x39)
		{
			Car_Stop();
			Servor_SetAngle(180);
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
