#include "myusart.h"


void MyUsart_init(void)
{
	GPIO_InitTypeDef MyUsart_GPIO_InitStruct ;
	USART_InitTypeDef MyUSART_InitStruct; 
	// 这两个结构体的定义一定要放在时钟的之前，否者编译器警告
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA,ENABLE);
	
	
	// usart1  Tx  PA9
	MyUsart_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP ;
	MyUsart_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	MyUsart_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, & MyUsart_GPIO_InitStruct);
	
	//usart1 Rx  PA10
	MyUsart_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	MyUsart_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, & MyUsart_GPIO_InitStruct);
	
	
	// 初始化串口1
	MyUSART_InitStruct.USART_BaudRate = 115200 ;// 波特率
	MyUSART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	MyUSART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;// 收和发模式
	MyUSART_InitStruct.USART_Parity = USART_Parity_No;// 无奇偶校验位
	MyUSART_InitStruct.USART_StopBits = USART_StopBits_1;// 一位停止位
	MyUSART_InitStruct.USART_WordLength = USART_WordLength_8b;// 字长为8位的数据模式
	USART_Init(USART1, &MyUSART_InitStruct);
	
	USART_Cmd(USART1, ENABLE);// 使能串口1
	
}


// 发送一个字符
void Usart_send_byte(USART_TypeDef* USARTx,uint16_t Data)
{
	
	USART_SendData(USARTx,Data);
	while( USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET );


}
// 发送字符串，遇到字符串结尾标志‘\0’结束
void Usart_send_string(USART_TypeDef* USARTx,char *arr)
{
	uint16_t i = 0;
	
	do
	{
		Usart_send_byte(USARTx,*(arr + i));
		i++;
	
	}while(*(arr + i) != '\0');
	
	while( USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET );
	

}


//重定向 printf
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(uint8_t)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return (ch);
}



//重定向 输入 
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}


