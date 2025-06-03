/**
  ******************************************************************************
  * @file    stm32g4xx_nucleo_bus.c
  * @author  MCD Application Team
  * @brief   STM32G4xx_Nucleo board support package
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics International N.V.
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
  *    software, must execute solely and exclusively on micro-controller or
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

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_nucleo_errno.h"
#include "stm32g4xx_nucleo_bus.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32G4xx_NUCLEO
  * @{
  */

/** @defgroup STM32G4xx_NUCLEO_BUS STM32G4xx_NUCLEO BUS
  * @{
  */

#define DIV_ROUND_CLOSEST(x, d)  (((x) + ((d) / 2U)) / (d))

#define I2C_ANALOG_FILTER_ENABLE               1U
#define I2C_ANALOG_FILTER_DELAY_MIN            50U     /* ns */
#define I2C_ANALOG_FILTER_DELAY_MAX            260U    /* ns */
#define I2C_ANALOG_FILTER_DELAY_DEFAULT        2U      /* ns */

#define VALID_PRESC_NBR                        100U
#define PRESC_MAX                              16U
#define SCLDEL_MAX                             16U
#define SDADEL_MAX                             16U
#define SCLH_MAX                               256U
#define SCLL_MAX                               256U
#define I2C_DNF_MAX                            16U
#define NSEC_PER_SEC                           1000000000UL


/**
  * struct i2c_charac - private i2c specification timing
  * @rate: I2C bus speed (Hz)
  * @rate_min: 80% of I2C bus speed (Hz)
  * @rate_max: 100% of I2C bus speed (Hz)
  * @fall_max: Max fall time of both SDA and SCL signals (ns)
  * @rise_max: Max rise time of both SDA and SCL signals (ns)
  * @hddat_min: Min data hold time (ns)
  * @vddat_max: Max data valid time (ns)
  * @sudat_min: Min data setup time (ns)
  * @l_min: Min low period of the SCL clock (ns)
  * @h_min: Min high period of the SCL clock (ns)
  */
struct i2c_specs 
{
  uint32_t rate;
  uint32_t rate_min;
  uint32_t rate_max;
  uint32_t fall_max;
  uint32_t rise_max;
  uint32_t hddat_min;
  uint32_t vddat_max;
  uint32_t sudat_min;
  uint32_t l_min;
  uint32_t h_min;
};

enum i2c_speed 
{
  I2C_SPEED_STANDARD  = 0U, /* 100 kHz */
  I2C_SPEED_FAST      = 1U, /* 400 kHz */
  I2C_SPEED_FAST_PLUS = 2U, /* 1 MHz */
};

/**
  * struct i2c_setup - private I2C timing setup parameters
  * @rise_time: Rise time (ns)
  * @fall_time: Fall time (ns)
  * @dnf: Digital filter coefficient (0-16)
  * @analog_filter: Analog filter delay (On/Off)
  */
struct i2c_setup 
{
  uint32_t rise_time;
  uint32_t fall_time;
  uint32_t dnf;
  uint32_t analog_filter;
};

/**
  * struct i2c_timings - private I2C output parameters
  * @node: List entry
  * @presc: Prescaler value
  * @scldel: Data setup time
  * @sdadel: Data hold time
  * @sclh: SCL high period (master mode)
  * @scll: SCL low period (master mode)
  */
struct i2c_timings 
{
  uint32_t presc;
  uint32_t scldel;
  uint32_t sdadel;
  uint32_t sclh;
  uint32_t scll;
};

static const struct i2c_specs i2c_specs[] = 
{
  [I2C_SPEED_STANDARD] = 
  {
    .rate = 100000,
    .rate_min = 100000,
    .rate_max = 120000,
    .fall_max = 300,
    .rise_max = 1000,
    .hddat_min = 0,
    .vddat_max = 3450,
    .sudat_min = 250,
    .l_min = 4700,
    .h_min = 4000,
  },
  [I2C_SPEED_FAST] = 
  {
    .rate = 400000,
    .rate_min = 320000,
    .rate_max = 400000,
    .fall_max = 300,
    .rise_max = 300,
    .hddat_min = 0,
    .vddat_max = 900,
    .sudat_min = 100,
    .l_min = 1300,
    .h_min = 600,
  },
  [I2C_SPEED_FAST_PLUS] = 
  {
    .rate = 1000000,
    .rate_min = 800000,
    .rate_max = 1000000,
    .fall_max = 120,
    .rise_max = 120,
    .hddat_min = 0,
    .vddat_max = 450,
    .sudat_min = 50,
    .l_min = 500,
    .h_min = 260,
  },
};

static const struct i2c_setup i2c_user_setup[] = 
{
  [I2C_SPEED_STANDARD] = 
  {
    .rise_time = 400,
    .fall_time = 100,
    .dnf = I2C_ANALOG_FILTER_DELAY_DEFAULT,
    .analog_filter = 1,
  },
  [I2C_SPEED_FAST] = 
  {
    .rise_time = 250,
    .fall_time = 100,
    .dnf = I2C_ANALOG_FILTER_DELAY_DEFAULT,
    .analog_filter = 1,
  },
  [I2C_SPEED_FAST_PLUS] = 
  { 
    .rise_time = 60,
    .fall_time = 100,
    .dnf = I2C_ANALOG_FILTER_DELAY_DEFAULT,
    .analog_filter = 1,
  },
};

/** @defgroup STM32G4xx_NUCLEO_BUS_Exported_Variables
  * @{
  */
#ifdef HAL_I2C_MODULE_ENABLED
I2C_HandleTypeDef hbus_i2c1;
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
SPI_HandleTypeDef hbus_spi1;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
UART_HandleTypeDef hbus_uart1;
#endif /* HAL_UART_MODULE_ENABLED */


#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
static uint32_t IsSpi1MspCbValid = 0;
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
static uint32_t IsI2C1MspCbValid = 0;
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */ 
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
static uint32_t IsUart1MspCbValid = 0;
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */ 
/**
  * @}STM32G4xx_NUCLEO_BUS_Exported_Variables
  */


/** @defgroup STM32G4xx_NUCLEO_BUS_Private_Function_Prototypes
  * @{
  */
#ifdef HAL_I2C_MODULE_ENABLED
static void I2C1_MspInit(I2C_HandleTypeDef *hI2c);
static void I2C1_MspDeInit(I2C_HandleTypeDef *hI2c);
static uint32_t I2C_GetTiming(uint32_t clock_src_hz, uint32_t i2cfreq_hz);
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
static void SPI1_MspInit(SPI_HandleTypeDef* hspi);
static void SPI1_MspDeInit(SPI_HandleTypeDef* hspi);
static uint32_t SPI_GetPrescaler( uint32_t clk_src_hz, uint32_t baudrate_mbps );
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
static void UART1_MspInit  (UART_HandleTypeDef *huart);
static void UART1_MspDeInit(UART_HandleTypeDef *huart);
#endif /* HAL_UART_MODULE_ENABLED */
/**
  * @}STM32G4xx_NUCLEO_BUS_Private_Function_Prototypes
  */


/** @defgroup STM32G4xx_NUCLEO_BUS_Exported_Functions
  * @{
  */ 

/**
  * @brief  Additional IO pins configuration needed.
  * @param  none
  * @retval 0 in case of success, an error code otherwise
  */
int32_t HW_IO_Init(void)
{
#if 1
  /* !!!! Following code has no impact using X-NUCLEO-SAFEA1 board */
  /* !!!! Usefull using METKEY board (not anymore available) */
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configure GPIO pin : RST Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  HAL_Delay(50);
#endif

  return BSP_ERROR_NONE;
}

#ifdef HAL_I2C_MODULE_ENABLED
/**
  * @brief  MX I2C1 Inititialization as generated by CubeMX.
  * @param  phi2c : I2C handle.
  * @param  timing : I2C timings as described in the I2C peripheral V2 and V3.
  * @retval Prescaler dividor
  */
__weak HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *phi2c, uint32_t timing)
{
  phi2c->Init.Timing           = timing;
  phi2c->Init.OwnAddress1      = 0;
  phi2c->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  phi2c->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  phi2c->Init.OwnAddress2      = 0;
  phi2c->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  phi2c->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

  if(HAL_I2C_Init(phi2c) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (HAL_I2CEx_ConfigAnalogFilter(phi2c, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (HAL_I2CEx_ConfigDigitalFilter(phi2c, I2C_ANALOG_FILTER_DELAY_DEFAULT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Initializes I2C HAL.
  * @retval BSP status
  */
int32_t BSP_I2C1_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  hbus_i2c1.Instance  = I2C1;

  if (HAL_I2C_GetState(&hbus_i2c1) == HAL_I2C_STATE_RESET)
  {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
    /* Init the I2C Msp */
    I2C1_MspInit(&hbus_i2c1);
#else
    if(IsI2c1MspCbValid == 0U)
    {
      if(BSP_I2C1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif
    /* Init the I2C */
    if (MX_I2C1_Init(&hbus_i2c1, I2C_GetTiming (HAL_RCC_GetPCLK2Freq(), BUS_I2C1_FREQUENCY )) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else if( HAL_I2CEx_ConfigAnalogFilter(&hbus_i2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK) 
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitializes I2C HAL.
  * @retval BSP status
  */
int32_t BSP_I2C1_DeInit(void)
{ 
  int32_t ret  = BSP_ERROR_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
  /* DeInit the I2C */ 
  I2C1_MspDeInit(&hbus_i2c1);
#endif

  /* DeInit the I2C */ 
  if(HAL_I2C_DeInit(&hbus_i2c1) != HAL_OK)
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }

  return ret;  
}

/**
  * @brief  Check whether the I2C bus is ready.
  * @retval DevAddr : I2C device address
  * @retval Trials : Check trials number
  */
int32_t BSP_I2C1_IsReady(uint16_t DevAddr, uint32_t Trials)
{
  int32_t ret;

  if(HAL_I2C_IsDeviceReady(&hbus_i2c1, DevAddr, Trials, BUS_I2C1_POLL_TIMEOUT) != HAL_OK)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to write
  * @param  pData  Pointer to data buffer to write
  * @param  Length Data Length
  * @retval BSP status
  */
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;

  if(HAL_I2C_Mem_Write(&hbus_i2c1, (uint8_t)DevAddr,
                       (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,
                       (uint8_t *)pData, Length, BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  Read a register of the device through BUS
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to read
  * @param  pData  Pointer to data buffer to read
  * @param  Length Data Length
  * @retval BSP status
  */
int32_t  BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;

  if (HAL_I2C_Mem_Read(&hbus_i2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_8BIT, pData,
                       Length, BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to write
  * @param  pData  Pointer to data buffer to write
  * @param  Length Data Length
  * @retval BSP statu
  */
int32_t BSP_I2C1_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;

  if(HAL_I2C_Mem_Write(&hbus_i2c1, (uint8_t)DevAddr,
                       (uint16_t)Reg, I2C_MEMADD_SIZE_16BIT,
                       (uint8_t *)pData, Length, BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  Read a register of the device through BUS
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to read
  * @param  pData  Pointer to data buffer to read
  * @param  Length Data Length
  * @retval BSP status
  */
int32_t  BSP_I2C1_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;
  
  if (HAL_I2C_Mem_Read(&hbus_i2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_16BIT, pData,
                       Length, BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  Send data through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  pData  Pointer to data buffer to write
  * @param  Length Data Length
  * @retval BSP status
  */
int32_t BSP_I2C1_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;

  if (HAL_I2C_Master_Transmit(&hbus_i2c1, 
                              DevAddr, 
                              pData, 
                              Length, 
                              BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  Receive data through BUS
  * @param  DevAddr Device address on Bus.
  * @param  pData  Pointer to data buffer to read
  * @param  Length Data Length
  * @retval BSP status
  */
int32_t  BSP_I2C1_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret;
  uint32_t hal_error;

  if (HAL_I2C_Master_Receive(&hbus_i2c1, 
                              DevAddr, 
                              pData, 
                              Length, 
                              BUS_I2C1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  else
  {
    hal_error = HAL_I2C_GetError(&hbus_i2c1);
    if( hal_error == HAL_I2C_ERROR_AF)
    {
      return BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }
  return ret;
}

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default I2C1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterDefaultMspCallbacks (void)
{
  __HAL_I2C_RESET_HANDLE_STATE(&hbus_i2c1);

  /* Register MspInit Callback */
  if(HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPINIT_CB_ID, I2C1_MspInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPDEINIT_CB_ID, I2C1_MspDeInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsI2c1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}

/**
  * @brief Register I2C1 Bus Msp Callback registering
  * @param Callbacks     pointer to I2C1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterMspCallbacks (BSP_I2C1_Cb_t *Callbacks)
{
  __HAL_I2C_RESET_HANDLE_STATE(&hbus_i2c1);

  /* Register MspInit Callback */
  if(HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPINIT_CB_ID, Callbacks->pMspI2cInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_I2C_RegisterCallback(&hbus_i2c1, HAL_I2C_MSPDEINIT_CB_ID, Callbacks->pMspI2cDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsI2c1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief  Initializes MX SPI1 HAL.
  * @param  phspi SPI handler
  * @param  baudrate_presc : baud rate prescaler
  * @retval HAL status
  */
__weak HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef* phspi, uint32_t baudrate_presc)
{

  phspi->Init.Mode = SPI_MODE_MASTER;
  phspi->Init.Direction = SPI_DIRECTION_2LINES;
  phspi->Init.DataSize = SPI_DATASIZE_8BIT;
  phspi->Init.CLKPolarity = SPI_POLARITY_LOW;
  phspi->Init.CLKPhase = SPI_PHASE_1EDGE;
  phspi->Init.NSS = SPI_NSS_SOFT;
  phspi->Init.BaudRatePrescaler = baudrate_presc;
  phspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
  phspi->Init.TIMode = SPI_TIMODE_DISABLE;
  phspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  phspi->Init.CRCPolynomial = 7;

  return HAL_SPI_Init(phspi);
}

/**
  * @brief  Initializes SPI HAL.
  * @retval BSP status
  */
int32_t BSP_SPI1_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  hbus_spi1.Instance  = SPI1;

  if (HAL_SPI_GetState(&hbus_spi1) == HAL_SPI_STATE_RESET)
  {  
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
    /* Init the SPI Msp */
    SPI1_MspInit(&hbus_spi1);
#else
    if(IsSpi1MspCbValid == 0U)
    {
      if(BSP_SPI1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif  
    
    /* Init the SPI */
    if (MX_SPI1_Init(&hbus_spi1, SPI_GetPrescaler(HAL_RCC_GetPCLK2Freq(), BUS_SPI1_BAUDRATE )) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitializes SPI HAL.
  * @retval BSP status
  */
int32_t BSP_SPI1_DeInit(void)
{
  int32_t ret  = BSP_ERROR_BUS_FAILURE;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
  SPI1_MspDeInit(&hbus_spi1);
#endif  
  /* DeInit the SPI*/
  if(HAL_SPI_DeInit(&hbus_spi1) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;  
}

/**
  * @brief  Write Data through SPI BUS.
  * @param  pData  Pointer to data buffer to send
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_Send(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if(HAL_SPI_Transmit(&hbus_spi1, pData, Length, BUS_SPI1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

/**
  * @brief  Receive Data from SPI BUS
  * @param  pData  Pointer to data buffer to receive
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t  BSP_SPI1_Recv(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if(HAL_SPI_Receive(&hbus_spi1, pData, Length, BUS_SPI1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

/**
  * @brief  Send and Receive data to/from SPI BUS (Full duplex)
  * @param  pData  Pointer to data buffer to send/receive
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if(HAL_SPI_TransmitReceive(&hbus_spi1, pTxData,pRxData, Length, BUS_SPI1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default SPI1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_SPI1_RegisterDefaultMspCallbacks (void)
{
  __HAL_SPI_RESET_HANDLE_STATE(&hbus_spi1);

  /* Register MspInit Callback */
  if(HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPINIT_CB_ID, SPI1_MspInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPDEINIT_CB_ID, SPI1_MspDeInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsSpi1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}

/**
  * @brief Register SPI1 Bus Msp Callback 
  * @param Callbacks: pointer to SPI1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_SPI1_RegisterMspCallbacks(BSP_SPI1_Cb_t *Callbacks)
{ 
  __HAL_SPI_RESET_HANDLE_STATE(&hbus_spi1);

  /* Register MspInit Callback */
  if(HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPINIT_CB_ID, Callbacks->pMspSpiInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_SPI_RegisterCallback(&hbus_spi1, HAL_SPI_MSPDEINIT_CB_ID, Callbacks->pMspSpiDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsSpi1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}
#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Initializes MX UART1 HAL.
  * @param  phuart UART handler
  * @param  baudrate_presc : baud rate prescaler
  * @retval HAL status
  */
__weak HAL_StatusTypeDef MX_UART1_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *UART_Init) 
{
  /* USART configuration */
 huart->Init.BaudRate     = UART_Init->BaudRate;
 huart->Init.Mode         = UART_MODE_TX_RX;
 huart->Init.Parity       = (uint32_t)UART_Init->Parity;
 huart->Init.WordLength   = UART_Init->WordLength;
 huart->Init.StopBits     = (uint32_t)UART_Init->StopBits;
 huart->Init.HwFlowCtl    = (uint32_t)UART_Init->HwFlowCtl;
 huart->Init.OverSampling = UART_OVERSAMPLING_8;

 return HAL_UART_Init(huart);
}

/**
  * @brief  Initializes UART1 HAL.
  * @retval BSP status
  */
int32_t BSP_UART1_Init(BUS_UART_InitTypeDef *Init)
{
  int32_t ret = BSP_ERROR_NONE;

  hbus_uart1.Instance  = USART1;

  if (HAL_UART_GetState(&hbus_uart1) == HAL_UART_STATE_RESET)
  {  
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    /* Init the UART Msp */
    UART1_MspInit(&hbus_uart1);
#else
    if(IsUart1MspCbValid == 0U)
    {
      if(BSP_UART1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif  

    /* Init the UART */
    if (MX_UART1_Init(&hbus_uart1, Init) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
  }
  return ret;
}

/**
  * @brief  DeInitializes UART1 HAL.
  * @retval BSP status
  */
int32_t BSP_UART1_DeInit(void)
{
  int32_t ret  = BSP_ERROR_BUS_FAILURE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
  UART1_MspDeInit(&hbus_uart1);
#endif  
  /* DeInit the UART*/
  if(HAL_UART_DeInit(&hbus_uart1) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;  
}

/**
  * @brief  Write Data through UART1 BUS.
  * @param  pData  Pointer to data buffer to send
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t BSP_UART1_Send(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if(HAL_UART_Transmit(&hbus_uart1, pData, Length, BUS_UART1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

/**
  * @brief  Receive Data from UART1 BUS
  * @param  pData  Pointer to data buffer to receive
  * @param  Length Length of data in byte
  * @retval BSP status
  */
int32_t  BSP_UART1_Recv(uint8_t *pData, uint16_t Length)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;

  if(HAL_UART_Receive(&hbus_uart1, pData, Length, BUS_UART1_POLL_TIMEOUT) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default UART1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_UART1_RegisterDefaultMspCallbacks (void)
{
  __HAL_UART_RESET_HANDLE_STATE(&hbus_uart1);

  /* Register MspInit Callback */
  if(HAL_UART_RegisterCallback(&hbus_uart1, HAL_UART_MSPINIT_CB_ID, UART1_MspInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_UART_RegisterCallback(&hbus_uart1, HAL_UART_MSPDEINIT_CB_ID, UART1_MspDeInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsUart1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}

/**
  * @brief Register UART1 Bus Msp Callback 
  * @param Callbacks: pointer to UART1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_UART1_RegisterMspCallbacks(BSP_UART1_Cb_t *Callbacks)
{ 
  __HAL_UART_RESET_HANDLE_STATE(&hbus_uart1);
  
  /* Register MspInit Callback */
  if(HAL_UART_RegisterCallback(&hbus_uart1, HAL_UART_MUARTNIT_CB_ID, Callbacks->pMspSpiInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if(HAL_UART_RegisterCallback(&hbus_uart1, HAL_UART_MSPDEINIT_CB_ID, Callbacks->pMspSpiDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsUart1MspCbValid = 1;

  return BSP_ERROR_NONE;  
}
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */
#endif /* #if (USE_BSP_COM_FEATURE > 0) */
#endif /* HAL_UART_MODULE_ENABLED */

/**
  * @brief  Return system tick (ms) function .
  * @retval Current HAL time base time stamp
  */
int32_t BSP_GetTick(void)
{
  return (int32_t)HAL_GetTick();
}

/** @addtogroup STM32G4xx_NUCLEO_BUS_Private_Function_Prototypes
  * @{
  */

#ifdef HAL_I2C_MODULE_ENABLED
/**
  * @brief  Initializes I2C MSP.
  * @param  hI2c  I2C handler
  * @retval None
  */
static void I2C1_MspInit(I2C_HandleTypeDef *hI2c)
{
  GPIO_InitTypeDef  gpio_init;

  /* Enable I2C clock */
  BUS_I2C1_CLK_ENABLE();

  /* Enable GPIO clock */
  BUS_I2C1_SDA_GPIO_CLK_ENABLE();
  BUS_I2C1_SCL_GPIO_CLK_ENABLE();

  /* Configure I2C SDA Line */
  gpio_init.Pin = BUS_I2C1_SDA_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_OD;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_I2C1_SDA_GPIO_AF;
  HAL_GPIO_Init(BUS_I2C1_SDA_GPIO_PORT, &gpio_init);

  /* Configure I2C SCL Line */
  gpio_init.Pin = BUS_I2C1_SCL_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_OD;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_I2C1_SCL_GPIO_AF;
  HAL_GPIO_Init(BUS_I2C1_SCL_GPIO_PORT, &gpio_init);
}

/**
  * @brief  DeInitializes I2C MSP.
  * @param  hI2c  I2C handler
  * @retval None
  */
static void I2C1_MspDeInit(I2C_HandleTypeDef *hI2c)
{
  /* Disable I2C clock */
  __HAL_RCC_I2C1_CLK_DISABLE();

  /* DeInitialize peripheral GPIOs */
  HAL_GPIO_DeInit(BUS_I2C1_SDA_GPIO_PORT, BUS_I2C1_SDA_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_I2C1_SCL_GPIO_PORT, BUS_I2C1_SCL_GPIO_PIN);
}
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief  Initializes SPI MSP.
  * @param  hspi  SPI handler
  * @retval None
  */
static void SPI1_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef gpio_init;

  /* Peripheral clock enable */
  BUS_SPI1_CLK_ENABLE();

  /* Enable GPIO clock */
  BUS_SPI1_SCK_GPIO_CLK_ENABLE();
  BUS_SPI1_MOSI_GPIO_CLK_ENABLE();
  BUS_SPI1_MISO_GPIO_CLK_ENABLE();

  /* SPI1 GPIO Configuration */ 
  gpio_init.Pin = BUS_SPI1_SCK_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLDOWN;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_SPI1_SCK_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_SCK_GPIO_PORT, &gpio_init);

  gpio_init.Pin = BUS_SPI1_MISO_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLDOWN;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_SPI1_MISO_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_MISO_GPIO_PORT, &gpio_init);

  gpio_init.Pin = BUS_SPI1_MOSI_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLDOWN;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_SPI1_MOSI_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_MOSI_GPIO_PORT, &gpio_init);  
}

/**
  * @brief  DeInitializes SPI MSP.
  * @param  hspi  SPI handler
  * @retval None
  */
static void SPI1_MspDeInit(SPI_HandleTypeDef* hspi)
{
  /* Peripheral clock disable */
  BUS_SPI1_CLK_DISABLE();

  /* DeInitialize Peripheral GPIOs */
  HAL_GPIO_DeInit(BUS_SPI1_SCK_GPIO_PORT, BUS_SPI1_SCK_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_MISO_GPIO_PORT, BUS_SPI1_MISO_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_MOSI_GPIO_PORT, BUS_SPI1_MOSI_GPIO_PIN);  
}
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Initializes UART MSP.
  * @param  huart  UART handler
  * @retval None
  */
static void UART1_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef gpio_init;

  /* Peripheral clock enable */
  BUS_UART1_CLK_ENABLE();

  /* Enable GPIO clock */
  BUS_UART1_TX_GPIO_CLK_ENABLE();
  BUS_UART1_RX_GPIO_CLK_ENABLE();

  /* UART1 GPIO Configuration */ 
  gpio_init.Pin = BUS_UART1_TX_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLDOWN;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_UART1_TX_GPIO_AF;
  HAL_GPIO_Init(BUS_UART1_TX_GPIO_PORT, &gpio_init);

  gpio_init.Pin = BUS_UART1_RX_GPIO_PIN;
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLDOWN;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = BUS_UART1_RX_GPIO_AF;
  HAL_GPIO_Init(BUS_UART1_RX_GPIO_PORT, &gpio_init);
}

/**
  * @brief  DeInitializes UART MSP.
  * @param  huart  UART handler
  * @retval None
  */
static void UART1_MspDeInit(UART_HandleTypeDef* huart)
{
  /* Peripheral clock disable */
  BUS_UART1_CLK_DISABLE();

  /* DeInitialize Peripheral GPIOs */
  HAL_GPIO_DeInit(BUS_UART1_TX_GPIO_PORT, BUS_UART1_TX_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_UART1_RX_GPIO_PORT, BUS_UART1_RX_GPIO_PIN);
}
#endif /* #if (USE_BSP_COM_FEATURE > 0) */
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
/**
  * @brief  Convert the I2C Frequency into I2C timing.
  * @param  clock_src_hz : I2C source clock in HZ.
  * @param  i2cfreq_hz : I2C frequency in Hz.
  * @retval Prescaler dividor
  */        
static uint32_t I2C_GetTiming(uint32_t clock_src_hz, uint32_t i2cfreq_hz)
{
  uint32_t ret = 0;
  uint32_t speed = 0;
  uint32_t is_valid_speed = 0; 
  uint32_t p_prev = PRESC_MAX;
  uint32_t i2cclk;
  uint32_t i2cspeed;
  uint32_t clk_error_prev;
  uint32_t tsync;
  uint32_t af_delay_min, af_delay_max;
  uint32_t dnf_delay;
  uint32_t clk_min, clk_max;
  int32_t sdadel_min, sdadel_max;
  int32_t scldel_min;
  struct i2c_timings *s;
  struct i2c_timings valid_timing[VALID_PRESC_NBR];
  uint32_t p, l, a, h;
  uint32_t valid_timing_nbr = 0;  

  if((clock_src_hz == 0U) || (i2cfreq_hz == 0U))
  {
    ret = 0;
  }
  else
  {
    for (uint32_t i =0 ; i <=  (uint32_t)I2C_SPEED_FAST_PLUS ; i++)
    {
      if ((i2cfreq_hz >= i2c_specs[i].rate_min) &&
          (i2cfreq_hz <= i2c_specs[i].rate_max))
      {
        is_valid_speed = 1;
        speed = i;
        break;
      }
    }

    if(is_valid_speed != 0U)  
    {
      i2cclk = DIV_ROUND_CLOSEST(NSEC_PER_SEC, clock_src_hz);
      i2cspeed = DIV_ROUND_CLOSEST(NSEC_PER_SEC, i2cfreq_hz);

      clk_error_prev = i2cspeed;

      /*  Analog and Digital Filters */
      af_delay_min =((i2c_user_setup[speed].analog_filter == 1U)? I2C_ANALOG_FILTER_DELAY_MIN : 0U);
      af_delay_max =((i2c_user_setup[speed].analog_filter == 1U)? I2C_ANALOG_FILTER_DELAY_MAX : 0U);

      dnf_delay = i2c_user_setup[speed].dnf * i2cclk;
      
      sdadel_min = (int32_t)i2c_user_setup[speed].fall_time - (int32_t)i2c_specs[speed].hddat_min -
                   (int32_t)af_delay_min - (int32_t)(((int32_t)i2c_user_setup[speed].dnf + 3) * (int32_t)i2cclk);

      sdadel_max = (int32_t)i2c_specs[speed].vddat_max - (int32_t)i2c_user_setup[speed].rise_time -
                   (int32_t)af_delay_max - (int32_t)(((int32_t)i2c_user_setup[speed].dnf + 4) * (int32_t)i2cclk);

      scldel_min = (int32_t)i2c_user_setup[speed].rise_time + (int32_t)i2c_specs[speed].sudat_min;

      if (sdadel_min <= 0)
      {
        sdadel_min = 0;
      }

      if (sdadel_max <= 0)
      {
        sdadel_max = 0;
      }

      /* Compute possible values for PRESC, SCLDEL and SDADEL */
      for (p = 0; p < PRESC_MAX; p++) 
      {
        for (l = 0; l < SCLDEL_MAX; l++) 
        {
          uint32_t scldel = (l + 1U) * (p + 1U) * i2cclk;

          if (scldel < (uint32_t)scldel_min)
          {
            continue;
          }

          for (a = 0; a < SDADEL_MAX; a++) 
          {
            uint32_t sdadel = (a * (p + 1U) + 1U) * i2cclk;

            if (((sdadel >= (uint32_t)sdadel_min) && (sdadel <= (uint32_t)sdadel_max))&& (p != p_prev)) 
            {
              valid_timing[valid_timing_nbr].presc = p;
              valid_timing[valid_timing_nbr].scldel = l;
              valid_timing[valid_timing_nbr].sdadel = a;
              p_prev = p;
              valid_timing_nbr ++;

              if(valid_timing_nbr >= VALID_PRESC_NBR)
              {
                /* max valid timing buffer is full, use only these values*/
                goto  Compute_scll_sclh;
              }
            }
          }
        }
      }

      if (valid_timing_nbr == 0U) 
      {
        return 0;
      }

    Compute_scll_sclh: 
      tsync = af_delay_min + dnf_delay + (2U * i2cclk);
      s = NULL;
      clk_max = NSEC_PER_SEC / i2c_specs[speed].rate_min;
      clk_min = NSEC_PER_SEC / i2c_specs[speed].rate_max;

      /*
      * Among Prescaler possibilities discovered above figures out SCL Low
      * and High Period. Provided:
      * - SCL Low Period has to be higher than Low Period of tehs SCL Clock
      *   defined by I2C Specification. I2C Clock has to be lower than
      *   (SCL Low Period - Analog/Digital filters) / 4.
      * - SCL High Period has to be lower than High Period of the SCL Clock
      *   defined by I2C Specification
      * - I2C Clock has to be lower than SCL High Period
      */
      for (uint32_t count = 0; count < valid_timing_nbr; count++) 
      {          
        uint32_t prescaler = (valid_timing[count].presc + 1U) * i2cclk;

        for (l = 0; l < SCLL_MAX; l++) 
        {
          uint32_t tscl_l = (l + 1U) * prescaler + tsync;

          if ((tscl_l < i2c_specs[speed].l_min) || (i2cclk >= ((tscl_l - af_delay_min - dnf_delay) / 4U))) 
          {
            continue;
          }

          for (h = 0; h < SCLH_MAX; h++) 
          {
            uint32_t tscl_h = (h + 1U) * prescaler + tsync;
            uint32_t tscl = tscl_l + tscl_h + i2c_user_setup[speed].rise_time + i2c_user_setup[speed].fall_time;

            if ((tscl >= clk_min) && (tscl <= clk_max) && (tscl_h >= i2c_specs[speed].h_min) && (i2cclk < tscl_h)) 
            {
              int32_t clk_error = (int32_t)tscl - (int32_t)i2cspeed;

              if (clk_error < 0)
              {
                clk_error = -clk_error;
              }

              /* save the solution with the lowest clock error */
              if ((uint32_t)clk_error < clk_error_prev) 
              {
                clk_error_prev = (uint32_t)clk_error;
                valid_timing[count].scll = l;
                valid_timing[count].sclh = h;
                s = &valid_timing[count];
              }
            }
          }
        }
      }

      if (s == NULL) 
      {
        return 0;
      }

      ret = ((s->presc  & 0x0FU) << 28) |
            ((s->scldel & 0x0FU) << 20) |
            ((s->sdadel & 0x0FU) << 16) |
            ((s->sclh & 0xFFU) << 8) |
            ((s->scll & 0xFFU) << 0);
    }
  }

  return ret;
}
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief  Convert the SPI baudrate into prescaler.
  * @param  clock_src_hz : SPI source clock in HZ.
  * @param  baudrate_mbps : SPI baud rate in mbps.
  * @retval Prescaler dividor
  */
static uint32_t SPI_GetPrescaler( uint32_t clock_src_hz, uint32_t baudrate_mbps )
{
  uint32_t divisor = 0;
  uint32_t spi_clk = clock_src_hz;
  uint32_t presc = 0;

  static const uint32_t baudrate[]=
  {
    SPI_BAUDRATEPRESCALER_2,  
    SPI_BAUDRATEPRESCALER_4,      
    SPI_BAUDRATEPRESCALER_8,      
    SPI_BAUDRATEPRESCALER_16,     
    SPI_BAUDRATEPRESCALER_32,     
    SPI_BAUDRATEPRESCALER_64,     
    SPI_BAUDRATEPRESCALER_128,   
    SPI_BAUDRATEPRESCALER_256, 
  };

  while( spi_clk > baudrate_mbps)
  {
    presc = baudrate[divisor];
    if (++divisor > 7)
      break;

    spi_clk= ( spi_clk >> 1);
  }

  return presc;
}
#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}STM32G4xx_NUCLEO_BUS_Private_Function_Prototypes
  */


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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
