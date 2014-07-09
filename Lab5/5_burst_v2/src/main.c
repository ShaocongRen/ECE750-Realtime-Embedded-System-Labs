#include "stm32f4xx.h"
#include <stdio.h>

void EXTI0_GPIOB_Init();
void TIM2_Config();
void GPIOA_Init();
void GPIOB_Init();
int i;
// NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
int counter = 0;

/*
 * Main Function (program point of entry)
 */
int main(void)
{
    TIM2_Config();
    
    GPIOA_Init();
    GPIOB_Init();
    EXTI0_GPIOB_Init();
    while(1);
    return 0;
}
void GPIOA_Init()
{
    GPIO_InitTypeDef        GPIO_InitStructure;
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
	//GPIOA->ODR&=~(0x1<<1);
}

void GPIOB_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable GPIOB clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	//configure GPIO Pin B0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void EXTI0_GPIOB_Init()    //EXTI0 on Pin PB0
{
    NVIC_InitTypeDef NVIC_InitStructure;
	//EXTI_InitTypeDef EXTI_InitStructure;

	//Enable SysCfg Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	//connect EXTI line 0 to PB0 pin
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource0);

	//Configure EXTI 0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//Configure EXTI 0 in NVIC
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM2_Config()
{
    //TIM2 clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 7000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 3000 - 1;
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
void EXTI0_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line0))
    {
        if(counter<5){
            //set bit i to 0
            GPIOA->ODR&=~(0x1<<1);
            //set bit i to 1
            GPIOA->ODR|=(0x1<<1);
            
        }
        else{
            
            EXTI->IMR &=~(0x1<<0);
        }   
        counter++;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    
    
}
void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {    
        TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
        counter = 0;
        EXTI->IMR |=(0x1<<0);
    }
}