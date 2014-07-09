/**
  ******************************************************************************
  * @file    stm32f4xx_tim.h
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    25-August-2011
  * @brief   This file contains all the functions prototypes for the TIM firmware 
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
#ifndef __STM32F4xx_TIM_H
#define __STM32F4xx_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TIM Time Base Init structure definition  
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.  
  */

typedef struct
{
  uint16_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  uint16_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1 and TIM8. */
} TIM_TimeBaseInitTypeDef; 

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  uint16_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_State */

  uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint32_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} TIM_OCInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

typedef struct
{

  uint16_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint16_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint16_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

/** 
  * @brief  BDTR structure definition 
  * @note   This structure is used only with TIM1 and TIM8.    
  */

typedef struct
{

  uint16_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_Lock_level */ 

  uint16_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not. 
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */

  uint16_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_Break_Polarity */

  uint16_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants 
  * @{
  */

/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */

 #define TIM_CKD_DIV1                       ((uint16_t)0x0000)
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode 
  * @{
  */

#define TIM_CounterMode_Up                 ((uint16_t)0x0000)

/**
  * @}
  */ 




/** @defgroup TIM_interrupt_sources 
  * @{
  */

#define TIM_IT_Update                      ((uint16_t)0x0001)

/**
  * @}
  */ 


/**
  * @}
  */ 
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
      



/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update                    ((uint16_t)0x0001)



/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* TimeBase management ********************************************************/
void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);


#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_TIM_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
