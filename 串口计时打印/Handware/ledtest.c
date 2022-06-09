#include "ledtest.h"


void LED_GPIO_init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef Test_Sensor_LEDinit;
	Test_Sensor_LEDinit.GPIO_Mode = GPIO_Mode_Out_PP ;
	Test_Sensor_LEDinit.GPIO_Pin = GPIO_Pin_1;
	Test_Sensor_LEDinit.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&Test_Sensor_LEDinit);

}

