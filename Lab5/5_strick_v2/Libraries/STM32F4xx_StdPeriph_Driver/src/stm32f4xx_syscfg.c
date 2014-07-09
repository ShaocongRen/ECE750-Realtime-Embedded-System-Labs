/**
  ******************************************************************************
  * @file    stm32f4xx_syscfg.c
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    25-August-2011
  * @brief   This file provides firmware functions to manage the SYSCFG peripheral.
  *
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *                  
  *          This driver provides functions for:
  *          
  *          1. Remapping the memory accessible in the code area using SYSCFG_MemoryRemapConfig()
  *              
  *          2. Manage the EXTI lines connection to the GPIOs using SYSCFG_EXTILineConfig()
  *            
  *          3. Select the ETHERNET media interface (RMII/RII) using SYSCFG_ETH_MediaInterfaceConfig()
  *
  *  @note  SYSCFG APB clock must be enabled to get write access to SYSCFG registers,
  *         using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
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
#include "stm32f4xx_syscfg.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx : selects the GPIO port to be used as source for
  *          EXTI lines where x can be (A..I).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  *           This parameter can be EXTI_PinSourcex where x can be (0..15, except
  *           for EXTI_PortSourceGPIOI x can be (0..11).
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
  uint32_t tmp = 0x00;

  /* Check the parameters */
  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));

  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/   
