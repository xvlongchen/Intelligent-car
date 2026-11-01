#ifndef _SERIAL_H
#define _SERIAL_H

#include "stdio.h"
void Serial_Init(void);
void Send_Date(uint8_t Byte);
void Send_Array(uint8_t *Array,uint16_t Length);
void Send_String(char *String);
void Send_Num(uint32_t Num,uint8_t Length);
void Send_sprintf(char *format, ...);


#endif
