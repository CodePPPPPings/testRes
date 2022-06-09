#include "stm32f10x.h"                  // Device header

#include "tim.h"
#include "myusart.h"
#include "ledtest.h"

uint8_t cnt =0;

int main (void)
{
	LED_GPIO_init();//led只是用来测试的
	TIM_init( 1999, 35999);
	MyUsart_init();
	
	
	while(1)
	{
		

	}

}

void TIM2_IRQHandler(void)
{
	static uint8_t time_cnt = 0;
	
	time_cnt +=1;
	
	
	if( TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET )
	{
		printf("time:%d\n",time_cnt);
		
	/*	led测试代码
		if(cnt == 0)
		{
			cnt =1;
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		}
		else if(cnt == 1)
		{
			cnt =0;
			GPIO_SetBits(GPIOB,GPIO_Pin_1); 

		
		}
		*/
		
	}
	
	TIM_ClearITPendingBit(TIM2,  TIM_IT_Update);
	
}


