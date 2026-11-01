//串口通信

#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdarg.h"

void Serial_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;       //TX输出脚，用复用推挽输出；RX数据输入脚，用输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;       //RX数据输入脚，用输入模式上拉
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;									//波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	 					//硬件流控制 不使用流控
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;							//模式 发送接收
	USART_InitStructure.USART_Parity=USART_Parity_No;					//校验位 选无
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8位字长
	USART_Init(USART1,&USART_InitStructure);
	
	//配置中断控制器
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);    //开启RXNE中断位到NVIC的输出
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);						//中断分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;				//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	//开启USART
	USART_Cmd(USART1,ENABLE);
}

//发送数据函数
void Send_Date(uint8_t Byte)
{
	//发送数据
	USART_SendData(USART1,Byte);
	
	//检验是否发送完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

//发送数组
void Send_Array(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Send_Date(Array[i]);
	}
}

//发送字符串
void Send_String(char *String)
{
	uint8_t i;
	for(i=0;String[i] !='\0';i++)
	{
		Send_Date(String[i]);
	}
}

//发送数字
uint32_t Serial_Pow(uint32_t x,uint32_t y)
{
	uint32_t Result=1;
	while(y--)
	{
		Result *=x;
	}
	return Result;
}
void Send_Num(uint32_t Num,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Send_Date(Num/Serial_Pow(10,Length-i-1)%10+'0');   //最后加偏移0x30
	}
}

//printf重定向
int fputc(int ch,FILE *f)
{
	Send_Date(ch);
	return ch;
}

//对sprintf进行封装
void Send_sprintf(char *format, ...)
{
	char String[100];
	
	//定义参数列表变量:类型名+变量名
	va_list arg;
	//从format位置接收参数表，放在arg里面
	va_start(arg,format);
	//打印位置：String 格式化字符串：format 参数表：arg
	vsprintf(String,format,arg);
	//释放参数表
	va_end(arg);
	Send_String(String);
}
