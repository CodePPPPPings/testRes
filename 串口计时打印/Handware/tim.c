#include "tim.h"


// 用的是通用定时器2
void TIM_init(uint32_t ARR,uint32_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//设中断组
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);
	
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	// 定时器2初始化
	TIM_TimeBaseInitStruct.TIM_Period = ARR;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct);
	
	// 使能定时器2
	TIM_Cmd(TIM2,  ENABLE);
	// 清除中断，避免系统启动中断会立即产生中断、
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	// 定时器中断更新
	TIM_ITConfig( TIM2,  TIM_IT_Update,  ENABLE);
	
	
	
	// 定时器2 的中断初始化
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(& NVIC_InitStruct);


}




