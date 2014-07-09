/**
  ******************************************************************************
  * @file    stm32f4xx_gpio.c
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    25-August-2011
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:           
  *           - Initialization and Configuration
  *           - GPIO Read and Write
  *           - GPIO Alternate functions configuration
  * 
  *  @verbatim
  *
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================       
  *           1. Enable the GPIO AHB clock using the following function
  *                RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);
  *             
  *           2. Configure the GPIO pin(s) using GPIO_Init()
  *              Four possible configuration are available for each pin:
  *                - Input: Floating, Pull-up, Pull-down.
  *                - Output: Push-Pull (Pull-up, Pull-down or no Pull)
  *                          Open Drain (Pull-up, Pull-down or no Pull).
  *                  In output mode, the speed is configurable: 2 MHz, 25 MHz,
  *                  50 MHz or 100 MHz.
  *                - Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull)
  *                                      Open Drain (Pull-up, Pull-down or no Pull).
  *                - Analog: required mode when a pin is to be used as ADC channel
  *                          or DAC output.
  * 
  *          3- Peripherals alternate function:
  *              - For ADC and DAC, configure the desired pin in analog mode using 
  *                  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN;
  *              - For other peripherals (TIM, USART...):
  *                 - Connect the pin to the desired peripherals' Alternate 
  *                   Function (AF) using GPIO_PinAFConfig() function
  *                 - Configure the desired pin in alternate function mode using
  *                   GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  *                 - Select the type, pull-up/pull-down and output speed via 
  *                   GPIO_PuPd, GPIO_OType and GPIO_Speed members
  *                 - Call GPIO_Init() function
  *        
  *          4. To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
  *          
  *          5. To set/reset the level of a pin configured in output mode use
  *             GPIO_SetBits()/GPIO_ResetBits()
  *               
  *          6. During and just after reset, the alternate functions are not 
  *             active and the GPIO pins are configured in input floating mode
  *             (except JTAG pins).
  *
  *          7. The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as 
  *             general-purpose (PC14 and PC15, respectively) when the LSE
  *             oscillator is off. The LSE has priority over the GPIO function.
  *
  *          8. The HSE oscillator pins OSC_IN/OSC_OUT can be used as 
  *             general-purpose PH0 and PH1, respectively, when the HSE 
  *             oscillator is off. The HSE has priority over the GPIO function.
  *             
  *  @endverbatim        
  *
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_gpio.h"

/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /* -------------------------Configure the port pins---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
