# SBSFU for STM32G474 Nucleo board 
## Overview
This is modified version of SBSFU basing on STM32MCU X-CUBE-SBSFU v2.6.2 package with new features added:
**Crypto Scheme** New crypto scheme added to support ECDSA384 + SHA384 with or without AES256
**Key Revocation** Key revocation option added to allow 8 set of public keys and AES keys to be generated and stored. FW Image header is updated to add key index added for both public key and symmetric key. OTP is used to store the minimum key index allowed.
**User App** SPDM demo is included in the user application.
