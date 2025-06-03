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
#ifndef INC_SPDM_HANDLER_PRIVATE_H_
#define INC_SPDM_HANDLER_PRIVATE_H_

#define C_SPDM_SIG_PREFIX_LEN 100
#define NUMBER_OF_BYTES_TO_GET_CERTIFICATE_SIZE              4

typedef struct {
	uint16_t size;
	uint8_t vca[600]; //long enough buffer to store VCA
} tSPDM_VCA;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t cmd;
  uint8_t reserved[2];
} tSPDM_GetVersion_CMD;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t rspCode;
  uint8_t reserved[3];
  uint8_t VersionNumberEntryCount;
  struct{
	  uint8_t Alpha:4;
	  uint8_t UpdateVersionNumber:4;
  };
  uint8_t versionMajMin;
} tSPDM_GetVersion_RSP;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t reserved1[3];
  uint8_t CTExponent;
  uint8_t reserved2[2];
  uint8_t flags[4];
  uint8_t DataTransferSize[4];
  uint8_t MaxSPDMmsgSize[4];
} tSPDM_GetCapabilities_CMD;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t reserved1[3];
  uint8_t CTExponent;
  uint8_t reserved2[2];
  union{
	  uint8_t flags[4];
	  struct {
		  uint8_t CACHE_CAP:1;
		  uint8_t CERT_CAP:1;
		  uint8_t CHAL_CAP:1;
		  uint8_t MEAS_CAP:2;
		  uint8_t MEAS_FRESH_CAP:1;
		  uint8_t ENCRYPT_CAP:1;
		  uint8_t MAC_CAP:1;
		  uint8_t unusedFlags[3];
	  };
  };
  uint8_t DataTransferSize[4];
  uint8_t MaxSPDMmsgSize[4];
} tSPDM_GetCapabilities_RSP;


typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t NumbOfReqAlgStruct;
  uint8_t reserved0;
  uint8_t length;
  uint8_t reserved1;
  uint8_t MeasurementSpecification;
  uint8_t OtherParamsSupport;
  union {
	  uint8_t BaseAsymAlgo[4];
	  struct {
	  		  uint8_t TPM_ALG_RSASSA_2048:1;
	  		  uint8_t TPM_ALG_RSAPSS_2048:1;
	  		  uint8_t TPM_ALG_RSASSA_3072:1;
	  		  uint8_t TPM_ALG_RSAPSS_3072:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P256:1;
	  		  uint8_t TPM_ALG_RSASSA_4096:1;
	  		  uint8_t TPM_ALG_RSAPSS_4096:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P384:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P521:1;
	  		  uint8_t TPM_ALG_SM2_ECC_SM2_P256:1;
	  		  uint8_t EdDSA_ed25519:1;
	  		  uint8_t EdDSA_ed448:1;
	  		  uint8_t BaseAsymAlgo_reservedBits:4;
	  		  uint8_t BaseAsymAlgo_reservedBytes[2];
	  	  };
  };
  union {
	  uint8_t BaseHashAlgo[4];
	  struct {
	  		  uint8_t TPM_ALG_SHA_256:1;
	  		  uint8_t TPM_ALG_SHA_384:1;
	  		  uint8_t TPM_ALG_SHA_512:1;
	  		  uint8_t TPM_ALG_SHA3_256:1;
	  		  uint8_t TPM_ALG_SHA3_384:1;
	  		  uint8_t TPM_ALG_SHA3_512:1;
	  		  uint8_t TPM_ALG_SM3_256:1;
	  		  uint8_t BaseHashAlgo_reservedBits:1;
	  		  uint8_t BaseHashAlgo_reservedBytes[3];
	  	  };
  };
  uint8_t reserved2[12];
  uint8_t ExtAsymCount;
  uint8_t ExtHashCount;
  uint8_t reserved3[2];
} tSPDM_NegotiateAlgorithms_CMD_min;


typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t NumbOfReqAlgStruct;
  uint8_t reserved0;
  uint8_t length;
  uint8_t reserved1;
  uint8_t MeasurementSpecificationSel;
  uint8_t OtherParamsSelection;
  union {
	  uint8_t MeasurementHashAlgo[4];
	  struct {
  		  	  uint8_t MeasurementHashAlgo_RawBitStream:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA_256:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA_384:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA_512:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA3_256:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA3_384:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SHA3_512:1;
	  		  uint8_t MeasurementHashAlgo_TPM_ALG_SM3_256:1;
	  		  uint8_t MeasurementHashAlgo_reservedBytes[3];
	  	  };
  };
  union {
	  uint8_t BaseAsymSel[4];
	  struct {
	  		  uint8_t TPM_ALG_RSASSA_2048:1;
	  		  uint8_t TPM_ALG_RSAPSS_2048:1;
	  		  uint8_t TPM_ALG_RSASSA_3072:1;
	  		  uint8_t TPM_ALG_RSAPSS_3072:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P256:1;
	  		  uint8_t TPM_ALG_RSASSA_4096:1;
	  		  uint8_t TPM_ALG_RSAPSS_4096:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P384:1;
	  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P521:1;
	  		  uint8_t TPM_ALG_SM2_ECC_SM2_P256:1;
	  		  uint8_t EdDSA_ed25519:1;
	  		  uint8_t EdDSA_ed448:1;
	  		  uint8_t BaseAsymSel_reservedBits:4;
	  		  uint8_t BaseAsymSel_reservedBytes[2];
	  	  };
  };
  union {
	  uint8_t BaseHashSel[4];
	  struct {
	  		  uint8_t TPM_ALG_SHA_256:1;
	  		  uint8_t TPM_ALG_SHA_384:1;
	  		  uint8_t TPM_ALG_SHA_512:1;
	  		  uint8_t TPM_ALG_SHA3_256:1;
	  		  uint8_t TPM_ALG_SHA3_384:1;
	  		  uint8_t TPM_ALG_SHA3_512:1;
	  		  uint8_t TPM_ALG_SM3_256:1;
	  		  uint8_t BaseHashSel_reservedBits:1;
	  		  uint8_t BaseHashSel_reservedBytes[3];
	  	  };
  };
  uint8_t reserved2[12];
  uint8_t ExtAsymSelCount;
  uint8_t ExtHashSelCount;
  uint8_t reserved3[2];
} tSPDM_NegotiateAlgorithms_RSP_min;

typedef struct {
	uint8_t AlgType;
	uint8_t AlgCount;
	  union {
		  uint8_t AlgSupported[2];
		  struct {
		  		  uint8_t TPM_ALG_RSASSA_2048:1;
		  		  uint8_t TPM_ALG_RSAPSS_2048:1;
		  		  uint8_t TPM_ALG_RSASSA_3072:1;
		  		  uint8_t TPM_ALG_RSAPSS_3072:1;
		  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P256:1;
		  		  uint8_t TPM_ALG_RSASSA_4096:1;
		  		  uint8_t TPM_ALG_RSAPSS_4096:1;
		  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P384:1;
		  		  uint8_t TPM_ALG_ECDSA_ECC_NIST_P521:1;
		  		  uint8_t TPM_ALG_SM2_ECC_SM2_P256:1;
		  		  uint8_t EdDSA_ed25519:1;
		  		  uint8_t EdDSA_ed448:1;
		  		  uint8_t AlgSupported_reservedBits:4;
		  	  };
	  };
} tSPDM_NegotiateAlgorithms_RSP_AlgStructure;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  struct{
	  uint8_t reservedBits:4;
	  uint8_t SlotID:4;
  };
  uint8_t reserved;
  uint8_t offset[2];
  uint8_t length[2];
} tSPDM_GetCertificate_CMD;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  struct{
	  uint8_t reservedBits:4;
	  uint8_t SlotID:4;
  };
  uint8_t reserved;
  uint8_t PortionLength[2];
  uint8_t RemainderLength[2];
  uint8_t chainLength[2];
  uint8_t chainReserved[2];
  uint8_t RootHash[STSAFEA_SHA_384_LENGTH];
} tSPDM_GetCertificate_RSP_SHA384;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  struct{
	  uint8_t reservedBits:4;
	  uint8_t SlotID:4;
  };
  uint8_t reserved;
  uint8_t PortionLength[2];
  uint8_t RemainderLength[2];
  uint8_t chainLength[2];
  uint8_t chainReserved[2];
  uint8_t RootHash[STSAFEA_SHA_256_LENGTH];
} tSPDM_GetCertificate_RSP_SHA256;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t SlotID;
  uint8_t Param2;
  uint8_t nonce[32];
} tSPDM_Challenge_CMD;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t Param1;
  uint8_t Param2;
  uint8_t CertChainHash[STSAFEA_SHA_384_LENGTH];
  uint8_t nonce[32];
} tSPDM_Challenge_RSP_Start_SHA384;

typedef struct
{
  uint8_t SPDMVersion;
  uint8_t RequestResponseCode;
  uint8_t Param1;
  uint8_t Param2;
  uint8_t CertChainHash[STSAFEA_SHA_256_LENGTH];
  uint8_t nonce[32];
} tSPDM_Challenge_RSP_Start_SHA256;

typedef struct {
    uint8_t SPDMVersion;
    uint8_t RequestResponseCode;
    struct {
        uint8_t SignatureRequested : 1;
        uint8_t RawBitStreamRequested : 1;
        uint8_t reserved : 6;
    } Param1;
    uint8_t Param2;
    uint8_t Nonce[32];
    struct {
        uint8_t reserved : 4;
        uint8_t SlotID : 4;
    } SlotIDParam;
} tSPDM_Measurement_CMD_Nonce;

typedef struct {
    uint8_t SPDMVersion;
    uint8_t RequestResponseCode;
    struct {
        uint8_t SignatureRequested : 1;
        uint8_t RawBitStreamRequested : 1;
        uint8_t reserved : 6;
    } Param1;
    uint8_t Param2;
} tSPDM_Measurement_CMD;

typedef struct {
    uint8_t SPDMVersion;
    uint8_t RequestResponseCode;
    uint8_t Param1;
    struct {
    	uint8_t slotID:4;
    	uint8_t contentChanges:2;
    	uint8_t reserved:2;
    }Param2;
    uint8_t NumberOfBlocks;
    uint8_t MeasurementRecordLength[3];
    struct {
    	uint8_t Index;
    	struct {
    		uint8_t MeasurementSpecification_DMTF:1;
    		uint8_t MeasurementSpecification_reserved:7;
    	};
    	uint8_t MeasurementSize[2];
    	struct {
    		uint8_t DMTFSpecMeasurementValueType:7;
    		uint8_t DMTFSpecMeasurementValueType_isRawStream:1;
    	};
    	uint8_t DMTFSpecMeasurementValueSize[2];
    	uint8_t DMTFSpecMeasurementValue_Digest[STSAFEA_SHA_384_LENGTH];
    } MeasurementBlock;
    uint8_t Nonce[32];
} tSPDM_Measurement_RSP_SHA384;

typedef struct {
    uint8_t SPDMVersion;
    uint8_t RequestResponseCode;
    uint8_t Param1;
    struct {
    	uint8_t slotID:4;
    	uint8_t contentChanges:2;
    	uint8_t reserved:2;
    }Param2;
    uint8_t NumberOfBlocks;
    uint8_t MeasurementRecordLength[3];
    struct {
    	uint8_t Index;
    	struct {
    		uint8_t MeasurementSpecification_DMTF:1;
    		uint8_t MeasurementSpecification_reserved:7;
    	};
    	uint8_t MeasurementSize[2];
    	struct {
    		uint8_t DMTFSpecMeasurementValueType:7;
    		uint8_t DMTFSpecMeasurementValueType_isRawStream:1;
    	};
    	uint8_t DMTFSpecMeasurementValueSize[2];
    	uint8_t DMTFSpecMeasurementValue_Digest[STSAFEA_SHA_256_LENGTH];
    } MeasurementBlock;
    uint8_t Nonce[32];
} tSPDM_Measurement_RSP_SHA256;

typedef struct
{
  uint8_t numbOfSlots;
  uint8_t changeRight;
  uint16_t globalUsage;
  uint8_t slotNumber;
  uint8_t presence;
  uint16_t modeOfOperation;
  uint8_t filler;
  uint8_t curveIDLen;
} tTest_QueryprivateKeyType_RSP;

static void spdm_updateVCA();
static void spdm_setErrorRsp(void);
static void spdm_GetVersion(void);
static void spdm_GetCapabilities(void);
static void spdm_NegotiateAlgorithms(void);
static void spdm_GetCertificate(void);
static int32_t spdm_StSafe_GetCertificateSize(StSafeA_Handle_t* handle, uint16_t *certSize);
static int32_t spdm_StSafe_GetCertificateHash(uint8_t slot, uint8_t* out);
static void spdm_Challenge(void);
static void spdm_GetMeasurements(void);
static void spdm_ComputeDigestForSigning(uint8_t* prefixBuffer, uint8_t *messageHash, uint8_t* out);
static void spdm_ComputeMeasurementDigest(uint8_t blockID, uint8_t* out);
static void spdm_AppendSignature(const uint8_t* context, uint8_t contextSize, uint8_t keySlot);

static void pointToUnsignedInt(StSafeA_LVBuffer_t *point);

static uint8_t test_VerifySignature(void);
static uint8_t test_QueryCurveType(void);
static uint8_t test_Echo(void);
static uint8_t test_HostKeyCheck(uint8_t writeTestKey);
#endif /* INC_SPDM_HANDLER_PRIVATE_H_ */
