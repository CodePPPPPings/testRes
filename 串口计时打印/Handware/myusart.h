#ifndef __MYUSART_H_
#define __MYUSART_H_

#include "stm32f10x.h"                  // Device header
#include <stdio.h>


void MyUsart_init(void);
void Usart_send_byte(USART_TypeDef* USARTx,uint16_t Data);
void Usart_send_string(USART_TypeDef* USARTx,char *arr);
int fputc(int ch,FILE *f);
int fgetc(FILE *f);






#endif


