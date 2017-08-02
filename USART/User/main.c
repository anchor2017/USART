/**
  ******************************************************************************
  * @file    main.c
  * @author  caiyinmao
  * @version V1.0
  * @date    2017.8.2
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  *
  ******************************************************************************
  */ 
 
/*
睡眠模式使用GPIOC PC13作为触发源，GPIOB PC3,PC4 GPIOB PB0 LED灯显示
停止模式使用
*/

#include "bsp_usart1.h"


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	USART1_Config();			//用户自己写的函数，bsp里面
//	NVIC_Configuration();	//must use. if not will rise error
	
	while(1)
	{
	printf("--------------");
	}
}

/*********************************************END OF FILE**********************/
