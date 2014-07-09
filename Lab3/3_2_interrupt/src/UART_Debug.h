/*
 * UART_Debug.h
 *
 *  Created on: 2013-01-21
 *      Author: p6chen
 */

#ifndef UART_DEBUG_H_
#define UART_DEBUG_H_

#include <stdint.h>

#define SYS_GPIOB_ADDR		0x40020400
#define SYS_AHB1ENR_ADDR	0x40023830
#define SYS_APB2ENR_ADDR	0x40023844
#define SYS_USART1_ADDR		0x40011000
#define SYS_PCLK_FREQ		84000000//26880000
#define SYS_USART1_BAUD		115200
/*
 * GPIO Register Map
 */
typedef struct
{
	volatile uint32_t MODER;    	/*!< GPIO port mode register,              			Address offset: 0x00      */
	volatile uint32_t OTYPER;   	/*!< GPIO port output type register,        		Address offset: 0x04      */
	volatile uint32_t OSPEEDR; 		/*!< GPIO port output speed register,       		Address offset: 0x08      */
	volatile uint32_t PUPDR;   		/*!< GPIO port pull-up/pull-down register, 		 	Address offset: 0x0C      */
	volatile uint32_t IDR;      	/*!< GPIO port input data register,         		Address offset: 0x10      */
	volatile uint32_t ODR;      	/*!< GPIO port output data register,        		Address offset: 0x14      */
	volatile uint16_t BSSRL;  		/*!< GPIO port bit set/reset register (bits 15:0),  Address offset: 0x18      */
	volatile uint16_t BSSRH;  		/*!< GPIO port bit set/reset register (bits 31:16),	Address offset: 0x1A      */
	volatile uint32_t LCKR;     	/*!< GPIO port configuration lock register, 		Address offset: 0x1C      */
	volatile uint32_t AFRL;     	/*!< GPIO alternate function register (low),     	Address offset: 0x20	  */
	volatile uint32_t AFRH;		  	/*!< GPIO alternate function register (high),  		Address offset: 0x24	  */
} SYS_GPIO_TypeDef;

/*
 * USART Register Map
 */
typedef struct
{
	volatile uint16_t SR;       	/*!< USART Status register,                   		Address offset: 0x00	*/
	uint16_t      RESERVED0;  		/*!< Reserved, 0x02                                    		            	*/
	volatile uint16_t DR;         	/*!< USART Data register,                     		Address offset: 0x04 	*/
	uint16_t      RESERVED1; 		/*!< Reserved, 0x06                                               			*/
	volatile uint16_t BRR;        	/*!< USART Baud rate register,                		Address offset: 0x08 	*/
	uint16_t      RESERVED2;  		/*!< Reserved, 0x0A                                                			*/
	volatile uint16_t CR1;        	/*!< USART Control register 1,                		Address offset: 0x0C 	*/
	uint16_t      RESERVED3;  		/*!< Reserved, 0x0E                                                			*/
	volatile uint16_t CR2;        	/*!< USART Control register 2,                		Address offset: 0x10 	*/
	uint16_t      RESERVED4;  		/*!< Reserved, 0x12                                                			*/
	volatile uint16_t CR3;        	/*!< USART Control register 3,                		Address offset: 0x14 	*/
	uint16_t      RESERVED5;  		/*!< Reserved, 0x16                                                			*/
	volatile uint16_t GTPR;       	/*!< USART Guard time and prescaler register, 		Address offset: 0x18 	*/
	uint16_t      RESERVED6;  		/*!< Reserved, 0x1A                                                			*/
} SYS_USART_TypeDef;

void SYS_Enable_GPIOA_CLK();
void SYS_Enable_USART1_CLK();
void SYS_Config_GPIOB();
void SYS_Config_USART1(uint32_t baud);
void SYS_Init_Debug();
int SYS_Print(char * buf, int len);

#endif /* UART_DEBUG_H_ */
