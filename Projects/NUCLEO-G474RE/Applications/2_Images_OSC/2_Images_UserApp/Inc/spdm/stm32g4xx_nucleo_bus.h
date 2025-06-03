/**
  ******************************************************************************
  * @file    stm32g4xx_nucleo_bus.h
  * @author  MCD Application Team
  * @brief   STM32G4xx_Nucleo  board support package
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_NUCLEO_BUS_H
#define STM32G4xx_NUCLEO_BUS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_nucleo_conf.h"
#include "stm32g4xx_nucleo.h"

/** @addtogroup BSP
  * @{
  */


/** @addtogroup STM32G4xx_NUCLEO
  * @{
  */


/** @addtogroup STM32G4xx_NUCLEO_BUS
  * @{
  */


/** @defgroup STM32G4xx_NUCLEO_BUS_Exported_Constants STM32G4xx NUCLEO BUS Exported Constants
  * @{
  */
#ifndef BUS_I2C1_FREQUENCY
   #define BUS_I2C1_FREQUENCY  100000U /* Frequency of I2Cn = 100 KHz*/
#endif


#ifndef BUS_SPI1_BAUDRATE 
   #define BUS_SPI1_BAUDRATE  10000000U /* baud rate of SPIn = 10 Mbps*/
#endif

#define BUS_SPI1_INSTANCE                       SPI1

#define BUS_SPI1_CLK_ENABLE()                   __HAL_RCC_SPI1_CLK_ENABLE()
#define BUS_SPI1_CLK_DISABLE()                  __HAL_RCC_SPI1_CLK_DISABLE()

#define BUS_SPI1_SCK_GPIO_PIN                   GPIO_PIN_5
#define BUS_SPI1_MISO_GPIO_PIN                  GPIO_PIN_6
#define BUS_SPI1_MOSI_GPIO_PIN                  GPIO_PIN_7

#define BUS_SPI1_SCK_GPIO_PORT                  GPIOA
#define BUS_SPI1_MISO_GPIO_PORT                 GPIOA
#define BUS_SPI1_MOSI_GPIO_PORT                 GPIOA

#define BUS_SPI1_SCK_GPIO_AF                    GPIO_AF5_SPI1
#define BUS_SPI1_MOSI_GPIO_AF                   GPIO_AF5_SPI1
#define BUS_SPI1_MISO_GPIO_AF                   GPIO_AF5_SPI1

#define BUS_SPI1_SCK_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define BUS_SPI1_MOSI_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define BUS_SPI1_MISO_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

#ifndef BUS_SPI1_POLL_TIMEOUT
  #define BUS_SPI1_POLL_TIMEOUT                 0x1000
#endif

#define BUS_I2C1_INSTANCE                       I2C1

#define BUS_I2C1_CLK_ENABLE()                   __HAL_RCC_I2C1_CLK_ENABLE()
#define BUS_I2C1_CLK_DISABLE()                  __HAL_RCC_I2C1_CLK_DISABLE()

#define BUS_I2C1_SDA_GPIO_PIN                   GPIO_PIN_9
#define BUS_I2C1_SCL_GPIO_PIN                   GPIO_PIN_8

#define BUS_I2C1_SDA_GPIO_PORT                  GPIOB
#define BUS_I2C1_SCL_GPIO_PORT                  GPIOB

#define BUS_I2C1_SDA_GPIO_AF                    GPIO_AF4_I2C1
#define BUS_I2C1_SCL_GPIO_AF                    GPIO_AF4_I2C1

#define BUS_I2C1_SDA_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define BUS_I2C1_SCL_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#ifndef BUS_I2C1_POLL_TIMEOUT
   #define BUS_I2C1_POLL_TIMEOUT                0x1000U
#endif

#define BUS_UART1_INSTANCE                      UART1

#define BUS_UART1_CLK_ENABLE()                  __HAL_RCC_USART1_CLK_ENABLE()
#define BUS_UART1_CLK_DISABLE()                 __HAL_RCC_USART1_CLK_DISABLE()

#define BUS_UART1_TX_GPIO_PIN                   GPIO_PIN_9
#define BUS_UART1_RX_GPIO_PIN                   GPIO_PIN_10

#define BUS_UART1_TX_GPIO_PORT                  GPIOA
#define BUS_UART1_RX_GPIO_PORT                  GPIOA

#define BUS_UART1_TX_GPIO_AF                    GPIO_AF7_USART1
#define BUS_UART1_RX_GPIO_AF                    GPIO_AF7_USART1

#define BUS_UART1_TX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define BUS_UART1_RX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#ifndef BUS_UART1_POLL_TIMEOUT
   #define BUS_UART1_POLL_TIMEOUT               9600U
#endif

#define BUS_UART_InitTypeDef                    MX_UART_InitTypeDef
/**
  * @}STM32G4xx_NUCLEO_BUS_Exported_Constants
  */


/** @defgroup STM32G4xx_NUCLEO_BUS_Private_Types STM32G4xx NUCLEO BUS Private types
  * @{
  */
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
typedef struct
{
  pSPI_CallbackTypeDef  pMspInitCb;
  pSPI_CallbackTypeDef  pMspDeInitCb;
}BSP_SPI_Cb_t;
#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1) 
typedef struct
{
  pI2C_CallbackTypeDef  pMspInitCb;
  pI2C_CallbackTypeDef  pMspDeInitCb;
}BSP_I2C_Cb_t;
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */

#if (USE_HAL_UART_REGISTER_CALLBACKS  == 1)
typedef struct
{
  pUART_CallbackTypeDef  pMspInitCb;
  pUART_CallbackTypeDef  pMspDeInitCb;
}BSP_UART_Cb_t;
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */
/**
  * @}STM32G4xx_NUCLEO_BUS_Private_Types
  */


/** @defgroup STM32G4xx_NUCLEO_LOW_LEVEL_Exported_Variables LOW LEVEL Exported Constants
  * @{
  */
#ifdef HAL_I2C_MODULE_ENABLED
extern I2C_HandleTypeDef hbus_i2c1;
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
extern SPI_HandleTypeDef hbus_spi1;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
extern UART_HandleTypeDef hbus_uart1;
#endif /* HAL_UART_MODULE_ENABLED */

/**
  * @}STM32G4xx_NUCLEO_LOW_LEVEL_Exported_Variables
  */


/** @addtogroup STM32G4xx_NUCLEO_BUS_Exported_Functions
  * @{
  */
int32_t HW_IO_Init(void);

#ifdef HAL_I2C_MODULE_ENABLED
HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *phi2c, uint32_t timing);
int32_t BSP_I2C1_Init(void);
int32_t BSP_I2C1_DeInit(void);
int32_t BSP_I2C1_IsReady(uint16_t DevAddr, uint32_t Trials);
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef* phspi, uint32_t baudrate_presc);
int32_t BSP_SPI1_Init(void);
int32_t BSP_SPI1_DeInit(void);
int32_t BSP_SPI1_Send(uint8_t *pData, uint16_t Length);
int32_t BSP_SPI1_Recv(uint8_t *pData, uint16_t Length);
int32_t BSP_SPI1_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t Length);
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#if (USE_BSP_COM_FEATURE > 0)
__weak HAL_StatusTypeDef MX_UART1_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *UART_Init);
int32_t BSP_UART1_Init(BUS_UART_InitTypeDef *Init);
int32_t BSP_UART1_DeInit(void);
int32_t BSP_UART1_Send(uint8_t *pData, uint16_t Length);
int32_t BSP_UART1_Recv(uint8_t *pData, uint16_t Length);
#endif /* #if (USE_BSP_COM_FEATURE > 0) */
#endif /* HAL_UART_MODULE_ENABLED */

int32_t BSP_GetTick(void);

#if defined(HAL_I2C_MODULE_ENABLED) && (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
int32_t BSP_I2C1_RegisterDefaultMspCallbacks (void);
int32_t BSP_I2C1_RegisterMspCallbacks (BSP_I2C_Cb_t *Callbacks);
#endif /* HAL_I2C_MODULE_ENABLED && (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */

#if defined(HAL_SPI_MODULE_ENABLED) && (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
int32_t BSP_SPI1_RegisterDefaultMspCallbacks (void);
int32_t BSP_SPI1_RegisterMspCallbacks (BSP_SPI_Cb_t *Callbacks);
#endif /* HAL_SPI_MODULE_ENABLED && (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */

#if defined(HAL_UART_MODULE_ENABLED) && (USE_HAL_UART_REGISTER_CALLBACKS == 1)
int32_t BSP_UART1_RegisterDefaultMspCallbacks (void);
int32_t BSP_UART1_RegisterMspCallbacks (BSP_UART_Cb_t *Callbacks);
#endif /* HAL_UART_MODULE_ENABLED && (USE_HAL_UART_REGISTER_CALLBACKS == 1) */
/**
  * @}STM32G4xx_NUCLEO_BUS_Exported_Functions
  */


/**
  * @}STM32G4xx_NUCLEO_BUS
  */

/**
  * @}STM32G4xx_NUCLEO
  */


/**
  * @}BSP
  */


#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_NUCLEO_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
