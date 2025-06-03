/**
  ******************************************************************************
  * @file    se_key.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for Secure Engine KEY module
  *          functionalities.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SE_KEY_H
#define SE_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup  SE Secure Engine
  * @{
  */

/** @addtogroup SE_KEY SE Key
  * @{
  */


/** @addtogroup SE_KEY_Exported_Functions
  * @brief Functions SE_CoreBin can use to retrieve the keys.
  *        These functions are implemented in se_key.s
  * @note Depending on the crypto scheme, @ref SE_ReadKey or @ref SE_ReadKey_Pub can be useless.
  *       Nevertheless, we do not use compiler switches as the linker will remove the unused function(s).
  * @{
  */
/**
  * @brief Function to retrieve the symmetric key.
  *        One specific key per FW image.
  * @param pKey: pointer to an array of uint8_t with the appropriate size
  * @retval void
  */
#if !(defined KEY_REVOCATION)  
void SE_ReadKey_1(uint8_t *pKey);
void SE_ReadKey_2(uint8_t *pKey);
void SE_ReadKey_3(uint8_t *pKey);
#else
void SE_ReadKey_1_0(uint8_t *pKey);
void SE_ReadKey_1_1(uint8_t *pKey);
void SE_ReadKey_1_2(uint8_t *pKey);
void SE_ReadKey_1_3(uint8_t *pKey);
void SE_ReadKey_1_4(uint8_t *pKey);
void SE_ReadKey_1_5(uint8_t *pKey);
void SE_ReadKey_1_6(uint8_t *pKey);
void SE_ReadKey_1_7(uint8_t *pKey);

void SE_ReadKey_2_0(uint8_t *pKey);
void SE_ReadKey_2_1(uint8_t *pKey);
void SE_ReadKey_2_2(uint8_t *pKey);
void SE_ReadKey_2_3(uint8_t *pKey);
void SE_ReadKey_2_4(uint8_t *pKey);
void SE_ReadKey_2_5(uint8_t *pKey);
void SE_ReadKey_2_6(uint8_t *pKey);
void SE_ReadKey_2_7(uint8_t *pKey);

void SE_ReadKey_3_0(uint8_t *pKey);
void SE_ReadKey_3_1(uint8_t *pKey);
void SE_ReadKey_3_2(uint8_t *pKey);
void SE_ReadKey_3_3(uint8_t *pKey);
void SE_ReadKey_3_4(uint8_t *pKey);
void SE_ReadKey_3_5(uint8_t *pKey);
void SE_ReadKey_3_6(uint8_t *pKey);
void SE_ReadKey_3_7(uint8_t *pKey);
#endif

/**
  * @brief Function to retrieve the public asymmetric key.
  * @param pPubKey: pointer to an array of uint8_t with the appropriate size
  * @retval void
  */
#if !(defined KEY_REVOCATION)
void SE_ReadKey_1_Pub(uint8_t *pPubKey);
void SE_ReadKey_2_Pub(uint8_t *pPubKey);
void SE_ReadKey_3_Pub(uint8_t *pPubKey);
#else
void SE_ReadKey_1_Pub_0(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_1(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_2(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_3(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_4(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_5(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_6(uint8_t *pPubKey);
void SE_ReadKey_1_Pub_7(uint8_t *pPubKey);

void SE_ReadKey_2_Pub_0(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_1(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_2(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_3(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_4(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_5(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_6(uint8_t *pPubKey);
void SE_ReadKey_2_Pub_7(uint8_t *pPubKey);

void SE_ReadKey_3_Pub_0(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_1(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_2(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_3(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_4(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_5(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_6(uint8_t *pPubKey);
void SE_ReadKey_3_Pub_7(uint8_t *pPubKey);
#endif

#if (defined KEY_REVOCATION)

/* Data storage in OTP */
#define OTP_PUB_KEY_IDX_WORD_START (0)
#define OTP_ENC_KEY_IDX_WORD_START (7)
#define OTP_ENC_KEY_HASH_TABLE_HASH_WORD_START (116)
#define OTP_PUB_KEY_HASH_TABLE_HASH_WORD_START (122)

/* 
 * 1 word = 64 bit = 8 bytes 
 * Key use flag : 
 *   as long as the there is one bit in the word that is NOT 1, that means the index is used
 *   the idx is not used only if all the bits in the words are 1
 *   val = 0xFFFFFFFFFFFFFFFF: Index X not used
 *   val != 0xFFFFFFFFFFFFFFFF: Index X used (Any Index < X is not valid anymore)

  +----------------+---------------+-------------------------+
  | OTP word index | offset (bytes)|        Data             |
  +----------------+-----------------------------------------+
  |        0       |      0        |  Pub Key Idx 1 use flag |  
  +----------------+-----------------------------------------+
  |        1       |      8        |  Pub Key Idx 2 use flag |  
  +----------------+-----------------------------------------+
  |        2       |      16       |  Pub Key Idx 3 use flag |  
  +----------------+-----------------------------------------+
  |        3       |      24       |  Pub Key Idx 4 use flag |  
  +----------------+----------------------------------------+
  |        4       |      32       |  Pub Key Idx 5 use flag |  
  +----------------+-----------------------------------------+
  |        5       |      40       |  Pub Key Idx 6 use flag |  
  +----------------+-----------------------------------------+
  |        6       |      48       |  Pub Key Idx 7 use flag |  
  +----------------+-----------------------------------------+
  |        7       |      56       |  Enc Key Idx 1 use flag |  
  +----------------+-----------------------------------------+
  |        8       |      64       |  Pub Key Idx 2 use flag |  
  +----------------+-----------------------------------------+
  |        9       |      72       |  Pub Key Idx 3 use flag |  
  +----------------+-----------------------------------------+
  |        10      |      80       |  Pub Key Idx 4 use flag |  
  +----------------+-----------------------------------------+
  |        11      |      88       |  Pub Key Idx 5 use flag |  
  +----------------+----------------------------------------+
  |        12      |      96       |  Pub Key Idx 6 use flag |  
  +----------------+-----------------------------------------+
  |        13      |      114      |  Pub Key Idx 7 use flag |  
  +----------------+-----------------------------------------+
  |                |               |                         |
  |                |               |                         |
  |    14 ~ 115    |      120      |      NOT USED           | 
  |                |               |                         |
  |                |               |  Free for App usage     |
  |                |               |                         |
  +----------------+-----------------------------------------+  
  |   116 ~ 121    |      928      | Enc Key Hash Table Hash |  
  +----------------+-----------------------------------------+
  |   122 ~ 127    |      976      | Pub Key Hash Table Hash |  
  +----------------+-----------------------------------------+  


*/
#endif

/**
  * @brief Function to retrieve the external token pairing keys.
  * @param pPairingKey: pointer to an array of uint8_t with the appropriate size (32 bytes)
  * @retval void
  */
void SE_ReadKey_Pairing(uint8_t *pPairingKey);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* SE_KEY_H */
