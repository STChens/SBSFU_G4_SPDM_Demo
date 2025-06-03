# Copyright(c) 2018 STMicroelectronics International N.V.
# Copyright 2017 Linaro Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
from Crypto.Cipher import AES
from Crypto.Hash import SHA384
from ecdsa import SigningKey, VerifyingKey, NIST384p, util
from Crypto.Hash import SHA256
from ecdsa import SigningKey, VerifyingKey, NIST256p, util
import hashlib
from struct import pack
import translate_key
import numpy
#for AES_CBC lambda pad to 16 bytes by adding the padded value
#(i.e 24 bytes : 0x08 is added  8 times
BS = 16
pad = lambda s: s + (BS - len(s) % BS) * pack("B", 0)

class AES_CBC():
    def __init__(self, key):
        """Construct an AES_CBC private key with the given key data"""
        self.key = key
        self.nonce = []
    @staticmethod
    def generate():
        #use random from platform
        return AES_CBC(os.urandom(16))
    def export_private(self, path):
        if "AES_CBC" not in path:
          print("path does not contains AES_CBC : AES_CBC key should contain AES_CBC string!!!")
          exit(1)
        else:
          with open(path, 'wb') as f:
             f.write(self.key)

    def get_pub_hash(self):           
        # Calculate SHA - 256 hash of the key
        hash_object = hashlib.sha256(self.key)
        hash_bytes = hash_object.digest()
        return bytearray(hash_bytes)

        # get the path file name for hash file
        #hash_file_path = path + ".hash"
        # write public key hash to file
        #with open(hash_file_path, 'wb') as hash_file:
        #    hash_file.write(hash_bytes)

    def encrypt(self, payload, nonce=[]):
        if payload == []:
            print("error")
        #Fix me AES CBC is possibly 12 bytes
        if nonce == []:
            nonce = os.urandom(16)
        m = hashlib.sha256()
        print("block size ="+str(AES.block_size))
        encryptor = AES.new(self.key, AES.MODE_CBC, nonce)
        encrypted = ""
        #check if buffer size is aligned on BS size
        if (0 == (len(payload) % BS)):
          # we do not need to pad
          buffer=payload
          encrypted =  encryptor.encrypt(buffer)
        else:
          # Buffer size is not correct (and we do not support ciphertext stealing mode "CBC-CS2" specified in NIST SP 800-38A any more)
          raise Exception("AES CBC encryption requires the Firmware Image size to be a multiple of the AES block size (16 bytes)")
        #compute sh256 on clear buffer without padding
        m.update(payload)
        signature = m.digest()
        #swap the last two block and truncate if required
        return encrypted,signature, nonce
    def trans(self,section, name, end, assembly, version):
        outcode = translate_key.function(section, name, assembly)
        outcode += translate_key.translate(self.key,end, assembly, version)     
        outcode += translate_key.function(section, name+"_Hash", assembly)
        outcode += translate_key.translate(self.get_pub_hash(), end, assembly, version)    
        return outcode
    def has_nonce(self):
        return True
    def has_sign(self):
        return False
    def has_encrypt(self):
        return True
    def get_key(self, type):
        return self.key

class AES256_CBC():
    def __init__(self, key):
        """Construct an AES_CBC private key with the given key data"""
        self.key = key
        self.nonce = []
    @staticmethod
    def generate():
        #use random from platform
        return AES256_CBC(os.urandom(32))
    def export_private(self, path):
        if "AES256_CBC" not in path:
          print("path does not contains AES256_CBC : AES256_CBC key should contain AES256_CBC string!!!")
          exit(1)
        else:
          with open(path, 'wb') as f:
             f.write(self.key)

    def get_pub_hash(self):
        # Calculate SHA - 384 hash of the key
        hash_object = hashlib.sha384(self.key)
        hash_bytes = hash_object.digest()
        return bytearray(hash_bytes)

        # get the path file name for hash file
        #hash_file_path = path + ".hash"
        # write public key hash to file
        #with open(hash_file_path, 'wb') as hash_file:
        #    hash_file.write(hash_bytes)

    def encrypt(self, payload, nonce=[]):
        if payload == []:
            print("error")
        #Fix me AES CBC is possibly 12 bytes
        if nonce == []:
            nonce = os.urandom(16)
        m = hashlib.sha384()
        print("block size ="+str(AES.block_size))
        encryptor = AES.new(self.key, AES.MODE_CBC, nonce)
        encrypted = ""
        #check if buffer size is aligned on BS size
        if (0 == (len(payload) % BS)):
          # we do not need to pad
          buffer=payload
          encrypted =  encryptor.encrypt(buffer)
        else:
          # Buffer size is not correct (and we do not support ciphertext stealing mode "CBC-CS2" specified in NIST SP 800-38A any more)
          raise Exception("AES CBC encryption requires the Firmware Image size to be a multiple of the AES block size (16 bytes)")
        #compute sh384 on clear buffer without padding
        m.update(payload)
        signature = m.digest()
        #swap the last two block and truncate if required
        return encrypted,signature, nonce
    def trans(self,section, name, end, assembly, version):
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(self.key,end,assembly, version)
        outcode += translate_key.function(section, name+"_Hash",assembly)
        outcode += translate_key.translate(self.get_pub_hash(),end,assembly, version) 
        return outcode
    def has_nonce(self):
        return True
    def has_sign(self):
        return False
    def has_encrypt(self):
        return True
    def get_key(self, type):
        return self.key


class AES_CTR():
    def __init__(self, key):
        """Construct an AES_CTR private key with the given key data"""
        self.key = key
        self.nonce = []
    @staticmethod
    def generate():
        #use random from platform
        return AES_CTR(os.urandom(16))
    def export_private(self, path):
        if "AES_CTR" not in path:
          print("path does not contains AES_CTR : AES_CTR key should contain AES_CTR string!!!")
          exit(1)
        else:
          with open(path, 'wb') as f:
             f.write(self.key)
    def encrypt(self, payload, address, nonce=[]):
        if payload == []:
          print("error")
        m = hashlib.sha256()
        #Swap bytes inside 16 bytes block
        inarr = numpy.asarray(list(payload), numpy.int8).reshape(-1, 16)
        outarr = numpy.fliplr(inarr)
        payload = bytearray(outarr)
        print("block size ="+str(AES.block_size))
        #Encryption
        if nonce == []:
          encryptor = AES.new(self.key, AES.MODE_CTR, initial_value=address);
        else:
          encryptor = AES.new(self.key, AES.MODE_CTR, nonce=nonce, initial_value=address);
        encrypted = ""
        #check if buffer size is aligned on BS size
        if (0 == (len(payload) % BS)):
          # we do not need to pad
          buffer=payload
          encrypted =  encryptor.encrypt(buffer)
          nonce = encryptor.nonce
        else:
          raise Exception("AES CTR encryption requires the Firmware Image size to be a multiple of the AES block size (16 bytes)")
        #Swap bytes inside 16 bytes block
        inarr = numpy.asarray(list(encrypted), numpy.int8).reshape(-1, 16)
        outarr = numpy.fliplr(inarr)
        encrypted = bytearray(outarr)
        #compute sh256 on encrypted buffer without padding
        m.update(encrypted)
        signature = m.digest()
        #swap the last two block and truncate if required
        return encrypted,signature,nonce
    def trans(self,section, name, end, assembly, version):
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(self.key,end,assembly, version)
        return outcode
    def has_nonce(self):
        return True
    def has_sign(self):
        return False
    def has_encrypt(self):
        return True
    def get_key(self, type):
        return self.key

class AES_GCM():
    def __init__(self, key):
        """Construct an AES_GCM private key with the given key data"""
        self.key = key
        self.nonce = []
    @staticmethod
    def generate():
        #use random from platform
        return AES_GCM(os.urandom(16))
    def export_private(self, path):
        if "AES_CBC" in path:
          print("path contains AES_CBC : AES_GCM key should not contain AES_CBC!!!")
          exit(1)
        else:
          with open(path, 'wb') as f:
              f.write(self.key)
    def encrypt(self, payload, nonce=[]):
        if payload == []:
            print("error")

        if nonce == []:
            nonce = os.urandom(12)
        encryptor = AES.new(self.key, AES.MODE_GCM, nonce)
        encrypted = encryptor.encrypt(payload)
        signature = encryptor.digest()
        return encrypted,signature, nonce
    def sign(self,payload, nonce):
        encryptor = AES.new(self.key, AES.MODE_GCM, nonce)
        encryptor.update(payload)
        signature =  encryptor.digest()
        return signature, nonce
    def trans(self,section, name, end, assembly, version):
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(self.key,end,assembly, version)
        return outcode
    def has_nonce(self):
        return True
    def has_sign(self):
        return True
    def has_encrypt(self):
        return True
    def get_key(self, type):
        return self.key


class ECDSA256P1():
    def __init__(self, key):
        """Construct an ECDSA P-256 private key"""
        self.key = key

    @staticmethod
    def generate():
        return ECDSA256P1(SigningKey.generate(curve=NIST256p))

    def export_private(self, path):
        with open(path, 'wb') as f:
            f.write(self.key.to_pem())

    def export_public(self, path):
        public_key = self.key.get_verifying_key()
        with open(path, 'wb') as f:
            f.write(public_key.to_pem())

    def get_pub_hash(self):
        # get the public key
        # public_key = self.key.public_key()
        if isinstance(self.key, SigningKey):    
            public_key = self.key.get_verifying_key()
        elif isinstance(self.key, VerifyingKey):
            public_key = self.key

        # convert the public key to binary format
        public_key_binary = public_key.to_string()
        # comput SHA-384 hash value of the public key
        hash_object = hashlib.sha256(public_key_binary)
        hash_bytes = hash_object.digest()
        return bytearray(hash_bytes)

        # get the path file name for hash file
        #hash_file_path = path + ".hash"
        # write public key hash to file
        #with open(hash_file_path, 'wb') as hash_file:
        #    hash_file.write(hash_bytes)
        # print("Public key value: ")
        # print(public_key_binary.hex())
        # print(f"Public key SHA-256 hash exported to {hash_file_path} successfully.")

    def trans(self,section, name, end, assembly, version):
        if isinstance(self.key, SigningKey):    
            vk = self.key.get_verifying_key()
            binarykey = vk.to_string()
        elif isinstance(self.key, VerifyingKey):
            binarykey = self.key.to_string()
        #generate asm code
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(binarykey,end,assembly, version )
        outcode += translate_key.function(section, name+"_Hash",assembly)
        outcode += translate_key.translate(self.get_pub_hash(),end,assembly, version)         
        return outcode

    def sign(self, payload):
        # To make this fixed length, possibly pad with zeros.
        sig = self.key.sign(payload, hashfunc=hashlib.sha256)
        return sig

    def has_nonce(self):
        return False
    def has_sign(self):
        return True

    def has_encrypt(self):
        return False

    def get_key(self, type):
        if (type == "public"):
            vk = self.key.get_verifying_key()
            return vk.to_string()
        else:
            return self.key.to_pem()

class ECDSA384P1():
    def __init__(self, key):
        """Construct an ECDSA P-384 private key"""
        self.key = key

    @staticmethod
    def generate():
        return ECDSA384P1(SigningKey.generate(curve=NIST384p))

    def export_private(self, path):
        with open(path, 'wb') as f:
            f.write(self.key.to_pem())

    def export_public(self, path):
        public_key = self.key.get_verifying_key()
        with open(path, 'wb') as f:
            f.write(public_key.to_pem())

    def get_pub_hash(self):
        # get the public key
        # public_key = self.key.public_key()
        if isinstance(self.key, SigningKey):    
            public_key = self.key.get_verifying_key()
        elif isinstance(self.key, VerifyingKey):
            public_key = self.key
        
        # convert the public key to binary format
        public_key_binary = public_key.to_string()
        # comput SHA-384 hash value of the public key
        hash_object = hashlib.sha384(public_key_binary)
        hash_bytes = hash_object.digest()
        
        return bytearray(hash_bytes)

        # get the path file name for hash file
        #hash_file_path = path + ".hash"
        # write public key hash to file
        #with open(hash_file_path, 'wb') as hash_file:
        #    hash_file.write(hash_bytes)
        # print("Public key value: ")
        # print(public_key_binary.hex())
        # print(f"Public key SHA-384 hash exported to {hash_file_path} successfully.")

    def trans(self, section, name, end, assembly, version):
        if isinstance(self.key, SigningKey):    
            vk = self.key.get_verifying_key()
            binarykey = vk.to_string()
        elif isinstance(self.key, VerifyingKey):
            binarykey = self.key.to_string()
        #generate asm code
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(binarykey,end,assembly, version )
        outcode += translate_key.function(section, name+"_Hash",assembly)
        outcode += translate_key.translate(self.get_pub_hash(),end,assembly, version)         
        return outcode

    def sign(self, payload):
        # To make this fixed length, possibly pad with zeros.
        sig = self.key.sign(payload, hashfunc=hashlib.sha384)
        return sig

    def has_nonce(self):
        return False
    def has_sign(self):
        return True

    def has_encrypt(self):
        return False

    def get_key(self, type):
        if (type == "public"):
            vk = self.key.get_verifying_key()
            return vk.to_string()
        else:
            return self.key.to_pem()

class PAIRING():
    def __init__(self, key):
        """Construct an PAIRING private key with the given key data"""
        self.key = key
        self.nonce = []
    @staticmethod
    def generate():
        print("Pairing class unsupported !!")
        exit(1)
    def export_private(self, path):
        print("Pairing class unsupported !!")
        exit(1)
    def encrypt(self, payload, nonce=[]):
        print("Pairing class unsupported !!")
        exit(1)
    def sign(self,payload, nonce):
        print("Pairing class unsupported !!")
        exit(1)
    def trans(self,section, name, end, assembly, version):
        outcode = translate_key.function(section, name,assembly)
        outcode += translate_key.translate(self.key,end,assembly, version)
        return outcode
    def has_nonce(self):
        print("Pairing class unsupported !!")
        exit(1)
    def has_sign(self):
        print("Pairing class unsupported !!")
        exit(1)
    def has_encrypt(self):
        print("Pairing class unsupported !!")
        exit(1)
    def get_key(self, type):
        return self.key

def load(path):
    with open(path, 'rb') as f:
        pem = f.read()
    if len(pem) == 16:
        if "AES_CBC" in path:
          return AES_CBC(pem)
        elif "AES_CTR" in path:
          return AES_CTR(pem)
        else:
          return AES_GCM(pem)
    elif len(pem) == 32:
        if "AES256_CBC" in path:
          return AES256_CBC(pem)
        else:
          return PAIRING(pem)
    else:
        try:
            key = SigningKey.from_pem(pem)
        except Exception as e:
            key = VerifyingKey.from_pem(pem)
        if key.curve.name == 'NIST256p':
            return ECDSA256P1(key)
        elif key.curve.name == 'NIST384p':
            return ECDSA384P1(key)
        else:
            raise Exception("Unsupported")


