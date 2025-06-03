/**
  ******************************************************************************
  * @file           : spdm_handler.c
  * @brief          : SPDM message handler
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


#include "main.h"
#include <stdlib.h>
#include <string.h>
#include "stsafe_testKeys.h"
#include "stsafea_interface_conf.h"
#include "stsafea_core.h"
#include "x509.h"

#if defined CRYPTOLIB_V4
#include "cmox_crypto.h"
#include "hash/legacy_v3_hash.h"
#else
#include "crypto.h"
#endif

#include "spdm_handler_private.h"
#include "spdm_handler.h"


#define useSHA384 1
#define requireMAC 0

#if useSHA384
#if defined CRYPTOLIB_V4
#include "hash/legacy_v3_sha384.h"
#endif
	typedef SHA384ctx_stt SHActx;
	typedef tSPDM_GetCertificate_RSP_SHA384 tSPDM_GetCertificate_RSP;
	typedef tSPDM_Challenge_RSP_Start_SHA384 tSPDM_Challenge_RSP_Start;
	typedef tSPDM_Measurement_RSP_SHA384 tSPDM_Measurement_RSP;
	#define SHA_digest_size CRL_SHA384_SIZE
	#define STSAFE_GenSig_SHA  STSAFEA_SHA_384
#else
#if defined CRYPTOLIB_V4
#include "hash/legacy_v3_sha256.h"
#endif

	typedef SHA256ctx_stt SHActx;
	typedef tSPDM_GetCertificate_RSP_SHA256 tSPDM_GetCertificate_RSP;
	typedef tSPDM_Challenge_RSP_Start_SHA256 tSPDM_Challenge_RSP_Start;
	typedef tSPDM_Measurement_RSP_SHA256 tSPDM_Measurement_RSP;
	#define SHA_digest_size CRL_SHA256_SIZE
	#define STSAFE_GenSig_SHA  STSAFEA_SHA_256
#endif
        
#if requireMAC
	#define genSigMACMode STSAFEA_MAC_HOST_CMAC //C-MAC on command to authorize signature generation by STSAFE
	#define verSignMACMode STSAFEA_MAC_HOST_RMAC //R-MAC from STSAFE on response to verify it is STSAFE who is responding
#else
	#define genSigMACMode STSAFEA_MAC_NONE
	#define verSignMACMode STSAFEA_MAC_NONE
#endif



tSPDM_VCA    vca;
SPDM_State_t spdmState;

SHActx      m1; //cryptolib context

/*****************Hash functions*******************************/
static inline int32_t SHA_Init(SHActx *P_pSHActx)
{
#if useSHA384
	return SHA384_Init(P_pSHActx);
#else
	return SHA256_Init(P_pSHActx);
#endif
}

/************************************************/
static inline int32_t SHA_Append(SHActx *P_pSHActx, const uint8_t *P_pInputBuffer, int32_t P_inputSize)
{
#if useSHA384
	return SHA384_Append(P_pSHActx, P_pInputBuffer, P_inputSize);
#else
	return SHA256_Append(P_pSHActx, P_pInputBuffer, P_inputSize);
#endif
}

/************************************************/
static inline int32_t SHA_Finish(SHActx *P_pSHActx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize)
{
#if useSHA384
	return SHA384_Finish(P_pSHActx, P_pOutputBuffer, P_pOutputSize);
#else
	return SHA256_Finish(P_pSHActx, P_pOutputBuffer, P_pOutputSize);
#endif
}


static void spdm_updateVCA(void);

/************************************************/
void spdm_StateReset(void)
{
	spdmState =SPDM_STATE_RESET;
	vca.size = 0;
	memset(vca.vca, 0, sizeof(vca.vca));
	m1.mFlags = E_HASH_DEFAULT;
	m1.mTagSize = SHA_digest_size;
	SHA_Init(&m1);
}

/************************************************/
void spdm_dispatch(void)
{
	uint8_t expectedVer;
	if (txtrBuffer.dataSize<2) {
		spdm_setErrorRsp();
		return;
	}

	if (txtrBuffer.buffer[0] == TEST_CMD)
	{
		test_dispatch();
		return;
	}

	if (spdmState!=SPDM_STATE_RESET ) {
		expectedVer = SPDM_VERSION_1_2;
	} else {
		expectedVer = SPDM_GENERIC_VERSION;
	}

	if (txtrBuffer.buffer[0] !=expectedVer ) {
		if ((txtrBuffer.buffer[0] ==SPDM_GENERIC_VERSION ) &&  (txtrBuffer.buffer[1] ==SPDM_CMD_GET_VERSION )) {
			spdm_StateReset();
			spdm_GetVersion();
		} else {
			spdm_setErrorRsp();
		}
		return;
	}

	switch (spdmState) {
	case SPDM_STATE_RESET:
	{
		if (txtrBuffer.buffer[1] !=SPDM_CMD_GET_VERSION ) {
				spdm_setErrorRsp();
		} else {
			spdm_GetVersion();
		}
		break;
	}
	case SPDM_STATE_VERSION:
	{
		if (txtrBuffer.buffer[1] !=SPDM_CMD_GET_CAPABILITIES ) {
			spdm_setErrorRsp();
		} else {
			spdm_GetCapabilities();
		}
		break;
	}
	case SPDM_STATE_CAPABILITIES:
	{
		if (txtrBuffer.buffer[1] !=SPDM_CMD_NEGOTIATE_ALGO ) {
			spdm_setErrorRsp();
		} else {
			spdm_NegotiateAlgorithms();
		}
		break;
	}
	case SPDM_STATE_ALGORITHMS: {
		if (txtrBuffer.buffer[1] !=SPDM_CMD_GET_CERTIFICATE ) {
			spdm_setErrorRsp();
		} else {
			spdm_GetCertificate();
		}
		break;
	}
	case SPDM_STATE_CERTIFICATE: {
		switch (txtrBuffer.buffer[1]) {
			case SPDM_CMD_GET_CERTIFICATE:{
				spdm_GetCertificate(); //to support certificate chaining, not tested
				break;
			}
			case SPDM_CMD_CHALLENGE: {
				spdm_Challenge();
				break;
			}
			default:
				spdm_setErrorRsp();
			break;
		}
		break;
	}
	case SPDM_STATE_CHALLENGE:
	{
		if (txtrBuffer.buffer[1] !=SPDM_CMD_GET_MESUREMENTS ) {
			spdm_setErrorRsp();
		} else {
			spdm_GetMeasurements();
		}
		break;
	}
	default:
		spdm_setErrorRsp();
	}
	return;
}

/************************************************/
void test_dispatch(void)
{
	//Only test commands are handled there (not part of SPDM protocol, just demonstration of some STSAFE commands)
	switch(txtrBuffer.buffer[1]){
	case TEST_QUERY_CURVE:{
		txtrBuffer.buffer[0] = test_QueryCurveType();
		txtrBuffer.dataSize = 1;
		break;
	}
	case TEST_QUERY_ECHO: {
		txtrBuffer.dataSize = test_Echo();
		break;
	}
	case TEST_HOST_KEY: {
		if (txtrBuffer.dataSize!=3) return ;
		txtrBuffer.buffer[0] = test_HostKeyCheck(txtrBuffer.buffer[2]);
		txtrBuffer.dataSize = 1;
		break;
	}
	case TEST_VERIFY_SIGNATURE: {
		txtrBuffer.buffer[0] = test_VerifySignature();
		txtrBuffer.dataSize = 1;
		break;
	}
	default:
		break;
	}

}

/************************************************/
static void pointToUnsignedInt(StSafeA_LVBuffer_t *point)
{
	while (*(point->Data)==0){
		if (point->Length <10 ) break; //normally point is a huge value, length shouldn't be too small
		point->Data = point->Data+1;
		point->Length--;
	}
}

/************************************************/
static uint8_t test_VerifySignature(void)
{
	StSafeA_LVBuffer_t pInPubX, pInPubY, pInSignR, pInSignS, pInDigest;
	StSafeA_VerifySignatureBuffer_t  pOutRespVerifySignature;
	uint16_t offset = 2;  //offset length check might not be exhaustive as it is a test only command.
	pInPubX.Length = txtrBuffer.buffer[offset++];
	pInPubX.Data = &txtrBuffer.buffer[offset];
	offset += pInPubX.Length;
	pInPubY.Length = txtrBuffer.buffer[offset++];
	pInPubY.Data = &txtrBuffer.buffer[offset];
	offset += pInPubY.Length;
	pInSignR.Length =txtrBuffer.buffer[offset++];
	pInSignR.Data =&txtrBuffer.buffer[offset];
	offset += pInSignR.Length;
	pInSignS.Length =txtrBuffer.buffer[offset++];
	pInSignS.Data = &txtrBuffer.buffer[offset];
	offset += pInSignS.Length;
	pInDigest.Length =txtrBuffer.buffer[offset++];
	pInDigest.Data = &txtrBuffer.buffer[offset];
	offset += pInDigest.Length;

	//OpenSSL and other standards might represent R and S as SIGNED integer,
	// which will lead to a trailing 00 byte in some cases
	// STSAFE works with UNSIGNED representation of points so trailing 00s have to be removed if present
	pointToUnsignedInt(&pInSignR);
	pointToUnsignedInt(&pInSignS);

	if (offset!=txtrBuffer.dataSize) return 0xFF;
	if (StSafeA_VerifyMessageSignature(&stsafea_handle, STSAFEA_NIST_P_256, &pInPubX, &pInPubY, &pInSignR, &pInSignS, &pInDigest, &pOutRespVerifySignature, verSignMACMode)
					!= STSAFEA_OK) {
								return 0xFF;
	}

	return pOutRespVerifySignature.SignatureValidity;
}

/************************************************/
static uint8_t test_HostKeyCheck(uint8_t writeTestKey)
{
	int32_t              StatusCode = 0;
	StSafeA_HostKeySlotBuffer_t HostKeySlot;

	StatusCode = StSafeA_HostKeySlotQuery(&stsafea_handle, &HostKeySlot, STSAFEA_MAC_NONE);
	if (StatusCode != 0 ) {return 0xFF;}
	if (HostKeySlot.HostKeyPresenceFlag == 0U) { //Host Key is not populated
		if (writeTestKey != 0) {
			uint8_t Host_MAC_Cipher_Key[2U * STSAFEA_HOST_KEY_LENGTH] = {
					cTestHostMacKey,    /* Host MAC key */
				cTestHostCipherKey     /* Host cipher key */
			    };
			//Need to write key into slot. This operation can only be done ONCE and is irreversible
			StatusCode = StSafeA_PutAttribute(&stsafea_handle, STSAFEA_TAG_HOST_KEY_SLOT,
			                                                      Host_MAC_Cipher_Key, 2U * STSAFEA_HOST_KEY_LENGTH,
			                                                      STSAFEA_MAC_NONE);
			if (StatusCode != 0 ) {return 0xFF;} //error during update
			return 0x02; // Key was updated status code
		}
		return 0x00; //no key in Host Key slot
	}
	return 0x01; //key present in Host Key slot
}

/************************************************/
static uint8_t test_Echo(void)
{
	int32_t              StatusCode = 0;
	StSafeA_LVBuffer_t	response;
	uint8_t echoRspLen=txtrBuffer.dataSize-2;

	response.Data = txtrBuffer.buffer;
	response.Length = 1024;
	StatusCode = StSafeA_Echo(&stsafea_handle, &txtrBuffer.buffer[2], echoRspLen, &response,  STSAFEA_MAC_NONE);
	if (StatusCode!=0 ) return 0;
	return echoRspLen;
}

/************************************************/
static uint8_t test_QueryCurveType(void)
{
	int32_t             StatusCode = 0;
	StSafeA_TLVBuffer_t InRawCommand;
	uint8_t queryIO[50]; //max return of query Private Key Table
	tTest_QueryprivateKeyType_RSP *rsp = (tTest_QueryprivateKeyType_RSP*)queryIO;

	InRawCommand.Header = STSAFEA_CMD_QUERY;
	queryIO[0] = STSAFEA_TAG_PRIVATE_KEY_TABLE;
	InRawCommand.LV.Data = queryIO;
	InRawCommand.LV.Length = 1U;

	StatusCode = StSafeA_RawCommand(&stsafea_handle, &InRawCommand, 50, &InRawCommand, STSAFEA_MS_WAIT_TIME_CMD_QUERY, STSAFEA_MAC_NONE);

	if (StatusCode != 0 ) {return 0xFF;}
	if (rsp->presence) {
		switch (rsp->curveIDLen) {
		case STSAFEA_ECC_CURVE_OID_NIST_P_256_LEN:{
			if (memcmp(STSAFEA_ECC_CURVE_OID_NIST_P_256, &queryIO[sizeof(tTest_QueryprivateKeyType_RSP)],STSAFEA_ECC_CURVE_OID_NIST_P_256_LEN ) == 0)
			{
				return STSAFEA_NIST_P_256;
			}
			break;
		}
		case STSAFEA_ECC_CURVE_OID_NIST_P_384_LEN:{
			if (memcmp(STSAFEA_ECC_CURVE_OID_NIST_P_384, &queryIO[sizeof(tTest_QueryprivateKeyType_RSP)],STSAFEA_ECC_CURVE_OID_NIST_P_384_LEN ) == 0)
			{
				return STSAFEA_NIST_P_384;
			}
			break;
		}
		case STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_LEN:{
			if (memcmp(STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256, &queryIO[sizeof(tTest_QueryprivateKeyType_RSP)],STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_256_LEN ) == 0)
			{
				return STSAFEA_BRAINPOOL_P_256;
			}
			if (memcmp(STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384, &queryIO[sizeof(tTest_QueryprivateKeyType_RSP)],STSAFEA_ECC_CURVE_OID_BRAINPOOL_P_384_LEN ) == 0)
			{
				return STSAFEA_BRAINPOOL_P_384;
			}
			break;
		}
		default:
			break;
		}
	}
	return 0xFF;

}

/************************************************/
static void spdm_setErrorRsp(void)
{
	if (spdmState!=SPDM_STATE_RESET ) {
		txtrBuffer.buffer[0] = SPDM_VERSION_1_2;
	} else {
		txtrBuffer.buffer[0] = SPDM_GENERIC_VERSION;
	}

	txtrBuffer.buffer[1] = SPDM_RSP_ERROR;
	txtrBuffer.buffer[2] = SPDM_ERROR_CODE_UNSPECIFIED;
	txtrBuffer.buffer[3] = 0;
	txtrBuffer.dataSize = 4;
	spdm_StateReset();
}

/************************************************/
static void spdm_updateVCA(void)
{
	if ((vca.size +txtrBuffer.dataSize  ) > sizeof(vca.vca)) {
		spdm_setErrorRsp();
		return;
	}
	memcpy(&vca.vca[vca.size],txtrBuffer.buffer,txtrBuffer.dataSize );
	vca.size += txtrBuffer.dataSize;
	return ;
}

/************************************************/
static void spdm_GetVersion(void)
{
	tSPDM_GetVersion_RSP* rsp = (tSPDM_GetVersion_RSP*) txtrBuffer.buffer;
	if (txtrBuffer.dataSize !=sizeof(tSPDM_GetVersion_CMD) )
		{
			spdm_setErrorRsp();
			return;
		}
	spdm_updateVCA();
	memset(rsp, 0, sizeof(tSPDM_GetVersion_RSP));

	rsp->SPDMVersion = SPDM_GENERIC_VERSION;
	rsp->rspCode = SPDM_RSP_VERSION;
	rsp->VersionNumberEntryCount = 1;
	rsp->versionMajMin = SPDM_VERSION_1_2;
	txtrBuffer.dataSize = sizeof(tSPDM_GetVersion_RSP);

	spdm_updateVCA();

	spdmState=SPDM_STATE_VERSION;
}

/************************************************/
static void spdm_GetCapabilities(void)
{
	tSPDM_GetCapabilities_RSP*  rsp = (tSPDM_GetCapabilities_RSP*) txtrBuffer.buffer;
	//only check msg size, ignore the rest for this demonstration
	if (txtrBuffer.dataSize !=sizeof(tSPDM_GetCapabilities_CMD) )
		{
			spdm_setErrorRsp();
			return;
		}
	spdm_updateVCA();

	memset(rsp, 0, sizeof(tSPDM_GetCapabilities_RSP));

	rsp->SPDMVersion = SPDM_VERSION_1_2;
	rsp->RequestResponseCode = SPDM_RSP_CAPABILITIES;
	rsp->CERT_CAP =1;
	rsp->CHAL_CAP = 1;
	rsp->MEAS_CAP = 2; // 10b . The Responder supports MEASUREMENTS response and can generate signatures.
	rsp->MaxSPDMmsgSize[2] = 0x4; //setting buffer size to 0x400
	rsp->DataTransferSize[2] = 0x4;

	txtrBuffer.dataSize = sizeof(tSPDM_GetCapabilities_RSP);
	spdm_updateVCA();
	spdmState=SPDM_STATE_CAPABILITIES;
}

/************************************************/
static void spdm_NegotiateAlgorithms(void)
{
	tSPDM_NegotiateAlgorithms_CMD_min*  cmd = (tSPDM_NegotiateAlgorithms_CMD_min*) txtrBuffer.buffer;
	tSPDM_NegotiateAlgorithms_RSP_min rsp;
	uint8_t curveType = test_QueryCurveType();
	if ((txtrBuffer.dataSize <sizeof(tSPDM_NegotiateAlgorithms_CMD_min) )
		||(txtrBuffer.dataSize != cmd->length ))
		{
			spdm_setErrorRsp();
			return;
		}
	spdm_updateVCA();

	//validation of all flags and error cases is quite complex, no need to do it for current demonstration?


	memset((uint8_t*)&rsp, 0, sizeof(tSPDM_NegotiateAlgorithms_RSP_min));
	rsp.SPDMVersion = SPDM_VERSION_1_2;
	rsp.RequestResponseCode = SPDM_RSP_ALGORITHMS;
	rsp.MeasurementSpecificationSel = 1;

	if (curveType==STSAFEA_NIST_P_256) {
		rsp.TPM_ALG_ECDSA_ECC_NIST_P256 = 1;
	} else {
		rsp.TPM_ALG_ECDSA_ECC_NIST_P384 = 1;
	}
#if useSHA384
	rsp.TPM_ALG_SHA_384 = 1;
	rsp.MeasurementHashAlgo_TPM_ALG_SHA_384 = 1;
#else
	rsp.TPM_ALG_SHA_256 = 1;
	rsp.MeasurementHashAlgo_TPM_ALG_SHA_256 = 1;
#endif

	if (cmd->NumbOfReqAlgStruct!=0) {
		tSPDM_NegotiateAlgorithms_RSP_AlgStructure algStruct;
		memset((uint8_t*)&algStruct, 0, sizeof(tSPDM_NegotiateAlgorithms_RSP_AlgStructure));
		algStruct.AlgType = 4;//fixed value
		algStruct.AlgCount = 0x20;//fixed value
		if (curveType==STSAFEA_NIST_P_256) {
			algStruct.TPM_ALG_ECDSA_ECC_NIST_P256 =1 ;
		} else {
			algStruct.TPM_ALG_ECDSA_ECC_NIST_P384 =1 ;
		}
		rsp.length = sizeof(tSPDM_NegotiateAlgorithms_RSP_AlgStructure) + sizeof(tSPDM_NegotiateAlgorithms_RSP_min);
		memcpy(&txtrBuffer.buffer[sizeof(tSPDM_NegotiateAlgorithms_RSP_min)],(uint8_t*)&algStruct,sizeof(tSPDM_NegotiateAlgorithms_RSP_AlgStructure) );
	} else {
		rsp.length = sizeof(tSPDM_NegotiateAlgorithms_RSP_min);
	}
	memcpy(txtrBuffer.buffer,(uint8_t*)&rsp, sizeof(tSPDM_NegotiateAlgorithms_RSP_min));

	txtrBuffer.dataSize = rsp.length;
	spdm_updateVCA();

	spdmState=SPDM_STATE_ALGORITHMS;
}

/************************************************/
static void spdm_GetCertificate(void)
{
	tSPDM_GetCertificate_CMD*  cmd = (tSPDM_GetCertificate_CMD*) txtrBuffer.buffer;
	tSPDM_GetCertificate_RSP*  rsp = (tSPDM_GetCertificate_RSP*) txtrBuffer.buffer;
	uint16_t bufferLen, chainLen;
	uint8_t slot;
	int32_t               StatusCode,digestLen;
	StSafeA_LVBuffer_t cert;
	SHActx      tmpHashCtx; //cryptolib context
	uint8_t rootCA_p256[] = {ROOT_CA_P256};
	uint8_t rootCA_p384[] = {ROOT_CA_P384};
	uint8_t curveType = test_QueryCurveType();
	uint8_t *rootCA = rootCA_p384;
	uint16_t rootCALen = sizeof(rootCA_p384);
	if (curveType==STSAFEA_NIST_P_256) {
		rootCA = rootCA_p256;
		rootCALen = sizeof(rootCA_p256);
	}
	if ((txtrBuffer.dataSize !=sizeof(tSPDM_GetCertificate_CMD) )
			|| (cmd->offset[0] !=0 )
			|| (cmd->offset[1] !=0 ) //sample code does not support chaining so offset must be 00
			|| (cmd->SlotID > 1 )) //sample code only works with slot 0
			{
				spdm_setErrorRsp();
				return;
			}
	bufferLen=(cmd->length[1]<<8 )+cmd->length[0];
	slot = cmd->SlotID;

	StatusCode = spdm_StSafe_GetCertificateSize(&stsafea_handle, &cert.Length);

	if (StatusCode != 0 || cert.Length == 0U || cert.Length>bufferLen)
	{
		spdm_setErrorRsp();
		return;
	}

	SHA_Init(&m1);
	SHA_Append(&m1,  vca.vca,vca.size);
	SHA_Append(&m1,  txtrBuffer.buffer,sizeof(tSPDM_GetCertificate_CMD));
	memset(rsp, 0, sizeof(tSPDM_GetCertificate_RSP));
	rsp->SPDMVersion = SPDM_VERSION_1_2;
	rsp->RequestResponseCode = SPDM_RSP_CERTIFICATE;
	rsp->SlotID = slot;

	tmpHashCtx.mFlags = E_HASH_DEFAULT;
	tmpHashCtx.mTagSize = SHA_digest_size;
	SHA_Init(&tmpHashCtx);
	SHA_Append(&tmpHashCtx,  rootCA,rootCALen);
	SHA_Finish(&tmpHashCtx, rsp->RootHash, &digestLen);
	chainLen = 4+ digestLen + rootCALen+cert.Length;
	rsp->chainLength[0] = (uint8_t)(chainLen&0x00FF);
	rsp->chainLength[1] = (uint8_t)((chainLen>>8)&0x00FF);
	rsp->PortionLength[0] = (uint8_t)(chainLen&0x00FF);
	rsp->PortionLength[1] = (uint8_t)((chainLen>>8)&0x00FF);
	memcpy(&txtrBuffer.buffer[sizeof(tSPDM_GetCertificate_RSP)], rootCA,rootCALen);
	cert.Data=&txtrBuffer.buffer[sizeof(tSPDM_GetCertificate_RSP)+rootCALen];
	StatusCode = StSafeA_Read(&stsafea_handle, 0, 0, STSAFEA_AC_ALWAYS, 0, 0,
			cert.Length, cert.Length,&cert, STSAFEA_MAC_NONE);

	if (StatusCode != 0 )
	{
		spdm_setErrorRsp();
		return;
	}

	txtrBuffer.dataSize = sizeof(tSPDM_GetCertificate_RSP)+rootCALen+cert.Length;
	SHA_Append(&m1,  txtrBuffer.buffer,txtrBuffer.dataSize);
	spdmState=SPDM_STATE_CERTIFICATE;
}

/************************************************/
static void spdm_Challenge(void)
{
	tSPDM_Challenge_CMD*  cmd = (tSPDM_Challenge_CMD*) txtrBuffer.buffer;
	tSPDM_Challenge_RSP_Start* rsp = (tSPDM_Challenge_RSP_Start*) txtrBuffer.buffer;
	StSafeA_LVBuffer_t pOutLVResponse;
	const uint8_t context[] = "responder-challenge_auth signing";
	uint8_t measType = cmd->Param2;
	const uint8_t dummyAllMeasurementsHash[] = {0x47,0x25,0x31,0x2D,0x03,0x13,0x55,0x04,0x93,0x0C,0x10,0x53,0x54,0x0D,0x21,0x5,
												0x03,0x25,0x3A,0x23,0x46,0x23,0x55,0x04,0x02,0x1C,0x11,0x53,0x54,0xCD,0x00,0x23,
												0xAB,0x25,0xAA,0x2A,0x03,0x33,0x55,0x04,0xA7,0x0C,0x12,0x53,0x54,0x4A,0x24,0x40};
	uint8_t slot = cmd->SlotID;
	if ((txtrBuffer.dataSize !=sizeof(tSPDM_Challenge_CMD) )
			|| ((cmd->Param2 > 0 ) && (cmd->Param2 != 0xFF )) //sample code only supports 00 or FF
			|| (cmd->SlotID != 0 )) //sample code only works with slot 0
			{
				spdm_setErrorRsp();
				return;
			}
	SHA_Append(&m1,  txtrBuffer.buffer,sizeof(tSPDM_Challenge_CMD));
	memset(rsp, 0, sizeof(tSPDM_Challenge_RSP_Start));
	rsp->SPDMVersion = SPDM_VERSION_1_2;
	rsp->RequestResponseCode = SPDM_RSP_CHALLENGE;
	rsp->Param1 = slot;
	rsp->Param2 = 1;
	if (spdm_StSafe_GetCertificateHash(slot, rsp->CertChainHash) != 0 ) {
		spdm_setErrorRsp();
		return;
	}
	pOutLVResponse.Data =  rsp->nonce;
	pOutLVResponse.Length = 32;
	if (StSafeA_GenerateRandom(&stsafea_handle, STSAFEA_EPHEMERAL_RND, 32, &pOutLVResponse, STSAFEA_MAC_NONE) != STSAFEA_OK) {
		spdm_setErrorRsp();
		return;
	}
	//tmp code
	txtrBuffer.dataSize = sizeof(tSPDM_Challenge_RSP_Start);
	if (measType != 0) {
		memcpy( txtrBuffer.buffer+txtrBuffer.dataSize,dummyAllMeasurementsHash,sizeof(dummyAllMeasurementsHash));
		txtrBuffer.dataSize+=sizeof(dummyAllMeasurementsHash);
	}

	//generate what is needed to sign data
	SHA_Append(&m1,  txtrBuffer.buffer,txtrBuffer.dataSize );

	spdm_AppendSignature(context, sizeof(context),slot );

	spdmState=SPDM_STATE_CHALLENGE;
	//prepare hash context for measurements command and update it with VCA
	SHA_Init(&m1);
	SHA_Append(&m1,  vca.vca,vca.size);
}

/************************************************/
static void spdm_GetMeasurements(void)
{
	tSPDM_Measurement_CMD*  cmd = (tSPDM_Measurement_CMD*) txtrBuffer.buffer;
	tSPDM_Measurement_RSP*  rsp = (tSPDM_Measurement_RSP*) txtrBuffer.buffer;
	uint8_t slotID;
	StSafeA_LVBuffer_t pOutLVResponse;
	uint8_t measurementBlock;
	uint8_t signatureRequested = 0;
	if ((txtrBuffer.dataSize !=sizeof(tSPDM_Measurement_CMD) && txtrBuffer.dataSize !=sizeof(tSPDM_Measurement_CMD_Nonce))
			|| ((cmd->Param1.SignatureRequested == 1) &&  txtrBuffer.dataSize !=sizeof(tSPDM_Measurement_CMD_Nonce))
			|| ((cmd->Param1.SignatureRequested == 0) &&  txtrBuffer.dataSize !=sizeof(tSPDM_Measurement_CMD))
			|| (cmd->Param1.RawBitStreamRequested != 0) //not supported in this nominal case
			|| (cmd->Param2 == 0) || (cmd->Param2 > 0x05)) //only range in 1..5 is supported according to M-CRPS
			{
				spdm_setErrorRsp();
				return;
			}
	if (cmd->Param1.SignatureRequested == 1) {
		tSPDM_Measurement_CMD_Nonce*  cmd2 = (tSPDM_Measurement_CMD_Nonce*) txtrBuffer.buffer;
		if  (cmd2->SlotIDParam.reserved != 0) {
			spdm_setErrorRsp();
			return;
		}
		slotID = cmd2->SlotIDParam.SlotID;
		signatureRequested = cmd->Param1.SignatureRequested;
	}
	measurementBlock = cmd->Param2;
	SHA_Append(&m1,  txtrBuffer.buffer,txtrBuffer.dataSize);

	memset(rsp, 0, sizeof(tSPDM_Measurement_RSP));
	rsp->SPDMVersion = SPDM_VERSION_1_2;
	rsp->RequestResponseCode = SPDM_RSP_MEASUREMENTS;
	if (signatureRequested!=0 )  {
		rsp->Param2.slotID = slotID;
	}
	rsp->NumberOfBlocks = 1;
	rsp->MeasurementBlock.Index = measurementBlock;
	rsp->MeasurementBlock.DMTFSpecMeasurementValueSize[1] = SHA_digest_size;
	rsp->MeasurementBlock.MeasurementSpecification_DMTF = 1;
	spdm_ComputeMeasurementDigest(measurementBlock,rsp->MeasurementBlock.DMTFSpecMeasurementValue_Digest);
	rsp->MeasurementBlock.MeasurementSize[1] = SHA_digest_size + 3;
	rsp->MeasurementRecordLength[2] =rsp->MeasurementBlock.MeasurementSize[1]  + 4;

	/* FIXME: Here we suppose to have the measurement data according to DMTF measurement specification format */
	pOutLVResponse.Data =  rsp->Nonce;
	pOutLVResponse.Length = 32;
	if (StSafeA_GenerateRandom(&stsafea_handle, STSAFEA_EPHEMERAL_RND, 32, &pOutLVResponse, STSAFEA_MAC_NONE) != STSAFEA_OK) {
		spdm_setErrorRsp();
		return;
	}
	txtrBuffer.dataSize=sizeof(tSPDM_Measurement_RSP);
	SHA_Append(&m1,  txtrBuffer.buffer,sizeof(tSPDM_Measurement_RSP));
	if (signatureRequested!=0 )  {

		const uint8_t context[] = "responder-measurements signing";

		spdm_AppendSignature(context,sizeof(context), slotID);


		//prepare hash context for next measurements command and update it with VCA
		SHA_Init(&m1);
		SHA_Append(&m1,  vca.vca,vca.size);
	}

}

/************************************************/
static void spdm_AppendSignature(const uint8_t* context, uint8_t contextSize, uint8_t keySlot) {
	StSafeA_LVBuffer_t SignR, SignS;
	uint8_t data_SignR [SHA_digest_size];
	uint8_t data_SignS [SHA_digest_size];
	const uint8_t prefix[] = "dmtf-spdm-v1.2.*dmtf-spdm-v1.2.*dmtf-spdm-v1.2.*dmtf-spdm-v1.2.*";
	uint8_t prefixBuffer[C_SPDM_SIG_PREFIX_LEN];
	uint8_t digest[SHA_digest_size];
	uint32_t len;
	SHA_Finish(&m1, digest, (int32_t*)&len);
	memset(prefixBuffer, 0, C_SPDM_SIG_PREFIX_LEN);
	memcpy(prefixBuffer,prefix,sizeof(prefix));
	memcpy(&prefixBuffer[C_SPDM_SIG_PREFIX_LEN-contextSize+1],context,contextSize-1); //contextSize-1 because last \0 is not part of prefix
	spdm_ComputeDigestForSigning(prefixBuffer,digest,digest);
	SignR.Length = 0;
	SignS.Length = 0;
	SignR.Data = data_SignR;
	SignS.Data = data_SignS;
				/* Generate signature of Hash */
	if (StSafeA_GenerateSignature(&stsafea_handle, keySlot, digest, STSAFE_GenSig_SHA,SHA_digest_size,
				                                                         &SignR, &SignS, genSigMACMode, STSAFEA_ENCRYPTION_NONE)
			!= STSAFEA_OK) {
						spdm_setErrorRsp();
						return;
	}
	memcpy(txtrBuffer.buffer+txtrBuffer.dataSize,data_SignR, SignR.Length );
	memcpy(txtrBuffer.buffer+txtrBuffer.dataSize+SignR.Length,data_SignS, SignS.Length );
	txtrBuffer.dataSize +=SignR.Length+SignS.Length ;

}

/************************************************/
static void spdm_ComputeMeasurementDigest(uint8_t blockID, uint8_t* out)
{
	SHActx      ctx; //cryptolib context
	const uint8_t measData[5][5]  = {{0x1,0x1,0x1,0x1,0x1},
						 {0x2,0x2,0x2,0x2,0x2},
						 {0x3,0x3,0x3,0x3,0x3},
						 {0x4,0x4,0x4,0x4,0x4},
						 {0x5,0x5,0x5,0x5,0x5}
						}; //dummy data to be hashed for measurement
	int32_t len;
	ctx.mFlags = E_HASH_DEFAULT;
	ctx.mTagSize = SHA_digest_size;
	(void)SHA_Init(&ctx);
	(void)SHA_Append(&ctx, measData[blockID-1],sizeof(measData[blockID-1]) );
	(void)SHA_Finish(&ctx, out, &len);
}

/************************************************/
static void spdm_ComputeDigestForSigning(uint8_t* prefixBuffer, uint8_t *messageHash, uint8_t* out)
{
	SHActx      ctx; //cryptolib context
	int32_t len;
	ctx.mFlags = E_HASH_DEFAULT;
	ctx.mTagSize = SHA_digest_size;
	(void)SHA_Init(&ctx);
	(void)SHA_Append(&ctx, prefixBuffer,C_SPDM_SIG_PREFIX_LEN );
	(void)SHA_Append(&ctx, messageHash,SHA_digest_size );
	(void)SHA_Finish(&ctx, out, &len);
}

/************************************************/
static int32_t spdm_StSafe_GetCertificateSize(StSafeA_Handle_t* handle, uint16_t *certSize)
{
  int32_t                       StatusCode = 0;
//same as in
  StSafeA_LVBuffer_t sts_read;
  uint8_t data_sts_read [NUMBER_OF_BYTES_TO_GET_CERTIFICATE_SIZE];
  sts_read.Length = NUMBER_OF_BYTES_TO_GET_CERTIFICATE_SIZE;
  sts_read.Data = data_sts_read;


  /* Extract 4th 1st bytes of STSAFE-A's X509 CRT certificate */
  StatusCode = StSafeA_Read(handle, 0, 0, STSAFEA_AC_ALWAYS, 0, 0,
                                            NUMBER_OF_BYTES_TO_GET_CERTIFICATE_SIZE,
                                            NUMBER_OF_BYTES_TO_GET_CERTIFICATE_SIZE,
                                            &sts_read, STSAFEA_MAC_NONE);

  if (StatusCode == 0)
  {
    switch (sts_read.Data[1])
    {
      case 0x81U:
        *certSize = (uint16_t)sts_read.Data[2] + 3U;
        break;

      case 0x82U:
        *certSize = (((uint16_t)sts_read.Data[2]) << 8) + sts_read.Data[3] + 4U;
        break;

      default:
        if (sts_read.Data[1] < 0x81U)
        {
          *certSize = sts_read.Data[1];
        }
        break;
    }
  }

  return (StatusCode);
}

/************************************************/
static int32_t spdm_StSafe_GetCertificateHash(uint8_t slot, uint8_t* out)
{
	int32_t               StatusCode;
	SHActx      ctx; //cryptolib context
	uint8_t 	buffer[SHA_digest_size];
	StSafeA_LVBuffer_t cert;
	uint32_t  len, i;
	int32_t error_status;
	StatusCode = spdm_StSafe_GetCertificateSize(&stsafea_handle, &cert.Length);

	if (StatusCode != 0 || cert.Length == 0U ){
		return StatusCode;
	}

	len=cert.Length;
	cert.Data = buffer;
	cert.Length = SHA_digest_size;

	ctx.mFlags = E_HASH_DEFAULT;
	ctx.mTagSize = SHA_digest_size;
	error_status = SHA_Init(&ctx);
	if (error_status != 0 ) {return error_status;}
	for (i=0;len>0;i++)
	{
		StatusCode = StSafeA_Read(&stsafea_handle, 0, 0, STSAFEA_AC_ALWAYS, 0, i*SHA_digest_size,
					cert.Length, cert.Length,&cert, STSAFEA_MAC_NONE);

		if (StatusCode != 0 ) {return StatusCode;}
		if (len > SHA_digest_size ) {
			error_status = SHA_Append(&ctx, buffer,SHA_digest_size );
			if (error_status != 0 ) {return error_status;}
			len -= SHA_digest_size;
		}  else {
			error_status = SHA_Append(&ctx, buffer,len );
			if (error_status != 0 ) {return error_status;}
			len=0;

		}
	}
	//add to hash
	error_status = SHA_Finish(&ctx, out, (int32_t*)&len);
	if (error_status != 0 ) {return error_status;}
	return 0;
}


