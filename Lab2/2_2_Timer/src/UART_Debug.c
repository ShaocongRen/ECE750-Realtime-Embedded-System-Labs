/*
 * UART_Debug.c
 *
 *  Created on: 2013-01-21
 *      Author: p6chen
 */

#include <string.h>
#include "UART_Debug.h"


SYS_GPIO_TypeDef * SYS_GPIOB = (SYS_GPIO_TypeDef *)((uint32_t)SYS_GPIOB_ADDR);
SYS_USART_TypeDef * SYS_USART1 = (SYS_USART_TypeDef *)((uint32_t)SYS_USART1_ADDR);

void SYS_Enable_GPIOB_CLK()
{
	volatile uint32_t *AHB1ENR = (uint32_t*)SYS_AHB1ENR_ADDR;
	*AHB1ENR |= 1<<1;	//Enable GPIO B
}

void SYS_Enable_USART1_CLK()
{
	volatile uint32_t *APB2ENR = (uint32_t*)SYS_APB2ENR_ADDR;
	*APB2ENR |= 1<<4;	//Enable USART 1
}

void SYS_Config_GPIOB()
{
	SYS_GPIOB->MODER &= ~(0x3 << (6*2));
	SYS_GPIOB->MODER |= (0x2 << (6*2));

	SYS_GPIOB->OTYPER &= ~(0x1 << 6);

	SYS_GPIOB->OSPEEDR &= ~(0x3 << (6*2));
	SYS_GPIOB->OSPEEDR |= (0x2 << (6*2));

	SYS_GPIOB->AFRL &= ~(0x7 << (6*4));
	SYS_GPIOB->AFRL |= (0x7 << (6*4));
}

void SYS_Config_USART1(uint32_t baud)
{
	SYS_USART1->CR1 &= ~(0x1<<12);	//8 data bits
	SYS_USART1->CR1 &= ~(0x1<<10);	//no parity bit
	SYS_USART1->CR1 |= (0x1<<3);	//tx enabled
	SYS_USART1->CR1 |= (0x1<<2);	//rx enabled
	SYS_USART1->CR2 &= ~(0x3<<12);	//1 stop bit
	SYS_USART1->CR3 &= ~(0x3<<8);	//hardware flow control disabled

	//baud rate calculations
	uint32_t tmp, integer, fraction;
	if((SYS_USART1->CR1 & (uint16_t)0x8000) != 0)	//8 oversamples
	{
		tmp = (SYS_PCLK_FREQ*25)/(baud*2);
		integer = (tmp/100);
		fraction = (((tmp-(integer*100))*8)+50)/100;
		SYS_USART1->BRR = (integer << 4) | (fraction & (uint8_t)0x7);
	}
	else	//16 oversamples
	{
		tmp = (SYS_PCLK_FREQ*25)/(baud*4);
		integer = (tmp/100);
		fraction = (((tmp-(integer*100))*16)+50)/100;
		SYS_USART1->BRR = (integer << 4) | (fraction & (uint8_t)0xF);
	}

	SYS_USART1->CR1 |= (0x1<<13);	//usart1 enabled
}

void SYS_Init_Debug()
{
	SYS_Enable_GPIOB_CLK();
	SYS_Enable_USART1_CLK();

	SYS_Config_GPIOB();
	SYS_Config_USART1(SYS_USART1_BAUD);
}

int SYS_Print(char * buf, int len)
{
	SYS_Init_Debug();

	int i;
	for (i=0;i<len;i++)
	{
		// wait until data register is empty
		while( !(SYS_USART1->SR & 0x00000040) );
		SYS_USART1->DR = ((char)*buf & 0x01FF);
		buf++;
	}

	return len;
}
