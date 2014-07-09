/**
  ******************************************************************************
  * @file    stm32f4xx_rcc.c
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    25-August-2011
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Reset and clock control (RCC) peripheral:           
  *           - Internal/external clocks, PLL, CSS and MCO configuration
  *           - System, AHB and APB busses clocks configuration
  *           - Peripheral clocks configuration
  *           - Interrupts and flags management
  *
  *  @verbatim
  *               
  *          ===================================================================
  *                               RCC specific features
  *          ===================================================================
  *    
  *          After reset the device is running from Internal High Speed oscillator 
  *          (HSI 16MHz) with Flash 0 wait state, Flash prefetch buffer, D-Cache 
  *          and I-Cache are disabled, and all peripherals are off except internal
  *          SRAM, Flash and JTAG.
  *           - There is no prescaler on High speed (AHB) and Low speed (APB) busses;
  *             all peripherals mapped on these busses are running at HSI speed.
  *       	  - The clock for all peripherals is switched off, except the SRAM and FLASH.
  *           - All GPIOs are in input floating state, except the JTAG pins which
  *             are assigned to be used for debug purpose.
  *        
  *          Once the device started from reset, the user application has to:        
  *           - Configure the clock source to be used to drive the System clock
  *             (if the application needs higher frequency/performance)
  *           - Configure the System clock frequency and Flash settings  
  *           - Configure the AHB and APB busses prescalers
  *           - Enable the clock for the peripheral(s) to be used
  *           - Configure the clock source(s) for peripherals which clocks are not
  *             derived from the System clock (I2S, RTC, ADC, USB OTG FS/SDIO/RNG)      
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
#include "stm32f4xx_rcc.h"


/**
  * @brief  Enables or disables the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  RCC_AHBPeriph: specifies the AHB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB1Periph_GPIOA:       GPIOA clock
  *            @arg RCC_AHB1Periph_GPIOB:       GPIOB clock 
  *            @arg RCC_AHB1Periph_GPIOC:       GPIOC clock
  *            @arg RCC_AHB1Periph_GPIOD:       GPIOD clock
  *            @arg RCC_AHB1Periph_GPIOE:       GPIOE clock
  *            @arg RCC_AHB1Periph_GPIOF:       GPIOF clock
  *            @arg RCC_AHB1Periph_GPIOG:       GPIOG clock
  *            @arg RCC_AHB1Periph_GPIOG:       GPIOG clock
  *            @arg RCC_AHB1Periph_GPIOI:       GPIOI clock
  *            @arg RCC_AHB1Periph_CRC:         CRC clock
  *            @arg RCC_AHB1Periph_BKPSRAM:     BKPSRAM interface clock
  *            @arg RCC_AHB1Periph_DMA1:        DMA1 clock
  *            @arg RCC_AHB1Periph_DMA2:        DMA2 clock
  *            @arg RCC_AHB1Periph_ETH_MAC:     Ethernet MAC clock
  *            @arg RCC_AHB1Periph_ETH_MAC_Tx:  Ethernet Transmission clock
  *            @arg RCC_AHB1Periph_ETH_MAC_Rx:  Ethernet Reception clock
  *            @arg RCC_AHB1Periph_ETH_MAC_PTP: Ethernet PTP clock
  *            @arg RCC_AHB1Periph_OTG_HS:      USB OTG HS clock
  *            @arg RCC_AHB1Periph_OTG_HS_ULPI: USB OTG HS ULPI clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB1_CLOCK_PERIPH(RCC_AHB1Periph));

  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->AHB1ENR |= RCC_AHB1Periph;
  }
  else
  {
    RCC->AHB1ENR &= ~RCC_AHB1Periph;
  }
}



/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2:   TIM2 clock
  *            @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *            @arg RCC_APB1Periph_TIM4:   TIM4 clock
  *            @arg RCC_APB1Periph_TIM5:   TIM5 clock
  *            @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *            @arg RCC_APB1Periph_TIM7:   TIM7 clock
  *            @arg RCC_APB1Periph_TIM12:  TIM12 clock
  *            @arg RCC_APB1Periph_TIM13:  TIM13 clock
  *            @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *            @arg RCC_APB1Periph_WWDG:   WWDG clock
  *            @arg RCC_APB1Periph_SPI2:   SPI2 clock
  *            @arg RCC_APB1Periph_SPI3:   SPI3 clock
  *            @arg RCC_APB1Periph_USART2: USART2 clock
  *            @arg RCC_APB1Periph_USART3: USART3 clock
  *            @arg RCC_APB1Periph_UART4:  UART4 clock
  *            @arg RCC_APB1Periph_UART5:  UART5 clock
  *            @arg RCC_APB1Periph_I2C1:   I2C1 clock
  *            @arg RCC_APB1Periph_I2C2:   I2C2 clock
  *            @arg RCC_APB1Periph_I2C3:   I2C3 clock
  *            @arg RCC_APB1Periph_CAN1:   CAN1 clock
  *            @arg RCC_APB1Periph_CAN2:   CAN2 clock
  *            @arg RCC_APB1Periph_PWR:    PWR clock
  *            @arg RCC_APB1Periph_DAC:    DAC clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *            @arg RCC_APB2Periph_TIM8:   TIM8 clock
  *            @arg RCC_APB2Periph_USART1: USART1 clock
  *            @arg RCC_APB2Periph_USART6: USART6 clock
  *            @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *            @arg RCC_APB2Periph_ADC2:   ADC2 clock
  *            @arg RCC_APB2Periph_ADC3:   ADC3 clock
  *            @arg RCC_APB2Periph_SDIO:   SDIO clock
  *            @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *            @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *            @arg RCC_APB2Periph_TIM9:   TIM9 clock
  *            @arg RCC_APB2Periph_TIM10:  TIM10 clock
  *            @arg RCC_APB2Periph_TIM11:  TIM11 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2:   TIM2 clock
  *            @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *            @arg RCC_APB1Periph_TIM4:   TIM4 clock
  *            @arg RCC_APB1Periph_TIM5:   TIM5 clock
  *            @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *            @arg RCC_APB1Periph_TIM7:   TIM7 clock
  *            @arg RCC_APB1Periph_TIM12:  TIM12 clock
  *            @arg RCC_APB1Periph_TIM13:  TIM13 clock
  *            @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *            @arg RCC_APB1Periph_WWDG:   WWDG clock
  *            @arg RCC_APB1Periph_SPI2:   SPI2 clock
  *            @arg RCC_APB1Periph_SPI3:   SPI3 clock
  *            @arg RCC_APB1Periph_USART2: USART2 clock
  *            @arg RCC_APB1Periph_USART3: USART3 clock
  *            @arg RCC_APB1Periph_UART4:  UART4 clock
  *            @arg RCC_APB1Periph_UART5:  UART5 clock
  *            @arg RCC_APB1Periph_I2C1:   I2C1 clock
  *            @arg RCC_APB1Periph_I2C2:   I2C2 clock
  *            @arg RCC_APB1Periph_I2C3:   I2C3 clock
  *            @arg RCC_APB1Periph_CAN1:   CAN1 clock
  *            @arg RCC_APB1Periph_CAN2:   CAN2 clock
  *            @arg RCC_APB1Periph_PWR:    PWR clock
  *            @arg RCC_APB1Periph_DAC:    DAC clock
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *            @arg RCC_APB2Periph_TIM8:   TIM8 clock
  *            @arg RCC_APB2Periph_USART1: USART1 clock
  *            @arg RCC_APB2Periph_USART6: USART6 clock
  *            @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *            @arg RCC_APB2Periph_ADC2:   ADC2 clock
  *            @arg RCC_APB2Periph_ADC3:   ADC3 clock
  *            @arg RCC_APB2Periph_SDIO:   SDIO clock
  *            @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *            @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *            @arg RCC_APB2Periph_TIM9:   TIM9 clock
  *            @arg RCC_APB2Periph_TIM10:  TIM10 clock
  *            @arg RCC_APB2Periph_TIM11:  TIM11 clock
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_RESET_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}


/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
