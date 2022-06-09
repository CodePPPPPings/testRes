#include "myusart.h"


void MyUsart_init(void)
{
	GPIO_InitTypeDef MyUsart_GPIO_InitStruct ;
	USART_InitTypeDef MyUSART_InitStruct; 
	// �������ṹ��Ķ���һ��Ҫ����ʱ�ӵ�֮ǰ�����߱���������
	
	
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
	
	
	// ��ʼ������1
	MyUSART_InitStruct.USART_BaudRate = 115200 ;// ������
	MyUSART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	MyUSART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;// �պͷ�ģʽ
	MyUSART_InitStruct.USART_Parity = USART_Parity_No;// ����żУ��λ
	MyUSART_InitStruct.USART_StopBits = USART_StopBits_1;// һλֹͣλ
	MyUSART_InitStruct.USART_WordLength = USART_WordLength_8b;// �ֳ�Ϊ8λ������ģʽ
	USART_Init(USART1, &MyUSART_InitStruct);
	
	USART_Cmd(USART1, ENABLE);// ʹ�ܴ���1
	
}


// ����һ���ַ�
void Usart_send_byte(USART_TypeDef* USARTx,uint16_t Data)
{
	
	USART_SendData(USARTx,Data);
	while( USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET );


}
// �����ַ����������ַ�����β��־��\0������
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


//�ض��� printf
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(uint8_t)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return (ch);
}



//�ض��� ���� 
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}


