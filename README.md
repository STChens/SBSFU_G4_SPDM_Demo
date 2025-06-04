# SBSFU for STM32G474 Nucleo board 
## Overview
This is modified version of SBSFU basing on STM32MCU X-CUBE-SBSFU v2.6.2 package with new features added:

* **Crypto Scheme** New crypto scheme added to support ECDSA384 + SHA384 with or without AES256

* **Key Revocation** Key revocation option added to allow 8 set of public keys and AES keys to be generated and stored. FW Image header is updated to add key index added for both public key and symmetric key. OTP is used to store the minimum key index allowed.

* **User App** SPDM demo is included in the user application.

# SBSFU Features
## Supported HW platform
Nucleo-G474RE board

## Supported flash layout
* **1_Image** Single image layout. Only possible to download new FW version from bootloader and User App in active slot will be replaced directly
* **2_Images** Dual image layout with active slot and download slot. Possible to download new FW version from App
* **2_Images_OSC** Dual image layout. Same as 2_Images layout, except that the crypto implementation is using mbedtls instead of STM32 x-cube-cryptolib

## Two new crypto schemes with ECDSA384
*	SECBOOT_ECCDSA_WITH_AES256_CBC_SHA384 (default)
*	SECBOOT_ECCDSA_WITHOUT_ENCRYPT_SHA384

##	Supported IDE
*	IAR (Tested with v8.50.9)
*	KEIL (Tested with v5.39.0.0)
*	STM32CubeIDE (Tested with v1.18.0)

##	About protection
Two protections not enabled in the default settings
*	SFU_TAMPER_PROTECT_ENABLE：this is usually linked to the customer board HW design, so disabled by default
*	SFU_MPU_PROTECT_ENABLE：due to new features added in SECoreBin, flash and RAM size required increased. After memory layout adjustment, the region to be protected by MPU may not be able to meet the constraint of region start address/size and so on. So MPU protection is disabled in this version.

## Key revocation feature
### Number of keys supported
Maximum 8 key sets can be supported for key revocation purpose
Value of the 8 key sets (including public keys and AES keys will all be converted to code and built in the secure boot binary.

### Key files for ECC keys and AES keys
New key files added in folder Projects\NUCLEO-G474RE\Applications\2_Images\2_Images_SECoreBin\Binary
*	ECCKEY1-384.txt_x (x = 0 ~ 7)
*	OEM_KEY_COMPANY1_key_AES256_CBC.bin_x (x = 0 ~ 7)

### Generate key sets
New key sets can be generated using genkey command of prepareimg tool, e.g.
*	generate 8 ECC keys 
+ prepareimage keygen -k ECCKEY1-384.txt -t ecdsa-p384 -n 8 
8 ECC key files will be generated and named as ECCKEY1-384.txt_0 to ECCKEY1-384.txt_7

*	generate 8 AES CBC keys
** prepareimage keygen -k OEM_KEY_COMPANY1_key_AES256_CBC.bin -t aes256-cbc -n 8 
8 AES CBC key files will be generated and named as OEM_KEY_COMPANY1_key_AES256_CBC.bin_0 to OEM_KEY_COMPANY1_key_AES256_CBC.bin_7

###	Compile flags and Build actions in Projects
Compile flag **KEY_REVOCATION** is added to SECoreBin and SBSFU project preprocessor config to activate support key revocation feature. 
Calling of prebuild.bat from SECoreBin project folder: 
*	Additional one parameter for “number of keys” is added at the end of the command. 
*	The value 8 is given as the parameter. This is to tell the prebuild command to convert 8 keys into 8 functions in se_key.s
*	Calling of postbuild.bat from SECoreBIn project folder:
*	Additional two parameters are added at the end of the command to call postbuild script. 
+ 8 is given as “number of keys” parameter to let the postbuild script to know that there are multi keys for key revocation
+ 0 is given as “key index” parameter to let the postbuild script to select the right key from the 8 key sets. For examples, 0 corresponds to ECCKEY1-384.txt_0 and OEM_KEY_COMPANY1_key_AES256_CBC.bin_0
+ The last parameter can be 0 to 7. If a none 0 value is given, the key with index that is less than the value will become invalid. 

###	About key index storage on the device
There is a compile flag added in the source code to store the key index value in Backup register：**#define TEST_KEY_REVOCATION_STORAGE_IN_BKPR**
This definition is added to Projects\NUCLEO-G474RE\Applications\2_Images\2_Images_SECoreBin\Inc\se_crypto_config.h

The same definition is also added to Projects\NUCLEO-G474RE\Applications\2_Images\2_Images_SBSFU\Core\Src\main.c. This is more to enable the related clock and so on to make sure Backup register can work. 

If **TEST_KEY_REVOCATION_STORAGE_IN_BKPR** macro is defined in se_crypto_config.h, then when a bigger index is detected in a valid header, OTP will not be updated for the new minimum key index. Instead, the data is updated to backup register. That means, the key revocation feature can be tested as long as the board is powered on without changing OTP. 

This option flag is to ease the test of Key revocation feature because OTP can only be written once. 
To test the feature using OTP, please comment out the definition of macro in se_crypto_config.h at least. 

For the OTP layout definition, please refer to the comments in Middlewares\ST\STM32_Secure_Engine\Key\se_key.h
Ideally, the key hash table hash shall also be stored in OTP to be used to check the key data. But this part is not implemented yet. So the top part of the OTP is not used for now.

###	Other notes
**se_key.s** contains not only the functions for the keys, but also the functions for the key hashes. 
If customer want to add key value check against hash value, the key hash functions can be used
Such feature is not implemented yet. Can be added if customer need it. 
