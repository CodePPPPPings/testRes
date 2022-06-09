#include "tim.h"


// �õ���ͨ�ö�ʱ��2
void TIM_init(uint32_t ARR,uint32_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//���ж���
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);
	
	// ����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	// ��ʱ��2��ʼ��
	TIM_TimeBaseInitStruct.TIM_Period = ARR;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct);
	
	// ʹ�ܶ�ʱ��2
	TIM_Cmd(TIM2,  ENABLE);
	// ����жϣ�����ϵͳ�����жϻ����������жϡ�
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	// ��ʱ���жϸ���
	TIM_ITConfig( TIM2,  TIM_IT_Update,  ENABLE);
	
	
	
	// ��ʱ��2 ���жϳ�ʼ��
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(& NVIC_InitStruct);


}




