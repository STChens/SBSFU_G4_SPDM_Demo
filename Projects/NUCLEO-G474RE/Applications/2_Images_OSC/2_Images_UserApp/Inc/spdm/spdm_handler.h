/**
  ******************************************************************************
  * @file           : spdm_handler.h
  * @brief          : Header for spdm_handler.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef INC_SPDM_HANDLER_H_
#define INC_SPDM_HANDLER_H_

#define SPDM_CMD_GET_CERTIFICATE 	0x82
#define SPDM_CMD_CHALLENGE		 	0x83
#define SPDM_CMD_GET_VERSION 		0x84
#define SPDM_CMD_GET_MESUREMENTS 	0xE0
#define SPDM_CMD_GET_CAPABILITIES 	0xE1
#define SPDM_CMD_NEGOTIATE_ALGO 	0xE3
#define TEST_CMD				 	0xFA
#define TEST_QUERY_CURVE			0x01
#define TEST_QUERY_ECHO				0x00
#define TEST_HOST_KEY				0x02
#define TEST_VERIFY_SIGNATURE		0x03

#define SPDM_RSP_CERTIFICATE 	0x02
#define SPDM_RSP_CHALLENGE	 	0x03
#define SPDM_RSP_VERSION 	 	0x04
#define SPDM_RSP_MEASUREMENTS  	0x60
#define SPDM_RSP_CAPABILITIES 	0x61
#define SPDM_RSP_ALGORITHMS 	0x63
#define SPDM_RSP_ERROR 		 	0x7F

#define SPDM_ERROR_CODE_UNSPECIFIED 	 0x05

#define SPDM_GENERIC_VERSION 0x10
#define SPDM_VERSION_1_2 0x12


typedef enum
{
  SPDM_STATE_RESET = 0x0U,
  SPDM_STATE_VERSION = 0x1U,
  SPDM_STATE_CAPABILITIES = 0x2U,
  SPDM_STATE_ALGORITHMS = 0x3U,
  SPDM_STATE_CERTIFICATE = 0x5U,
  SPDM_STATE_CHALLENGE = 0x6U
} SPDM_State_t;

void spdm_StateReset(void);
void spdm_dispatch(void);
void test_dispatch(void);


#endif /* INC_SPDM_HANDLER_H_ */
