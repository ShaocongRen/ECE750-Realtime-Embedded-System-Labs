#include "stm32f4xx.h"
#include <stdio.h>

//PortA initialization
void GPIOA_Init();
//PortB initialization
void GPIOB_Init();

/*
 * Main Function (program point of entry)
 */
int main(void)
{    
    uint8_t curFlag = 0;
    uint8_t preFlag = 0;
    GPIOA_Init();
    GPIOB_Init();

    while(1){
        curFlag = GPIOB->IDR & (0x1<<0);
        if((curFlag)  & (0 == preFlag)){
            
            //Following two clauses are to generate rising edges.
            //set bit i to 1
            GPIOA->ODR|=(0x1<<1);
            //set bit i to 0
            GPIOA->ODR&=~(0x1<<1);
        }
        preFlag = curFlag;
    }
    return 0;
}
void GPIOA_Init()
{
    GPIO_InitTypeDef    GPIO_InitStructure;
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
void GPIOB_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

	//Enable GPIOB clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	//configure GPIO Pin B0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}