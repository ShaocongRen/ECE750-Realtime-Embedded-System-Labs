/**
  ******************************************************************************
  * @file    stm32f4xx_syscfg.h
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    25-August-2011
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_SYSCFG_H
#define __STM32F4xx_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  
/** @defgroup SYSCFG_Exported_Constants 
  * @{
  */ 

/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 

#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)

/**
  * @}
  */ 


/** @defgroup SYSCFG_EXTI_Pin_Sources 
  * @{
  */ 
#define EXTI_PinSource0            ((uint8_t)0x00)
/**
  * @}
  */ 



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
 
void SYSCFG_DeInit(void);
void SYSCFG_MemoryRemapConfig(uint8_t SYSCFG_MemoryRemap);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void SYSCFG_ETH_MediaInterfaceConfig(uint32_t SYSCFG_ETH_MediaInterface); 
void SYSCFG_CompensationCellCmd(FunctionalState NewState); 
FlagStatus SYSCFG_GetCompensationCellStatus(void);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
