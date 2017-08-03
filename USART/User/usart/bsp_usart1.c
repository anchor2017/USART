/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  caiyinmao
  * @version V1.0
  * @date    2017.8
  * @brief   usart应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  *
  ******************************************************************************
  */

#include "bsp_usart1.h"

/**
  * @brief  串口配置函数
  * @param  无
  * @retval 无
  */
void USART1_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;					//TX PD8
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;			//RX PD9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART3, &USART_InitStructure);
	
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  串口的NVIC配置
  * @param  无
  * @retval 无
  */
void NVIC_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  c库函数fputc重定向
  * @param  无
  * @retval 无
  */
int fputc(int ch, FILE* fp)
{
	USART_SendData(USART3, (uint8_t)ch);
	
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	
	return (ch);
}

/**
  * @brief  c库函数fgetc重定向
  * @param  无
  * @retval 无
  */
int fgetc(FILE* fp)
{
	while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)));
	
	return (int)USART_ReceiveData(USART1);
}

