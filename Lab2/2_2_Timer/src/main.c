#include "stm32f4xx.h"
#include <stdio.h>

void TIM2_Config();
void TIM2_IRQHandler();
void GPIOA_Init();
void RCC_Configuration(void);

GPIO_InitTypeDef        GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
int                     flag = 0;
/*
 * Main Function (program point of entry)
 */
int main(void)
{
	//write your code here
    GPIOA_Init();
    TIM2_Config();   
    while(1);
    return 0;
}
void GPIOA_Init()
{
    //GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);  //PA0--TIM2_CH1
	//Enable GPIOA clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	//configure GPIO Pin A1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//initialize state to low
	GPIOA->ODR&=~(0x1<<1);
}
void TIM2_Config()
{
    //TIM2 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 27993-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 30 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//TIM2 interrupt enable
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_Cmd(TIM2,ENABLE);

	//Enable the TIM2 global interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {    
        TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
        
        //if(flag == 0){
        //    //GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        //    GPIOA->ODR|=(0x1<<1);
        //    flag = 1;
        //}
        //else if(flag == 1){
            //GPIO_SetBits(GPIOA, GPIO_Pin_1);
        //    GPIOA->ODR&=~(0x1<<1);
        //    flag = 0;
        //}
        GPIOA->ODR|=(0x1<<1);
        GPIOA->ODR&=~(0x1<<1);
        TIM2_Config();
    }  
}