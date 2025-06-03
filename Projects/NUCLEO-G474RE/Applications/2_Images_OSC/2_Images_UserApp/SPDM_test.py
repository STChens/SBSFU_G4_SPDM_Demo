import unittest
import serial
import random
import hashlib
from asn1crypto.x509 import Certificate
from asn1crypto.keys import PublicKeyInfo
from ecdsa import VerifyingKey, NIST384p,NIST256p

class SPDMRequester:
    def __init__(self, com_port):
        self.name = "SPDM Requester"
        self.com_port = com_port
        self.ser = serial.Serial(com_port, baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
        self.version = None
        self.vca=[]
        self.b4 = []
        self.unsignedMeas=[]
        self.algo = {}
        self.baseHashSel = ''
        self.measurementHashAlgo = ''
        self.certificate =[]


    def __del__(self):
        self.ser.close()
        
    def SendCmd(self,dataToSend):
        self.TransmitBytes(dataToSend)
        return self.ReceiveBytes()

    def ReceiveBytes(self):
        #first lets receive data size as 1 byte and then the command
        bytesToRead = int.from_bytes(self.ser.read(2), "little")
        return list(self.ser.read(bytesToRead))

    def TransmitBytes(self,dataToSend):
        #first transmit buffer length, then the actual data
        data = bytearray(dataToSend)
        self.ser.write(len(dataToSend).to_bytes(2, "little"))
        self.ser.write(data)

    def create_combined_spdm_prefix(self,SPDMversionString, context, isRequester):
        spdm_prefix = ("dmtf-spdm-v" + SPDMversionString + ".*") * 4
        spdm_context = "requester-" + context if isRequester else "responder-" + context
        zero_pad = b'\x00' * (100 - len(spdm_prefix.encode("ascii") + spdm_context.encode("ascii")) - 1)
        combined_spdm_prefix = spdm_prefix.encode("ascii") + bytes([0]) + zero_pad + spdm_context.encode("ascii")
        assert len(combined_spdm_prefix) == 100, f"combined_spdm_prefix should be 100 bytes long but it's {len(combined_spdm_prefix)} bytes long"
        return combined_spdm_prefix

    def SendQueryHostKey(self, putTestValues = False):
        cmd = bytearray([0xFA, 0x02, 0x01 if putTestValues else 0x00])
        print("----------------------------------------------------------------------")
        print("TEST CMD: Check HOST KEY Slot ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ",' '.join('{:02x}'.format(x) for x in response) )
        if len(response) != 1:
            return False
        if response[0] > 0x2:
            print("TEST CMD: Error received ")
            return False
        if response[0] == 0:
            print("TEST CMD: No HOST KEY present ")
        if response[0] == 1:
            print("TEST CMD: HOST KEY is present ")
        if response[0] == 2:
            print("TEST CMD: HOST KEY Slot was programmed with Test value ")
        return True

    def SendVerifySignature(self, pubX, pubY, signR, signS, digest):
        inputParam = [len(pubX)] + pubX + [len(pubY)] + pubY+ [len(signR)] + signR
        inputParam +=[len(signS)] + signS + [len(digest)] + digest
        
        cmd = bytearray([0xFA, 0x03]) +  bytearray(inputParam)
        print("----------------------------------------------------------------------")
        print("TEST VERIFY SIGNATURE ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ",' '.join('{:02x}'.format(x) for x in response) )
        if len(response) != 1:
            return False
        if response[0] == 1:
            print("TEST CVerify Signature: Signature is CORRECT ")
            return True
        if response[0] > 0x1:
            print("TEST Verify Signature: Error received ")
        if response[0] == 0:
            print("TEST Verify Signature: Signature is WRONG ")
        return False
        

    def SendEcho(self, param=bytearray([0x00, 0x01])):
        cmd = bytearray([0xFA, 0x00]) +  param
        print("----------------------------------------------------------------------")
        print("TEST CMD:Echo ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ",' '.join('{:02x}'.format(x) for x in response) )
        return bytearray(response)

    def SendQueryCurveType(self):
        cmd = bytearray([0xFA, 0x01])
        print("----------------------------------------------------------------------")
        print("TEST CMD: Check curve type in slot 0 ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ",' '.join('{:02x}'.format(x) for x in response) )
        if len(response) != 1:
            return False
        if response[0] > 0x3:
            print("TEST CMD: Error received ")
            return False
        if response[0] == 0:
            print("TEST CMD: NIST P-256 ")
        if response[0] == 1:
            print("TEST CMD: NIST P-384 ")
        if response[0] == 2:
            print("TEST CMD: Brainpool P-256 ")
        if response[0] == 3:
            print("TEST CMD: Brainpool P-384 ")
        return True

    def SendGetVersion(self, SPDMVersion=0x10):
        cmd = bytearray([SPDMVersion, 0x84, 0x00, 0x00])
        print("----------------------------------------------------------------------")
        print("GET_VERSION ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ",' '.join('{:02x}'.format(x) for x in response) )
        if len(response) < 6:
            return False
        if response[0] != SPDMVersion or response[1] != 0x04:
            return False
        if response[2] != 0x00 or response[3] != 0x00 or response[4] != 0x00:
            return False
        version_entries_count = response[5]
        print("Number of version entries: ", version_entries_count)
        if version_entries_count < 1:
            return False
        if len(response) != (6+2*version_entries_count):
            return False
        major_version = (response[7] >> 4) & 0xF
        minor_version = (response[7] & 0xF)
        self.version = major_version << 4 | minor_version
        print("Selected Version: ", hex(self.version))
        self.vca = cmd + bytearray(response)
        return True

    def SendGetCapabilities(self):
        if self.version == None:
            print("Error: Version is not set")
            return False
        cmd = bytearray([self.version, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00])
        print("----------------------------------------------------------------------")
        print("GET_CAPABILITIES ")
        print("Sending Command: ",  ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ", ' '.join('{:02x}'.format(x) for x in response))
        if len(response) < 20:
            return False
        if response[0] != self.version or response[1] != 0x61:
            return False
        if response[2] != 0x00 or response[3] != 0x00 or response[4] != 0x00 or response[5] != 0x00 or response[6] != 0x00 or response[7] != 0x00:
            return False
        CACHE_CAP = (response[8] >> 0) & 1
        CERT_CAP = (response[8] >> 1) & 1
        CHAL_CAP = (response[8] >> 2) & 1
        MEAS_CAP = (response[8] >> 3) & 3
        MEAS_FRESH_CAP = (response[8] >> 5) & 1
        ENCRYPT_CAP = (response[8] >> 6) & 1
        MAC_CAP = (response[8] >> 7) & 1
        print("CACHE_CAP: ", CACHE_CAP)
        print("CERT_CAP: ", CERT_CAP)
        print("CHAL_CAP: ", CHAL_CAP)
        print("MEAS_CAP: ", MEAS_CAP)
        print("MEAS_FRESH_CAP: ", MEAS_FRESH_CAP)
        print("ENCRYPT_CAP: ", ENCRYPT_CAP)
        print("MAC_CAP: ", MAC_CAP)
        if CERT_CAP != 1 or CHAL_CAP != 1 or MEAS_CAP != 2:
            return False
        DataTransferSize = (response[12] << 24) | (response[13] << 16) | (response[14] << 8) |response[15]
        MaxSPDMmsgSize = (response[16] << 24) | (response[17] << 16) | (response[18] << 8) |response[19]
        print ("DataTransferSize: " + str(DataTransferSize) + " bytes")
        print ("MaxSPDMmsgSize: " + str(MaxSPDMmsgSize) + " bytes")
        self.vca += cmd + bytearray(response)
        return True

    def SendNegotiateAlgorithms(self):
        if self.version == None:
            print("Error: Version is not set")
            return
        cmd = bytearray([self.version,
                         0xE3, 0x4,0, 0x30, 0, #version, cmd code, Number of algorithms structure tables, length of full message,
                 0x1,0x0,  #Measurement Specs, other Params support
                 0xFF, 0x0f, 0,0x0, #base Asym Algo
                 0x7F, 0, 0,0, #base hash algo
                 0,0,0,0,0,0,0,0,0,0,0,0,  #reserved
                 0,0,0,0, #ExtAsymCount, ExtHashCount, 2 bytes reserved
               #ReqAlgStruct - 4 incoming
               0x2, 0x20, 0x7F, 0, #Alg struct
               0x3, 0x20, 0x0F, 0, #Alg struct
               0x4, 0x20, 0xFF, 0x5, #Alg struct
               0x5, 0x20, 0x1, 0 #Alg struct
        ])
        print("----------------------------------------------------------------------")
        print("NEGOTIATE_ALGORITHMS ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ", ' '.join('{:02x}'.format(x) for x in response))
        if len(response) < 36:
            return False
        if response[0] != self.version or response[1] != 0x63:
            return False
        num_resp_alg = response[2]
        if response[3] != 0x00:
            return False
        resp_len = (response[5] << 8) | response[4]
        if resp_len != len(response):
            return False
        measurement_hash_algo = []
        base_asym_sel = []
        base_hash_sel = []
        if response[8] &  0b00000001:
            measurement_hash_algo.append("Raw Bit Stream Only")
        if response[8] &  0b00000010:
            measurement_hash_algo.append("TPM_ALG_SHA_256")
        if response[8] & 0b00000100:
            measurement_hash_algo.append("TPM_ALG_SHA_384")
        if response[8] & 0b00001000:
            measurement_hash_algo.append("TPM_ALG_SHA_512")
        if response[8] & 0b00010000:
            measurement_hash_algo.append("TPM_ALG_SHA3_256")
        if response[8] & 0b00100000:
            measurement_hash_algo.append("TPM_ALG_SHA3_384")
        if response[8] & 0b01000000:
            measurement_hash_algo.append("TPM_ALG_SHA3_512")
        if response[8] & 0b10000000:
            measurement_hash_algo.append("TPM_ALG_SM3_256")
        # check BaseAsymSel
        if response[12] & 0b00000001:
            base_asym_sel.append("TPM_ALG_RSASSA_2048")
        if response[12] & 0b00000010:
            base_asym_sel.append("TPM_ALG_RSAPSS_2048")
        if response[12] & 0b00000100:
            base_asym_sel.append("TPM_ALG_RSASSA_3072")
        if response[12] & 0b00001000:
            base_asym_sel.append("TPM_ALG_RSAPSS_3072")
        if response[12] & 0b00010000:
            base_asym_sel.append("TPM_ALG_ECDSA_ECC_NIST_P256")
        if response[12] & 0b00100000:
            base_asym_sel.append("TPM_ALG_RSASSA_4096")
        if response[12] & 0b01000000:
            base_asym_sel.append("TPM_ALG_RSAPSS_4096")
        if response[12] & 0b10000000:
            base_asym_sel.append("TPM_ALG_ECDSA_ECC_NIST_P384")
        if response[13] & 0b00000001:
            base_asym_sel.append("TPM_ALG_ECDSA_ECC_NIST_P521")
        if response[13]  & 0b00000010:
            base_asym_sel.append("TPM_ALG_SM2_ECC_SM2_P256")
        if response[13]  & 0b00000100:
            base_asym_sel.append("EdDSA_ed25519")
        if response[13]  & 0b00001000:
            base_asym_sel.append("EdDSA_ed448")
        if response[13]  & 0b11110000:
            return False
        
        if response[16] & 0b00000001:
            base_hash_sel.append("TPM_ALG_SHA_256")
        if response[16] & 0b00000010:
            base_hash_sel.append("TPM_ALG_SHA_384")
        if response[16] & 0b00000100:
            base_hash_sel.append("TPM_ALG_SHA_512")
        if response[16] & 0b00001000:
            base_hash_sel.append("TPM_ALG_SHA3_256")
        if response[16] & 0b00010000:
            base_hash_sel.append("TPM_ALG_SHA3_384")
        if response[16] & 0b00100000:
            base_hash_sel.append("TPM_ALG_SHA3_512")
        if response[16]  & 0b11000000:
            return False
        resp_alg_struct = response[36:]
        self.baseHashSel = base_hash_sel[0]
        self.measurementHashAlgo = measurement_hash_algo[0]
        result = {"MeasurementHashAlgo": measurement_hash_algo, 
              "BaseAsymSel": base_asym_sel, "BaseHashSel": base_hash_sel, "RespAlgStruct": resp_alg_struct}
        if bytes(response[9:12] + response[14:16] + response[17:20] + response[20:36]) != b'\x00' * 24:
            return False
        print (result)
        #todo parse RegAlgStruct
        if len(result["MeasurementHashAlgo"])!=1 or len(result["BaseHashSel"])!=1 or len(result["BaseAsymSel"])!=1:
            return False
        self.vca += cmd + bytearray(response)
        self.algo=result
        return True

    def SendGetCertificate(self, slot_id=0, offset=0, length=0xFFFF):
        if self.version == None:
            print("Error: Version is not set")
            return False
        cmd = bytearray([self.version, 0x82, (slot_id & 0x0F), 0x00,  offset & 0xFF,(offset >> 8) & 0xFF,
                         length & 0xFF,(length >> 8) & 0xFF])
        
        print("----------------------------------------------------------------------")
        print("GET_CERTIFICATE ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ", ' '.join('{:02x}'.format(x) for x in response))
        if (response[0] != self.version or response[1] != 0x02 or response[2] != (slot_id & 0x0F) or response[3] != 0x00):
            raise ValueError("Invalid response")
        
        portion_length = (response[5] << 8) | response[4]
        remainder_length = (response[7] << 8) | response[6]
        certificate = response[8:]
        
        if (len(certificate) != portion_length):
            print ("Portion Length is " + str(portion_length))
            print ("Certificate Length is " + str(len(certificate)) )
            raise ValueError("Invalid certificate length")
        self.certificate += certificate
        self.b4 += cmd + bytearray(response)
        return remainder_length

    def VerifyCertificateChain(self):
        print("-----OPTIONAL STEP - VERIFYING IF LEAF CERT WAS SIGNED BY ROOT(should be done by Requester)---------------------------")
        #print("Certificate Chain: ", ' '.join('{:02x}'.format(x) for x in self.certificate))
        chainLen = (self.certificate[1] << 8) | self.certificate[0]
        if (len(self.certificate) != chainLen):
            print ("Expected Certificate Chain Length is " + str(chainLen))
            print ("Actual Certificate Chain Length is " + str(len(self.certificate)) )
            return False
        if self.baseHashSel == 'TPM_ALG_SHA_384':
            alg ='sha384'
            digest = self.certificate[4:52]
            self.certificate = self.certificate[52:]
        elif self.baseHashSel == 'TPM_ALG_SHA_256':
            alg ='sha256'
            digest = self.certificate[4:36]
            self.certificate = self.certificate[36:]
        else:
            raise ValueError("Not implemented hash algorithm " + self.baseHashSel)
        
        #not a real parsing of x509 here, for quick test only
        rootLen = (self.certificate[2] << 8) | self.certificate[3]
        rootLen += 4 #to account for first 4 bytes where len is coded
        # Get the root certificate in the chain
        root_cert = self.certificate[:rootLen]
        self.certificate = self.certificate[rootLen:]
        
        h = hashlib.new(alg)
        h.update(bytes(root_cert))
        certHash=h.digest()
        if certHash != bytes(digest):
            print ("Root Certificate  - "+' '.join('{:02x}'.format(x) for x in root_cert))
            print ("Computed Root Certificate Digest - "+' '.join('{:02x}'.format(x) for x in certHash))
            print ("Received Root Certificate Digest - "+' '.join('{:02x}'.format(x) for x in bytes(digest)))
            raise ValueError("Invalid certificate hash")
        
        root_cert_parsed = Certificate.load(bytes(root_cert))
        leaf_cert_parsed = Certificate.load(bytes(self.certificate))
        try:
            derSignature = leaf_cert_parsed.signature
            leafCertInput = leaf_cert_parsed.dump()
            leafCertInputSize = ((leafCertInput[6] << 8) | leafCertInput[7]) +4
            leafCertInput = leafCertInput[4:leafCertInputSize+4]
            #print ("Leaf Certificate signature- "+' '.join('{:02x}'.format(x) for x in derSignature))
            #print ("Leaf Certificate signature input- "+' '.join('{:02x}'.format(x) for x in leafCertInput))
            
            rLen = derSignature[3]
            sLen = derSignature[5 + rLen]
            rOffset = 4
            sOffset = 6 + rLen
            if derSignature[rOffset] == 0:
                rOffset+=1
                rLen -=1
            if derSignature[sOffset] == 0:
                sOffset+=1
                sLen -=1
            rs = derSignature[rOffset:rOffset + rLen]+derSignature[sOffset:]
            alg = hashlib.sha256
            if "sha384_ecdsa" == leaf_cert_parsed["tbs_certificate"]["signature"]["algorithm"].native:
                alg = hashlib.sha384
            public_key_info = root_cert_parsed.public_key
            public_key = VerifyingKey.from_der(public_key_info.dump())
            public_key.verify(
                rs,
                leafCertInput,
                alg
            )
            print("Chain of trust verified successfully!")
        except Exception as e:
            print("Chain of trust verification failed:", e)
                
        return True
    
    def SendChallenge(self, slot_id=0, measurement_type=0x00):
        cmd = [self.version, 0x83, slot_id,measurement_type]
        randomlist = random.sample(range(0, 255), 32)
        cmd = bytearray(cmd+randomlist)
        print("----------------------------------------------------------------------")
        print("CHALLENGE ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ", ' '.join('{:02x}'.format(x) for x in response))
        if response[0] != self.version or response[1] != 0x03:
            raise ValueError("Invalid response")
        if response[2] != slot_id:
            raise ValueError("Invalid slot id in response")
        if self.baseHashSel == 'TPM_ALG_SHA_384':
            alg ='sha384'
            vkParam = hashlib.sha384
            certificate_hash = response[4:52]
            nonce = response[52:84]
            offset=84
            if measurement_type != 0x00:
                measurement_summary_hash = response[84:132]
                offset=132
            else:
                measurement_summary_hash = None
        elif self.baseHashSel == 'TPM_ALG_SHA_256':
            alg ='sha256'
            vkParam = hashlib.sha256
            certificate_hash = response[4:36]
            nonce = response[36:68]
            offset=68
            if measurement_type != 0x00:
                measurement_summary_hash = response[68:100]
                offset=100
            else:
                measurement_summary_hash = None
        else:
            raise ValueError("Not implemented hash algorithm " + self.baseHashSel)
        
        
        sig_len = 64 if self.algo["BaseAsymSel"] == ['TPM_ALG_ECDSA_ECC_NIST_P256'] else 96
        signature = response[offset:]
        if (len(signature) != sig_len):
            raise ValueError("Invalid signature length")
        h = hashlib.new(alg)
        h.update(bytes(self.certificate))
        certHash=h.digest()
        if certHash != bytes(certificate_hash):
            print (' '.join('{:02x}'.format(x) for x in certHash))
            print (' '.join('{:02x}'.format(x) for x in bytes(certificate_hash)))
            raise ValueError("Invalid certificate hash")
        h = hashlib.new(alg)
        inputData = bytearray(self.vca) + bytearray(self.b4)
        inputData+= cmd + bytearray(response[:-sig_len])
        h.update(bytes(inputData))
        m2=h.digest()
        cert = Certificate.load(bytes(self.certificate))
        public_key_info = cert.public_key
        # Check if it's an EC key
        if public_key_info.algorithm == 'ec':
            # Get the curve type
            curve_type = public_key_info['algorithm']['parameters'].native
            print("\n Curve type:", curve_type)
            print("Above curve type value secp256r1 or prime256v1 correspond to NIST P-256, value secp384r1 correspond to NIST P-384 \n ")

            # Get the public key value
            public_key_value = public_key_info['public_key'].native
            print("Public key value:", public_key_value.hex())
            print("\n")
        else:
            print("Not an EC key")
        print("  - Computed M2 hash: "+ ''.join('{:02x}'.format(x) for x in m2))
        digestInput = hashlib.new(alg)
        digestInput.update(self.create_combined_spdm_prefix("1.2","challenge_auth signing", False)+m2)
        digestInput = digestInput.digest()
        print(" - Computed digest for signing: "+''.join('{:02x}'.format(x) for x in digestInput) )
        print ("  - Received signature: "+  ''.join('{:02x}'.format(x) for x in signature))
        vk = None
        if self.algo["BaseAsymSel"] == ['TPM_ALG_ECDSA_ECC_NIST_P256']:
            vk = VerifyingKey.from_string(Certificate.load(bytes(self.certificate)).public_key.native["public_key"], NIST256p, vkParam)
        else:
            vk = VerifyingKey.from_string(Certificate.load(bytes(self.certificate)).public_key.native["public_key"], NIST384p, vkParam)
        if not vk.verify(bytes(signature),self.create_combined_spdm_prefix("1.2","challenge_auth signing", False)+m2):
            raise ValueError("Invalid signature")
        print ("signature verification is successful. Device is authenticated")    
        return True

    def SendMeasurement(self, measBlock,  isSignatureRequested=False,slot_id=0,):
        cmd = [self.version, 0xE0, 0,measBlock]
        if isSignatureRequested:
            cmd[2] = 1
            randomlist = random.sample(range(0, 255), 32)
            cmd = bytearray(cmd+randomlist + [slot_id&0xF])
        else:
            cmd = bytearray(cmd)
        print("----------------------------------------------------------------------")
        print("GET_MEASUREMENTS ")
        print("Sending Command: ", ' '.join('{:02x}'.format(x) for x in cmd))
        response = self.SendCmd(cmd)
        print("Received Response: ", ' '.join('{:02x}'.format(x) for x in response))
        if (response[0] != self.version or response[1] != 0x60 or response[2] != 0 or response[4] != 0x01):
            raise ValueError("Invalid response")
        if isSignatureRequested:
            if response[3] &0xF != slot_id:
                raise ValueError("Invalid slotID")
        else :
             if response[3] != 0:
                 raise ValueError("Invalid Param2")
        if (response[5] != 0x0 or response[6] != 0x0):
            raise ValueError("Invalid MeasurementRecordLength")
        if (response[8] != measBlock or response[9] != 0x1 or response[10] != 0x00):
            raise ValueError("Invalid Measurement block format")
        if (response[12] != 0x00 or response[13] != 0x0 ):
            raise ValueError("Invalid DMTFSpecMeasurement block")
        if self.measurementHashAlgo == 'TPM_ALG_SHA_384':
            if response[7] != 0x37:
                raise ValueError("Invalid MeasurementRecordLength")
            if response[11] != 0x33:
                raise ValueError("Invalid Measurement block format")
            if response[14] != 0x30:
                raise ValueError("Invalid DMTFSpecMeasurement block")
            alg ='sha384'
            vkParam = hashlib.sha384
            measHash = response[15:63]
            nonce = response[63:95]
            sigOffset = 95
        elif self.measurementHashAlgo == 'TPM_ALG_SHA_256':
            if response[7] != 0x27:
                raise ValueError("Invalid MeasurementRecordLength")
            if response[11] != 0x23:
                raise ValueError("Invalid Measurement block format")
            if response[14] != 0x20:
                raise ValueError("Invalid DMTFSpecMeasurement block")
            alg ='sha256'
            vkParam = hashlib.sha256
            measHash = response[15:47]
            nonce = response[47:79]
            sigOffset = 79
        else:
            raise ValueError("Not implemented hash algorithm " + self.baseHashSel)
        print("Measurement Hash: ", ' '.join('{:02x}'.format(x) for x in measHash))
        print("Measurement Nonce: ", ' '.join('{:02x}'.format(x) for x in nonce))
        if isSignatureRequested:
            sig_len = 64 if self.algo["BaseAsymSel"] == ['TPM_ALG_ECDSA_ECC_NIST_P256'] else 96
            signature = response[sigOffset:]
            if (len(signature) != sig_len):
                raise ValueError("Invalid signature length")
            self.unsignedMeas+=cmd + bytearray(response[:-sig_len])
            h = hashlib.new(alg)
            inputData = bytearray(self.vca) + bytearray(self.unsignedMeas)
            h.update(bytes(inputData))
            l2=h.digest()
            print("  - Computed L2 hash: "+ ''.join('{:02x}'.format(x) for x in l2))
            print ("  - Received signature: "+  ''.join('{:02x}'.format(x) for x in signature))
            if self.algo["BaseAsymSel"] == ['TPM_ALG_ECDSA_ECC_NIST_P256']:
                vk = VerifyingKey.from_string(Certificate.load(bytes(self.certificate)).public_key.native["public_key"], NIST256p, vkParam)
            else:
                vk = VerifyingKey.from_string(Certificate.load(bytes(self.certificate)).public_key.native["public_key"], NIST384p, vkParam)
            if not vk.verify(bytes(signature),self.create_combined_spdm_prefix("1.2","measurements signing", False)+l2):
                raise ValueError("Invalid signature")
            print ("signature verification is successful. Measurements authenticated")     
            self.unsignedMeas=[]
        else:
            self.unsignedMeas+=cmd + bytearray(response)
        return True
            

class TestSPDMRequester(unittest.TestCase):
    comPortName = "COM26"
    def test_ok(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        self.assertEqual("SPDM Requester", requester.name)
        self.assertEqual(True, requester.SendGetVersion())
        self.assertEqual(True, requester.SendGetCapabilities())
        self.assertEqual(True, requester.SendNegotiateAlgorithms())
        self.assertEqual(0, requester.SendGetCertificate())
        self.assertEqual(True, requester.VerifyCertificateChain())
        self.assertEqual(True, requester.SendChallenge(0,0))
        self.assertEqual(True, requester.SendMeasurement(measBlock=1))
        self.assertEqual(True, requester.SendMeasurement(measBlock=2,isSignatureRequested=True))
        self.assertEqual(True, requester.SendMeasurement(measBlock=3,isSignatureRequested=True))
        print("OK")

    def test_TestCMDBigCurve(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        requester.baseHashSel = 'TPM_ALG_SHA_384'
        requester.certificate = [0xe3,0x03,0x00,0x00,0xb7,0x75,0x3e,0x97,0x3f,0x03,0x1d,0x6d,0x61,0xf1,0x93,0x49,0xb3,0xc1,0x13,0x8c,0xfa,0x72,0x9e,0xce,0xf8,0xc0,0x7d,0xc7,0xf1,0x67,0x71,0xbd,0x99,0x91,0x6c,0x20,0xbb,0x66,0x98,0xa0,0x74,0x0f,0xd9,0x81,0x7b,0x08,0x8e,0xc5,0xef,0xc7,0xa2,0xe4,0x30,0x82,0x01,0xdd,0x30,0x82,0x01,0x63,0xa0,0x03,0x02,0x01,0x02,0x02,0x01,0x01,0x30,0x0a,0x06,0x08,0x2a,0x86,0x48,0xce,0x3d,0x04,0x03,0x03,0x30,0x4f,0x31,0x0b,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x4e,0x4c,0x31,0x1e,0x30,0x1c,0x06,0x03,0x55,0x04,0x0a,0x0c,0x15,0x53,0x54,0x4d,0x69,0x63,0x72,0x6f,0x65,0x6c,0x65,0x63,0x74,0x72,0x6f,0x6e,0x69,0x63,0x73,0x20,0x6e,0x76,0x31,0x20,0x30,0x1e,0x06,0x03,0x55,0x04,0x03,0x0c,0x17,0x53,0x54,0x4d,0x20,0x53,0x54,0x53,0x41,0x46,0x45,0x2d,0x41,0x20,0x54,0x45,0x53,0x54,0x20,0x43,0x41,0x20,0x30,0x32,0x30,0x1e,0x17,0x0d,0x32,0x33,0x30,0x35,0x33,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x5a,0x17,0x0d,0x34,0x33,0x30,0x35,0x33,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x5a,0x30,0x4f,0x31,0x0b,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x4e,0x4c,0x31,0x1e,0x30,0x1c,0x06,0x03,0x55,0x04,0x0a,0x0c,0x15,0x53,0x54,0x4d,0x69,0x63,0x72,0x6f,0x65,0x6c,0x65,0x63,0x74,0x72,0x6f,0x6e,0x69,0x63,0x73,0x20,0x6e,0x76,0x31,0x20,0x30,0x1e,0x06,0x03,0x55,0x04,0x03,0x0c,0x17,0x53,0x54,0x4d,0x20,0x53,0x54,0x53,0x41,0x46,0x45,0x2d,0x41,0x20,0x54,0x45,0x53,0x54,0x20,0x43,0x41,0x20,0x30,0x32,0x30,0x76,0x30,0x10,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x02,0x01,0x06,0x05,0x2b,0x81,0x04,0x00,0x22,0x03,0x62,0x00,0x04,0xe7,0xab,0xd5,0xad,0x60,0x1e,0xe6,0x49,0x57,0x0b,0x7a,0xc5,0x15,0xa3,0x3b,0x27,0x33,0x99,0x15,0xa3,0x92,0x5a,0x4d,0x49,0x0b,0x09,0x80,0x15,0xae,0x08,0x50,0xa8,0x1e,0xc0,0x8f,0x2e,0xff,0x4e,0x04,0xea,0xee,0xe4,0xa1,0x79,0x49,0x52,0x80,0x7a,0xe0,0xb4,0x67,0xa8,0xb4,0x39,0x87,0x97,0x09,0x76,0x38,0x5a,0x9b,0x04,0xc9,0x50,0x99,0x02,0xfc,0xfc,0xc3,0x49,0xaf,0xe4,0x54,0x8a,0x77,0x3e,0xa2,0xb7,0xb8,0x8e,0x2b,0xf6,0x2c,0xf0,0x0b,0x8f,0xe9,0xec,0x49,0x77,0xab,0x24,0xda,0x7b,0x14,0x7a,0xa3,0x13,0x30,0x11,0x30,0x0f,0x06,0x03,0x55,0x1d,0x13,0x01,0x01,0xff,0x04,0x05,0x30,0x03,0x01,0x01,0xff,0x30,0x0a,0x06,0x08,0x2a,0x86,0x48,0xce,0x3d,0x04,0x03,0x03,0x03,0x68,0x20,0x30,0x65,0x02,0x30,0x51,0x02,0x5a,0xeb,0x7a,0x19,0x03,0xa6,0x3d,0xdb,0xf7,0x55,0x96,0x64,0xd4,0xb1,0xa4,0xdb,0x20,0x1e,0x3b,0x7a,0x89,0x5d,0xbe,0x7f,0x91,0xa6,0x16,0xab,0x78,0x98,0x22,0xfe,0x94,0xbc,0x53,0x6b,0x60,0x91,0x20,0x54,0xf2,0x50,0x15,0xc3,0xf8,0xed,0x02,0x31,0x20,0x94,0x12,0xc4,0x7e,0x6d,0x57,0x55,0x66,0x9a,0x18,0xd7,0x14,0x73,0x51,0x3d,0xfd,0xee,0x78,0x56,0x79,0x90,0xdf,0x97,0xa5,0x17,0x41,0xf3,0x0f,0x88,0x1e,0xfb,0xc1,0x73,0x06,0x15,0x64,0x9e,0x8b,0x14,0xed,0xb8,0x1e,0xc3,0x07,0xab,0x54,0x8b,0x2f,
        0x30, 0x82, 0x01, 0xCA, 0x30, 0x82, 0x01, 0x50, 0xA0, 0x03, 0x02, 0x01,
	0x02, 0x02, 0x0B, 0x02, 0x09, 0x40, 0xD1, 0xE1, 0x21, 0xC4, 0xE1, 0xD0,
	0x01, 0x39, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04,
	0x03, 0x03, 0x30, 0x4F, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
	0x06, 0x13, 0x02, 0x4E, 0x4C, 0x31, 0x1E, 0x30, 0x1C, 0x06, 0x03, 0x55,
	0x04, 0x0A, 0x0C, 0x15, 0x53, 0x54, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x65,
	0x6C, 0x65, 0x63, 0x74, 0x72, 0x6F, 0x6E, 0x69, 0x63, 0x73, 0x20, 0x6E,
	0x76, 0x31, 0x20, 0x30, 0x1E, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x17,
	0x53, 0x54, 0x4D, 0x20, 0x53, 0x54, 0x53, 0x41, 0x46, 0x45, 0x2D, 0x41,
	0x20, 0x54, 0x45, 0x53, 0x54, 0x20, 0x43, 0x41, 0x20, 0x30, 0x32, 0x30,
	0x20, 0x17, 0x0D, 0x32, 0x33, 0x31, 0x32, 0x31, 0x31, 0x30, 0x30, 0x30,
	0x30, 0x30, 0x30, 0x5A, 0x18, 0x0F, 0x32, 0x30, 0x35, 0x33, 0x30, 0x35,
	0x31, 0x39, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5A, 0x30, 0x45, 0x31,
	0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x0A, 0x53, 0x75,
	0x70, 0x65, 0x72, 0x6D, 0x69, 0x63, 0x72, 0x6F, 0x31, 0x2E, 0x30, 0x2C,
	0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x25, 0x53, 0x75, 0x70, 0x65, 0x72,
	0x6D, 0x69, 0x63, 0x72, 0x6F, 0x2D, 0x30, 0x32, 0x30, 0x42, 0x30, 0x32,
	0x30, 0x39, 0x34, 0x30, 0x44, 0x31, 0x45, 0x31, 0x32, 0x31, 0x43, 0x34,
	0x45, 0x31, 0x44, 0x30, 0x30, 0x31, 0x33, 0x39, 0x30, 0x76, 0x30, 0x10,
	0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x05, 0x2B,
	0x81, 0x04, 0x00, 0x22, 0x03, 0x62, 0x00, 0x04, 0xB6, 0xA1, 0xD7, 0x16,
	0xD0, 0x24, 0xA6, 0x23, 0xC1, 0xD0, 0x10, 0x47, 0x94, 0x59, 0x1F, 0x96,
	0x0D, 0x33, 0xDF, 0xF4, 0xFC, 0x6F, 0xB6, 0x30, 0xD3, 0xF2, 0x86, 0xAB,
	0x9C, 0xAC, 0x71, 0xB9, 0xF4, 0xEE, 0x20, 0x12, 0x9F, 0x96, 0x1D, 0xFA,
	0x8D, 0xC3, 0x26, 0xB1, 0x74, 0x50, 0xE2, 0x84, 0x76, 0x27, 0x43, 0xD0,
	0x8C, 0x73, 0x91, 0xB2, 0x83, 0xB0, 0x83, 0x48, 0x16, 0x45, 0x14, 0xC6,
	0xD7, 0x01, 0x60, 0xA0, 0x7F, 0x35, 0x47, 0xC9, 0x22, 0x2D, 0xA1, 0x38,
	0x37, 0x9C, 0x6F, 0x04, 0x3C, 0x60, 0x3D, 0xD7, 0x53, 0x51, 0x1E, 0x25,
	0xDC, 0x8E, 0xFF, 0x78, 0x0E, 0xAC, 0x9C, 0x6C, 0x30, 0x0A, 0x06, 0x08,
	0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x03, 0x03, 0x68, 0x00, 0x30,
	0x65, 0x02, 0x31, 0x00, 0x80, 0x0F, 0xED, 0x7B, 0x43, 0x5F, 0x4D, 0xCC,
	0x90, 0xEF, 0x94, 0x78, 0xA0, 0xFC, 0x21, 0xF2, 0xD2, 0x04, 0xB8, 0xF0,
	0xBC, 0xC4, 0x56, 0xB8, 0x8B, 0xB3, 0x10, 0xA2, 0xC4, 0xFD, 0x1C, 0x0B,
	0x80, 0x03, 0xB1, 0xCB, 0x9D, 0x4B, 0x35, 0xE4, 0xB2, 0x9D, 0xCF, 0x59,
	0x15, 0x89, 0x85, 0x9B, 0x02, 0x30, 0x1C, 0xD2, 0x3A, 0x0B, 0x07, 0x36,
	0x88, 0x8C, 0x3D, 0x8E, 0x7B, 0x4C, 0x18, 0x24, 0x52, 0xA8, 0x42, 0x41,
	0x2A, 0x2C, 0xEA, 0x32, 0xE0, 0x8A, 0x15, 0xDF, 0x74, 0x0F, 0x8D, 0xEF,
	0x1A, 0xC6, 0x5B, 0x89, 0xB9, 0x5E, 0x0C, 0x28, 0xCE, 0xED, 0xB1, 0xC1,
	0xBD, 0x4D, 0x64, 0x86, 0x07, 0xB1]
        self.assertEqual(True, requester.VerifyCertificateChain())
        
    
    def test_TestCMD(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        self.assertEqual("SPDM Requester", requester.name)
        self.assertEqual(True, requester.SendQueryCurveType())
        echoParam=bytearray([0x00, 0x01,0xAA,0x03])
        self.assertEqual(echoParam, requester.SendEcho(echoParam))
        self.assertEqual(True, requester.SendQueryHostKey())
        #enable below line to Put test key values into HOST Key slots
        #self.assertEqual(True, requester.SendQueryHostKey(True))

    def test_TestVerifySignature1(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        self.assertEqual("SPDM Requester", requester.name)
        pubX = [0x39, 0xD4, 0x2B, 0xBD, 0xA9, 0x90, 0xAF, 0x39,
	    0x45, 0x39, 0x4E, 0xCC, 0x7B, 0xFC, 0xA5, 0xBA,
	    0xFB, 0x91, 0x57, 0x5D, 0x58, 0xE2, 0x3E, 0xFF,
	    0x1D, 0xD5, 0xAC, 0xD0, 0x0B, 0x84, 0x04, 0xBE]
        pubY = [0x32, 0xEB, 0xCD, 0x50, 0x5A, 0x46, 0xDE, 0xA6,
	    0xAB, 0x67, 0x9B, 0xC5, 0xB8, 0x66, 0x94, 0x1E,
	    0x46, 0x28, 0x72, 0x94, 0xD4, 0x3E, 0xD0, 0x36,
	    0xE8, 0x45, 0x9E, 0x7F, 0x2D, 0x67, 0xA1, 0x8F]
        signR = [0x2B, 0xB5, 0x82, 0x4B, 0x41, 0xE1, 0x00, 0xB4,
	    0x09, 0x0F, 0x99, 0x41, 0x64, 0x07, 0x98, 0xD0,
	    0x4A, 0xBB, 0x85, 0xD8, 0xD9, 0x13, 0x95, 0xB4,
	    0x21, 0xC5, 0xDD, 0x67, 0xF4, 0xDF, 0x9C, 0x37]
        signS = [0x47, 0xF6, 0x57, 0x26, 0x62, 0xA6, 0x2E, 0x1C,
	    0x18, 0x23, 0x52, 0x39, 0x97, 0x5B, 0xC5, 0xB2,
	    0x95, 0xA1, 0xD9, 0xC1, 0x70, 0xE7, 0x1C, 0x8A,
	    0xEF, 0xD3, 0x0F, 0xF8, 0xDA, 0xAF, 0x4A, 0x72]
        digest = [0xB3, 0x03, 0x54, 0x27, 0xD8, 0x66, 0x8B, 0x7A,
	    0x37, 0x94, 0x9A, 0x54, 0x24, 0x80, 0xB3, 0xB8,
	    0xB6, 0x4F, 0x43, 0x2D, 0x52, 0x52, 0x3B, 0xCC,
	    0x2A, 0x4B, 0x14, 0xBB, 0x48, 0xA3, 0x85, 0xF1]
        self.assertEqual(True, requester.SendVerifySignature(pubX, pubY, signR, signS, digest))

    def test_TestVerifySignature2(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        self.assertEqual("SPDM Requester", requester.name)
        pubX = [0x3F, 0xCB, 0x4B, 0xF2, 0x82, 0x58, 0x12, 0x3E,
	    0x40, 0x0D, 0xDE, 0xD2, 0x0D, 0xEC, 0x67, 0x9F,
	    0xA6, 0x81, 0x72, 0xDD, 0x3F, 0x0C, 0x35, 0x6B,
	    0x8D, 0x92, 0x50, 0x7C, 0x7F, 0xB2, 0xB1, 0x15]
        pubY = [0x65, 0x3F, 0x18, 0x6A, 0x85, 0x5C, 0x31, 0x5B,
	    0xEA, 0x68, 0x4C, 0xB7, 0x55, 0xE2, 0xA8, 0xA8,
	    0x7A, 0xD9, 0x0D, 0x7B, 0xFD, 0x89, 0xAB, 0x62,
	    0xEC, 0xBC, 0xB6, 0x26, 0x4B, 0x7F, 0xA5, 0xA9]
        signR = [0x46, 0xBD, 0xF0, 0x8B, 0x3D, 0xD6, 0x23, 0x42,
	    0x4F, 0xBB, 0x65, 0xDB, 0x50, 0x30, 0xC5, 0x7C,
	    0x6D, 0xF6, 0xFC, 0xBF, 0xAA, 0xC8, 0xFC, 0x0D,
	    0xAF, 0xD0, 0xA5, 0xC1, 0x05, 0x95, 0xCB, 0x6C]
        signS = [0x00, 0x9B, 0x2D, 0xB4, 0x6B, 0x4F, 0x38, 0xC6,
                 0x7C, 0x37, 0xC8, 0x49, 0x79, 0xCC, 0x07, 0x2F,
                 0x1E, 0x45, 0xC2, 0x9F, 0xE2, 0x1B, 0xA3, 0xC1,
                 0xFF, 0x80, 0x91, 0x14, 0x1E, 0x5A, 0x33, 0x68, 0xC0]
        digest = [0xB3, 0x03, 0x54, 0x27, 0xD8, 0x66, 0x8B, 0x7A,
	    0x37, 0x94, 0x9A, 0x54, 0x24, 0x80, 0xB3, 0xB8,
	    0xB6, 0x4F, 0x43, 0x2D, 0x52, 0x52, 0x3B, 0xCC,
	    0x2A, 0x4B, 0x14, 0xBB, 0x48, 0xA3, 0x85, 0xF1]
        self.assertEqual(True, requester.SendVerifySignature(pubX, pubY, signR, signS, digest))

    def test_TestVerifySignature3(self):
        com_port = TestSPDMRequester.comPortName
        requester = SPDMRequester(com_port)
        self.assertEqual("SPDM Requester", requester.name)
        pubX = [0xba,0xbf,0xab,0xec,0xd1,0xb3,0x37,0xf4,
                0x9c,0x3e,0x16,0x9f,0x8a,0x99,0xc0,0xc1,
                0x41,0xfe,0x8c,0x7b,0xfc,0x25,0x99,0xf1,
                0x46,0x2f,0x6b,0xec,0xa6,0x6c,0xc9,0xc6]
        pubY = [0xbd,0x0b,0xd9,0x2f,0x0f,0x66,0xec,0x84,
                0x53,0x7d,0xe9,0xc8,0xde,0x48,0xff,0x84,
                0x6c,0x9f,0xdc,0xa5,0x21,0x1d,0x5b,0x77,
                0xea,0x69,0xc2,0x1b,0xe1,0x49,0x5a,0xa4]
        signR = [0x32,0x77,0x1b,0x9f,0xa6,0x73,0x15,0x36,0xaa,0xc1,0x66,0xaa,0x24,0x12,0xaa,0x69,0x16,0x44,0xcc,0xc1,0xa9,0x8b,0x9e,0x92,0x9d,0xe3,0xb3,0x69,0x83,0x7b,0x88,0xde]
        signS = [0x0d,0x90,0x68,0x98,0x0f,0xbf,0x89,0x87,0x45,0x38,0xbb,0x89,0xb7,0x6f,0x62,0x7c,0xa1,0x67,0x15,0xb4,0x67,0x14,0xdf,0x6f,0x8a,0x2b,0x25,0x14,0xcb,0xaf,0x7d,0x8c]
        digest = [0x2b,0xa7,0x1d,0xe5,0x20,0x52,0x66,0x4a,0x4e,0x5f,0x6b,0x49,0xda,0xe4,0x20,0xc5,0x60,0x71,0x44,0x9e,0xb8,0xd8,0x51,0xcb,0x05,0xfe,0xca,0x80,0x9f,0xaf,0xe9,0x39,0x2e,0x9a,0xd3,0xdc,0x55,0xa3,0xd6,0x4b,0x26,0xe8,0x6b,0x49,0x39,0xcf,0x24,0xc5]
        self.assertEqual(True, requester.SendVerifySignature(pubX, pubY, signR, signS, digest))    

if __name__ == '__main__':
    unittest.main()
