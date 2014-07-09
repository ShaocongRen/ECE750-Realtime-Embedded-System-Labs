#include "stm32f4xx.h"
#include <stdio.h>

GPIO_InitTypeDef GPIO_InitStructure;
//void Delay(__IO uint32_t N);
//void GPIOA_Init();

void GPIOA_Init()
{
    
    //Enable GPIOA clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	//configure GPIO Pin A1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//initialize state to low
	GPIOA->ODR&=~(0x1<<1);
}
void Delay(__IO uint32_t N)
{
    int i;
	for(;N>0;N--)
	{
		for(i=0;i<1000;i++);
	}
}
/*
 * Main Function (program point of entry)
 */
int main(void)
{
    //write your code here
    GPIOA_Init();
    while(1){
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        Delay(129);
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    return 0;
}
