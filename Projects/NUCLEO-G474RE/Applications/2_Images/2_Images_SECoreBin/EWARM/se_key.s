	section .SE_Key_Data:CODE
	EXPORT SE_ReadKey_1_0
SE_ReadKey_1_0
	PUSH {R1-R5}
	MOVW R1, #0x5c3e
	MOVT R1, #0xa4cd
	MOVW R2, #0xfd28
	MOVT R2, #0xcd5e
	MOVW R3, #0x379e
	MOVT R3, #0x45ea
	MOVW R4, #0x9ebd
	MOVT R4, #0xbb3f
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7800
	MOVT R1, #0x44f8
	MOVW R2, #0xcb48
	MOVT R2, #0x921a
	MOVW R3, #0x431d
	MOVT R3, #0xcac2
	MOVW R4, #0xbdc5
	MOVT R4, #0x799d
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_0_Hash
SE_ReadKey_1_0_Hash
	PUSH {R1-R5}
	MOVW R1, #0xc367
	MOVT R1, #0xa369
	MOVW R2, #0x5607
	MOVT R2, #0x6af2
	MOVW R3, #0xcc6b
	MOVT R3, #0xc9d5
	MOVW R4, #0xcebc
	MOVT R4, #0x7df9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x66ec
	MOVT R1, #0x28b5
	MOVW R2, #0x28a9
	MOVT R2, #0xfd4a
	MOVW R3, #0x606f
	MOVT R3, #0x124b
	MOVW R4, #0x6aa6
	MOVT R4, #0xc2e3
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x18a7
	MOVT R1, #0x9d78
	MOVW R2, #0xfa0e
	MOVT R2, #0x89e0
	MOVW R3, #0xb5a6
	MOVT R3, #0x7bfc
	MOVW R4, #0xa0f
	MOVT R4, #0xb8c8
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_1
SE_ReadKey_1_1
	PUSH {R1-R5}
	MOVW R1, #0xc66e
	MOVT R1, #0xd764
	MOVW R2, #0xab60
	MOVT R2, #0xa8f8
	MOVW R3, #0x86d
	MOVT R3, #0x4b21
	MOVW R4, #0xf015
	MOVT R4, #0xdf61
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xafb9
	MOVT R1, #0x3683
	MOVW R2, #0x547f
	MOVT R2, #0x78f0
	MOVW R3, #0x198c
	MOVT R3, #0x1204
	MOVW R4, #0x7377
	MOVT R4, #0x9e2e
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_1_Hash
SE_ReadKey_1_1_Hash
	PUSH {R1-R5}
	MOVW R1, #0xa6dd
	MOVT R1, #0xcadb
	MOVW R2, #0xf5cc
	MOVT R2, #0xdc85
	MOVW R3, #0x22e8
	MOVT R3, #0xe2de
	MOVW R4, #0x9a6d
	MOVT R4, #0x3056
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe0c6
	MOVT R1, #0x4f7e
	MOVW R2, #0xae73
	MOVT R2, #0x2e56
	MOVW R3, #0xf3af
	MOVT R3, #0xefce
	MOVW R4, #0xb39a
	MOVT R4, #0x96a7
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xef18
	MOVT R1, #0xec5b
	MOVW R2, #0x9ecc
	MOVT R2, #0xb52a
	MOVW R3, #0x7642
	MOVT R3, #0x6b4
	MOVW R4, #0x2a38
	MOVT R4, #0x434e
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_2
SE_ReadKey_1_2
	PUSH {R1-R5}
	MOVW R1, #0x8681
	MOVT R1, #0xe197
	MOVW R2, #0xf789
	MOVT R2, #0x10ce
	MOVW R3, #0x3dc5
	MOVT R3, #0x56b9
	MOVW R4, #0x772
	MOVT R4, #0x1def
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2dc6
	MOVT R1, #0xb9dd
	MOVW R2, #0xeb90
	MOVT R2, #0x61be
	MOVW R3, #0x39ad
	MOVT R3, #0xbcb5
	MOVW R4, #0xf1b9
	MOVT R4, #0x4c31
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_2_Hash
SE_ReadKey_1_2_Hash
	PUSH {R1-R5}
	MOVW R1, #0xb974
	MOVT R1, #0xd460
	MOVW R2, #0x8757
	MOVT R2, #0x3f5b
	MOVW R3, #0x6e51
	MOVT R3, #0xbeb9
	MOVW R4, #0x2831
	MOVT R4, #0x4e3f
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x367b
	MOVT R1, #0xd1e5
	MOVW R2, #0x9bc5
	MOVT R2, #0x901d
	MOVW R3, #0xc83a
	MOVT R3, #0x880d
	MOVW R4, #0x9f09
	MOVT R4, #0xfa61
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3909
	MOVT R1, #0xb151
	MOVW R2, #0xdeb8
	MOVT R2, #0x74ed
	MOVW R3, #0xeb23
	MOVT R3, #0x3ee3
	MOVW R4, #0x436a
	MOVT R4, #0x769
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_3
SE_ReadKey_1_3
	PUSH {R1-R5}
	MOVW R1, #0x232c
	MOVT R1, #0x2203
	MOVW R2, #0x9b2
	MOVT R2, #0x4ec
	MOVW R3, #0x37a5
	MOVT R3, #0x15c7
	MOVW R4, #0xbb59
	MOVT R4, #0xe3ae
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x9d48
	MOVT R1, #0x3130
	MOVW R2, #0xa6ec
	MOVT R2, #0x42fc
	MOVW R3, #0x6b91
	MOVT R3, #0x414e
	MOVW R4, #0x66b3
	MOVT R4, #0x951b
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_3_Hash
SE_ReadKey_1_3_Hash
	PUSH {R1-R5}
	MOVW R1, #0x7c77
	MOVT R1, #0xc41
	MOVW R2, #0x7bff
	MOVT R2, #0x85b9
	MOVW R3, #0x88a6
	MOVT R3, #0xd88d
	MOVW R4, #0x93ca
	MOVT R4, #0x39de
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x74fc
	MOVT R1, #0x3f5
	MOVW R2, #0xa439
	MOVT R2, #0x5493
	MOVW R3, #0x966c
	MOVT R3, #0xfca6
	MOVW R4, #0x2850
	MOVT R4, #0x3928
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe8bf
	MOVT R1, #0xd9f0
	MOVW R2, #0xfac7
	MOVT R2, #0x9aa9
	MOVW R3, #0xda25
	MOVT R3, #0x786a
	MOVW R4, #0x867b
	MOVT R4, #0x28c1
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_4
SE_ReadKey_1_4
	PUSH {R1-R5}
	MOVW R1, #0x5058
	MOVT R1, #0x7fdf
	MOVW R2, #0xa3df
	MOVT R2, #0x38c6
	MOVW R3, #0xf17a
	MOVT R3, #0x8f47
	MOVW R4, #0x266
	MOVT R4, #0x4b27
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe481
	MOVT R1, #0x3e4d
	MOVW R2, #0x5ebd
	MOVT R2, #0xce9e
	MOVW R3, #0xf0cc
	MOVT R3, #0xc4d3
	MOVW R4, #0x4cfe
	MOVT R4, #0xd9db
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_4_Hash
SE_ReadKey_1_4_Hash
	PUSH {R1-R5}
	MOVW R1, #0x1f47
	MOVT R1, #0x259d
	MOVW R2, #0xdb61
	MOVT R2, #0xc413
	MOVW R3, #0x3616
	MOVT R3, #0x73cd
	MOVW R4, #0x5813
	MOVT R4, #0x75f5
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xb547
	MOVT R1, #0x7a0e
	MOVW R2, #0xc8a7
	MOVT R2, #0x3d64
	MOVW R3, #0x6110
	MOVT R3, #0xd7ec
	MOVW R4, #0xd77c
	MOVT R4, #0xa3a4
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xa9b7
	MOVT R1, #0xd0cf
	MOVW R2, #0x74e7
	MOVT R2, #0xe6d5
	MOVW R3, #0x2e
	MOVT R3, #0xb28e
	MOVW R4, #0xc752
	MOVT R4, #0xb338
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_5
SE_ReadKey_1_5
	PUSH {R1-R5}
	MOVW R1, #0x85e
	MOVT R1, #0x3d65
	MOVW R2, #0x721e
	MOVT R2, #0x2430
	MOVW R3, #0xebf0
	MOVT R3, #0x38b5
	MOVW R4, #0x9805
	MOVT R4, #0xfd11
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7263
	MOVT R1, #0x659f
	MOVW R2, #0xae74
	MOVT R2, #0x73d4
	MOVW R3, #0x2e11
	MOVT R3, #0x177
	MOVW R4, #0xedb2
	MOVT R4, #0x55a4
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_5_Hash
SE_ReadKey_1_5_Hash
	PUSH {R1-R5}
	MOVW R1, #0x52fe
	MOVT R1, #0x85b7
	MOVW R2, #0xc54e
	MOVT R2, #0x72b7
	MOVW R3, #0x1d14
	MOVT R3, #0x2747
	MOVW R4, #0x47cc
	MOVT R4, #0x7163
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6ca1
	MOVT R1, #0x53af
	MOVW R2, #0xdc77
	MOVT R2, #0x35c7
	MOVW R3, #0xd004
	MOVT R3, #0x42f5
	MOVW R4, #0xf2ac
	MOVT R4, #0x2e1
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x18b1
	MOVT R1, #0xc816
	MOVW R2, #0x4265
	MOVT R2, #0x593d
	MOVW R3, #0xd07a
	MOVT R3, #0x7997
	MOVW R4, #0x2fe7
	MOVT R4, #0x10c0
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_6
SE_ReadKey_1_6
	PUSH {R1-R5}
	MOVW R1, #0x2c41
	MOVT R1, #0x4340
	MOVW R2, #0xc8c
	MOVT R2, #0x2b2e
	MOVW R3, #0x74ae
	MOVT R3, #0x757f
	MOVW R4, #0xf56
	MOVT R4, #0x9d1b
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7a6a
	MOVT R1, #0xe5c3
	MOVW R2, #0xe6ac
	MOVT R2, #0xa6ee
	MOVW R3, #0xe871
	MOVT R3, #0x5f5e
	MOVW R4, #0x231d
	MOVT R4, #0xf1b
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_6_Hash
SE_ReadKey_1_6_Hash
	PUSH {R1-R5}
	MOVW R1, #0x8c4
	MOVT R1, #0x9da2
	MOVW R2, #0x6c03
	MOVT R2, #0x5d73
	MOVW R3, #0x3b7d
	MOVT R3, #0xd853
	MOVW R4, #0x4ef5
	MOVT R4, #0xe339
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x976b
	MOVT R1, #0x369b
	MOVW R2, #0x884b
	MOVT R2, #0xf900
	MOVW R3, #0x6239
	MOVT R3, #0x483e
	MOVW R4, #0xd8fe
	MOVT R4, #0xba3c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc5bc
	MOVT R1, #0x3b08
	MOVW R2, #0xc218
	MOVT R2, #0xee58
	MOVW R3, #0x830d
	MOVT R3, #0x54e1
	MOVW R4, #0xcbd8
	MOVT R4, #0x47b6
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_7
SE_ReadKey_1_7
	PUSH {R1-R5}
	MOVW R1, #0xbaff
	MOVT R1, #0x9f14
	MOVW R2, #0xa9f2
	MOVT R2, #0xdb21
	MOVW R3, #0xa39a
	MOVT R3, #0x4065
	MOVW R4, #0xeadc
	MOVT R4, #0x3e43
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xed2d
	MOVT R1, #0x2dd
	MOVW R2, #0x6ddc
	MOVT R2, #0x6dc1
	MOVW R3, #0x2f61
	MOVT R3, #0x2cd1
	MOVW R4, #0x205f
	MOVT R4, #0xafda
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_7_Hash
SE_ReadKey_1_7_Hash
	PUSH {R1-R5}
	MOVW R1, #0x2097
	MOVT R1, #0x7878
	MOVW R2, #0x4fce
	MOVT R2, #0x573e
	MOVW R3, #0xdaef
	MOVT R3, #0x906b
	MOVW R4, #0xe12f
	MOVT R4, #0x825d
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xfbf1
	MOVT R1, #0x403e
	MOVW R2, #0x8b07
	MOVT R2, #0x9329
	MOVW R3, #0x3fc9
	MOVT R3, #0xbb42
	MOVW R4, #0x19ca
	MOVT R4, #0xf830
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x83c1
	MOVT R1, #0xbf2
	MOVW R2, #0x989
	MOVT R2, #0x3d70
	MOVW R3, #0x7a04
	MOVT R3, #0xcfc5
	MOVW R4, #0xf461
	MOVT R4, #0x4be7
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_0
SE_ReadKey_1_Pub_0
	PUSH {R1-R5}
	MOVW R1, #0x57cd
	MOVT R1, #0xcaac
	MOVW R2, #0x2af7
	MOVT R2, #0x115a
	MOVW R3, #0xae4b
	MOVT R3, #0xa754
	MOVW R4, #0x6ce3
	MOVT R4, #0x65d2
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8e2e
	MOVT R1, #0x16bb
	MOVW R2, #0x9a1e
	MOVT R2, #0x2150
	MOVW R3, #0xc07
	MOVT R3, #0x6ee4
	MOVW R4, #0x28c0
	MOVT R4, #0x2ae8
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3ddd
	MOVT R1, #0x8b0c
	MOVW R2, #0x9dea
	MOVT R2, #0xbc76
	MOVW R3, #0x7d21
	MOVT R3, #0xaea0
	MOVW R4, #0x6ad7
	MOVT R4, #0x84e9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x36e6
	MOVT R1, #0xba03
	MOVW R2, #0xb541
	MOVT R2, #0x3aa6
	MOVW R3, #0xdf7e
	MOVT R3, #0xe985
	MOVW R4, #0x6398
	MOVT R4, #0x7d62
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2399
	MOVT R1, #0xdfc5
	MOVW R2, #0xbafd
	MOVT R2, #0x9a3
	MOVW R3, #0xaf75
	MOVT R3, #0xa344
	MOVW R4, #0xbca4
	MOVT R4, #0xe718
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4a42
	MOVT R1, #0x365e
	MOVW R2, #0xb910
	MOVT R2, #0x80b1
	MOVW R3, #0x4f53
	MOVT R3, #0x8d23
	MOVW R4, #0x1da3
	MOVT R4, #0xd1bf
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_0_Hash
SE_ReadKey_1_Pub_0_Hash
	PUSH {R1-R5}
	MOVW R1, #0x4d7c
	MOVT R1, #0x7df8
	MOVW R2, #0x650f
	MOVT R2, #0x8611
	MOVW R3, #0x42f6
	MOVT R3, #0x6e6c
	MOVW R4, #0xd528
	MOVT R4, #0x891d
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3071
	MOVT R1, #0x3b6c
	MOVW R2, #0x34da
	MOVT R2, #0x8e53
	MOVW R3, #0xdff8
	MOVT R3, #0x29d3
	MOVW R4, #0x7a38
	MOVT R4, #0x3694
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xf970
	MOVT R1, #0x4025
	MOVW R2, #0xa5ed
	MOVT R2, #0xa288
	MOVW R3, #0xf214
	MOVT R3, #0x1731
	MOVW R4, #0x25ff
	MOVT R4, #0xaf84
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_1
SE_ReadKey_1_Pub_1
	PUSH {R1-R5}
	MOVW R1, #0xafe3
	MOVT R1, #0x7659
	MOVW R2, #0xf6b
	MOVT R2, #0x193c
	MOVW R3, #0xde0e
	MOVT R3, #0x4612
	MOVW R4, #0xf701
	MOVT R4, #0xe5d9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3f6e
	MOVT R1, #0x6126
	MOVW R2, #0xf796
	MOVT R2, #0xf3b2
	MOVW R3, #0x8d06
	MOVT R3, #0x8542
	MOVW R4, #0x171a
	MOVT R4, #0x98f0
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7855
	MOVT R1, #0xf536
	MOVW R2, #0x229
	MOVT R2, #0x9fa3
	MOVW R3, #0xc82a
	MOVT R3, #0xa9b1
	MOVW R4, #0x7767
	MOVT R4, #0xb80b
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbb2d
	MOVT R1, #0xf9d1
	MOVW R2, #0xd141
	MOVT R2, #0x1ce0
	MOVW R3, #0x167c
	MOVT R3, #0x519d
	MOVW R4, #0xed23
	MOVT R4, #0xae9a
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xa750
	MOVT R1, #0xf839
	MOVW R2, #0xd79d
	MOVT R2, #0xa8e8
	MOVW R3, #0xd3ce
	MOVT R3, #0x5de
	MOVW R4, #0x85ab
	MOVT R4, #0xc99e
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x708f
	MOVT R1, #0xceb3
	MOVW R2, #0xe68
	MOVT R2, #0x241f
	MOVW R3, #0x6fbd
	MOVT R3, #0xe193
	MOVW R4, #0x3caa
	MOVT R4, #0xa33a
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_1_Hash
SE_ReadKey_1_Pub_1_Hash
	PUSH {R1-R5}
	MOVW R1, #0x9cdf
	MOVT R1, #0xb73e
	MOVW R2, #0x8745
	MOVT R2, #0xcb5f
	MOVW R3, #0xda81
	MOVT R3, #0x969a
	MOVW R4, #0x9ca5
	MOVT R4, #0x8d88
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xb837
	MOVT R1, #0x2029
	MOVW R2, #0xab8a
	MOVT R2, #0x3f62
	MOVW R3, #0xfa30
	MOVT R3, #0xcf7b
	MOVW R4, #0x4056
	MOVT R4, #0x535
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe63a
	MOVT R1, #0xf54c
	MOVW R2, #0x70f8
	MOVT R2, #0xfd35
	MOVW R3, #0x91fa
	MOVT R3, #0x43eb
	MOVW R4, #0x9672
	MOVT R4, #0xb5e3
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_2
SE_ReadKey_1_Pub_2
	PUSH {R1-R5}
	MOVW R1, #0x2779
	MOVT R1, #0xa7a3
	MOVW R2, #0xce5a
	MOVT R2, #0x41dc
	MOVW R3, #0xd9f1
	MOVT R3, #0xec97
	MOVW R4, #0xf0a
	MOVT R4, #0xd2b4
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6240
	MOVT R1, #0x75a1
	MOVW R2, #0x29f8
	MOVT R2, #0x210e
	MOVW R3, #0xf769
	MOVT R3, #0x3c5b
	MOVW R4, #0xddc9
	MOVT R4, #0x7224
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xa3c3
	MOVT R1, #0x2f2c
	MOVW R2, #0x68a8
	MOVT R2, #0x9f28
	MOVW R3, #0x840e
	MOVT R3, #0x6941
	MOVW R4, #0xec7b
	MOVT R4, #0xf8b0
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x32a0
	MOVT R1, #0x50de
	MOVW R2, #0x52b9
	MOVT R2, #0x3923
	MOVW R3, #0x2e1a
	MOVT R3, #0x2a5e
	MOVW R4, #0x2756
	MOVT R4, #0x9b2b
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x38ad
	MOVT R1, #0x397c
	MOVW R2, #0xfed0
	MOVT R2, #0xd72b
	MOVW R3, #0xdd8d
	MOVT R3, #0x893d
	MOVW R4, #0xe54e
	MOVT R4, #0x3faf
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe948
	MOVT R1, #0xb2b4
	MOVW R2, #0x8fa8
	MOVT R2, #0x7b32
	MOVW R3, #0xf75b
	MOVT R3, #0x3060
	MOVW R4, #0x6ae6
	MOVT R4, #0xe088
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_2_Hash
SE_ReadKey_1_Pub_2_Hash
	PUSH {R1-R5}
	MOVW R1, #0xe1d8
	MOVT R1, #0x85e6
	MOVW R2, #0x419c
	MOVT R2, #0xec99
	MOVW R3, #0xe455
	MOVT R3, #0x247
	MOVW R4, #0x566d
	MOVT R4, #0x73a5
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8c71
	MOVT R1, #0x49c0
	MOVW R2, #0x449a
	MOVT R2, #0x4214
	MOVW R3, #0x1870
	MOVT R3, #0x739d
	MOVW R4, #0x477c
	MOVT R4, #0x1198
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x54d3
	MOVT R1, #0x99d7
	MOVW R2, #0x6e9f
	MOVT R2, #0xb4f2
	MOVW R3, #0x79bd
	MOVT R3, #0xce31
	MOVW R4, #0x3e31
	MOVT R4, #0xa7a0
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_3
SE_ReadKey_1_Pub_3
	PUSH {R1-R5}
	MOVW R1, #0xc602
	MOVT R1, #0xa5b6
	MOVW R2, #0x1329
	MOVT R2, #0xd9be
	MOVW R3, #0x2c2d
	MOVT R3, #0x54c6
	MOVW R4, #0xcaea
	MOVT R4, #0xe911
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x669b
	MOVT R1, #0x9f71
	MOVW R2, #0x43a9
	MOVT R2, #0x6ce7
	MOVW R3, #0x2eb5
	MOVT R3, #0x7b9
	MOVW R4, #0x4f63
	MOVT R4, #0xbd96
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x71c8
	MOVT R1, #0x3f99
	MOVW R2, #0x2200
	MOVT R2, #0x8be4
	MOVW R3, #0x8470
	MOVT R3, #0x4e3a
	MOVW R4, #0xd0bc
	MOVT R4, #0xefab
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x5b55
	MOVT R1, #0x7b51
	MOVW R2, #0x986f
	MOVT R2, #0x7bfc
	MOVW R3, #0xd2f8
	MOVT R3, #0xc5d5
	MOVW R4, #0x1d72
	MOVT R4, #0x6223
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xfaba
	MOVT R1, #0xfbe5
	MOVW R2, #0xb274
	MOVT R2, #0xf1ca
	MOVW R3, #0xf0ea
	MOVT R3, #0x5c76
	MOVW R4, #0xd9a8
	MOVT R4, #0x385
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbfc8
	MOVT R1, #0xdfb5
	MOVW R2, #0xa509
	MOVT R2, #0xff78
	MOVW R3, #0xeb67
	MOVT R3, #0xaa48
	MOVW R4, #0xa195
	MOVT R4, #0xca00
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_3_Hash
SE_ReadKey_1_Pub_3_Hash
	PUSH {R1-R5}
	MOVW R1, #0x4dba
	MOVT R1, #0x2180
	MOVW R2, #0xe015
	MOVT R2, #0xe216
	MOVW R3, #0xb819
	MOVT R3, #0x95a6
	MOVW R4, #0x9606
	MOVT R4, #0xb872
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1068
	MOVT R1, #0x3532
	MOVW R2, #0x2d96
	MOVT R2, #0xbf7e
	MOVW R3, #0xa381
	MOVT R3, #0xafe4
	MOVW R4, #0x4c30
	MOVT R4, #0x6082
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xda1d
	MOVT R1, #0x5abe
	MOVW R2, #0x4094
	MOVT R2, #0xfc0c
	MOVW R3, #0xab5
	MOVT R3, #0xcf7f
	MOVW R4, #0xa0fa
	MOVT R4, #0xe264
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_4
SE_ReadKey_1_Pub_4
	PUSH {R1-R5}
	MOVW R1, #0xd5c6
	MOVT R1, #0x2e40
	MOVW R2, #0x6f90
	MOVT R2, #0x6455
	MOVW R3, #0xc95
	MOVT R3, #0x3622
	MOVW R4, #0x3810
	MOVT R4, #0xd039
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7b53
	MOVT R1, #0xf605
	MOVW R2, #0x5d8e
	MOVT R2, #0xed3b
	MOVW R3, #0x84e3
	MOVT R3, #0x6194
	MOVW R4, #0xdab8
	MOVT R4, #0xa9f9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8d61
	MOVT R1, #0xbf12
	MOVW R2, #0x616a
	MOVT R2, #0x4a1a
	MOVW R3, #0x3416
	MOVT R3, #0xffda
	MOVW R4, #0x9bc3
	MOVT R4, #0xcfad
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3fd9
	MOVT R1, #0x8e26
	MOVW R2, #0xc648
	MOVT R2, #0x20ad
	MOVW R3, #0x56dc
	MOVT R3, #0x2f42
	MOVW R4, #0x31ee
	MOVT R4, #0xd57c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1e97
	MOVT R1, #0x4722
	MOVW R2, #0x85bf
	MOVT R2, #0x46a6
	MOVW R3, #0xb9a6
	MOVT R3, #0xb997
	MOVW R4, #0x7691
	MOVT R4, #0x2539
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x511
	MOVT R1, #0xcd45
	MOVW R2, #0x2b1e
	MOVT R2, #0x22e2
	MOVW R3, #0x954d
	MOVT R3, #0xc63b
	MOVW R4, #0xc9b
	MOVT R4, #0xbbe1
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_4_Hash
SE_ReadKey_1_Pub_4_Hash
	PUSH {R1-R5}
	MOVW R1, #0xdc27
	MOVT R1, #0x51e5
	MOVW R2, #0xf1e4
	MOVT R2, #0xcec6
	MOVW R3, #0xf9a
	MOVT R3, #0x34b9
	MOVW R4, #0x408e
	MOVT R4, #0x4de2
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xf53f
	MOVT R1, #0xc4dc
	MOVW R2, #0xf96d
	MOVT R2, #0x6df
	MOVW R3, #0x33d
	MOVT R3, #0x8daa
	MOVW R4, #0x94ed
	MOVT R4, #0x656f
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x7a2d
	MOVT R1, #0x2b08
	MOVW R2, #0xfdf5
	MOVT R2, #0x9cd0
	MOVW R3, #0xd346
	MOVT R3, #0x31bd
	MOVW R4, #0x6f3d
	MOVT R4, #0x37c2
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_5
SE_ReadKey_1_Pub_5
	PUSH {R1-R5}
	MOVW R1, #0xfe61
	MOVT R1, #0xf0e5
	MOVW R2, #0xab76
	MOVT R2, #0x66dd
	MOVW R3, #0xc893
	MOVT R3, #0xc2c1
	MOVW R4, #0x70a2
	MOVT R4, #0x186e
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc14a
	MOVT R1, #0xb41d
	MOVW R2, #0x1942
	MOVT R2, #0x8e3a
	MOVW R3, #0xbb61
	MOVT R3, #0x9ed0
	MOVW R4, #0x3ab9
	MOVT R4, #0xa82c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xd320
	MOVT R1, #0x9f62
	MOVW R2, #0x500e
	MOVT R2, #0x39c4
	MOVW R3, #0x6192
	MOVT R3, #0xc248
	MOVW R4, #0x24a3
	MOVT R4, #0xded0
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xac41
	MOVT R1, #0xc21d
	MOVW R2, #0xc56f
	MOVT R2, #0x910f
	MOVW R3, #0x89bf
	MOVT R3, #0xc4a7
	MOVW R4, #0xd75c
	MOVT R4, #0xbf4
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x186a
	MOVT R1, #0x37c5
	MOVW R2, #0x2c5d
	MOVT R2, #0xfcea
	MOVW R3, #0x523c
	MOVT R3, #0x62dc
	MOVW R4, #0xd9f8
	MOVT R4, #0xd4ad
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1ee3
	MOVT R1, #0x8d91
	MOVW R2, #0x6401
	MOVT R2, #0x953f
	MOVW R3, #0xce5e
	MOVT R3, #0xb7ad
	MOVW R4, #0x4aa1
	MOVT R4, #0x255
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_5_Hash
SE_ReadKey_1_Pub_5_Hash
	PUSH {R1-R5}
	MOVW R1, #0xfa62
	MOVT R1, #0xf5
	MOVW R2, #0x6da1
	MOVT R2, #0x98c0
	MOVW R3, #0x53eb
	MOVT R3, #0xe495
	MOVW R4, #0xbaa4
	MOVT R4, #0xfe4c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2807
	MOVT R1, #0xaefb
	MOVW R2, #0x6360
	MOVT R2, #0x3d40
	MOVW R3, #0x43bc
	MOVT R3, #0x51f0
	MOVW R4, #0xa51e
	MOVT R4, #0xfe54
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x21ab
	MOVT R1, #0xc1fd
	MOVW R2, #0xbe1a
	MOVT R2, #0x4e4c
	MOVW R3, #0xa363
	MOVT R3, #0xd806
	MOVW R4, #0x5fcf
	MOVT R4, #0x27e3
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_6
SE_ReadKey_1_Pub_6
	PUSH {R1-R5}
	MOVW R1, #0x2eff
	MOVT R1, #0x7591
	MOVW R2, #0x90d5
	MOVT R2, #0x3832
	MOVW R3, #0x9d18
	MOVT R3, #0xdf6f
	MOVW R4, #0x9590
	MOVT R4, #0x8895
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc814
	MOVT R1, #0xbf2f
	MOVW R2, #0x4944
	MOVT R2, #0xa2e6
	MOVW R3, #0xb7e7
	MOVT R3, #0x5ca4
	MOVW R4, #0x5f22
	MOVT R4, #0x5d6b
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc2c6
	MOVT R1, #0x9a7
	MOVW R2, #0xa2ee
	MOVT R2, #0x1036
	MOVW R3, #0x7737
	MOVT R3, #0xf37
	MOVW R4, #0xa26a
	MOVT R4, #0x3400
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8ad5
	MOVT R1, #0x7148
	MOVW R2, #0x4c31
	MOVT R2, #0x6930
	MOVW R3, #0x9084
	MOVT R3, #0x2a4c
	MOVW R4, #0x8eb
	MOVT R4, #0x79df
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe6bd
	MOVT R1, #0xc160
	MOVW R2, #0x7ebb
	MOVT R2, #0x56a1
	MOVW R3, #0x4c62
	MOVT R3, #0x5bc
	MOVW R4, #0x947e
	MOVT R4, #0xf803
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3354
	MOVT R1, #0xda26
	MOVW R2, #0x1c14
	MOVT R2, #0x64c0
	MOVW R3, #0x9d17
	MOVT R3, #0x6035
	MOVW R4, #0x1bf7
	MOVT R4, #0x6ec9
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_6_Hash
SE_ReadKey_1_Pub_6_Hash
	PUSH {R1-R5}
	MOVW R1, #0x1732
	MOVT R1, #0xefa2
	MOVW R2, #0x8ca9
	MOVT R2, #0x3a02
	MOVW R3, #0x1709
	MOVT R3, #0x1ff1
	MOVW R4, #0x98bc
	MOVT R4, #0xc4f1
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6d51
	MOVT R1, #0xe3dc
	MOVW R2, #0x75b3
	MOVT R2, #0x3ad9
	MOVW R3, #0x28df
	MOVT R3, #0xfe00
	MOVW R4, #0x3b05
	MOVT R4, #0xc365
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x25b2
	MOVT R1, #0xafd0
	MOVW R2, #0x63aa
	MOVT R2, #0x43c9
	MOVW R3, #0x2533
	MOVT R3, #0x29c8
	MOVW R4, #0x43bb
	MOVT R4, #0x923e
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	EXPORT SE_ReadKey_1_Pub_7
SE_ReadKey_1_Pub_7
	PUSH {R1-R5}
	MOVW R1, #0x8a2
	MOVT R1, #0xca8b
	MOVW R2, #0x41e7
	MOVT R2, #0xffa9
	MOVW R3, #0xac44
	MOVT R3, #0xe8a6
	MOVW R4, #0x2f49
	MOVT R4, #0x56c5
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4255
	MOVT R1, #0x51d3
	MOVW R2, #0xd2b4
	MOVT R2, #0x8c90
	MOVW R3, #0x45d
	MOVT R3, #0xd56d
	MOVW R4, #0x15a0
	MOVT R4, #0x7068
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2cce
	MOVT R1, #0x33c1
	MOVW R2, #0x613a
	MOVT R2, #0x6adc
	MOVW R3, #0x2c87
	MOVT R3, #0x8194
	MOVW R4, #0x418d
	MOVT R4, #0x16d0
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6257
	MOVT R1, #0x2f83
	MOVW R2, #0x8c74
	MOVT R2, #0x32ba
	MOVW R3, #0x365d
	MOVT R3, #0xdd39
	MOVW R4, #0x4065
	MOVT R4, #0xf693
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x49a9
	MOVT R1, #0xaa89
	MOVW R2, #0x706e
	MOVT R2, #0xb2b3
	MOVW R3, #0xab58
	MOVT R3, #0x9904
	MOVW R4, #0x768f
	MOVT R4, #0xed60
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6352
	MOVT R1, #0xc1c0
	MOVW R2, #0xbd74
	MOVT R2, #0x2bb5
	MOVW R3, #0x2772
	MOVT R3, #0xc8c5
	MOVW R4, #0xcaab
	MOVT R4, #0xaa66
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	EXPORT SE_ReadKey_1_Pub_7_Hash
SE_ReadKey_1_Pub_7_Hash
	PUSH {R1-R5}
	MOVW R1, #0x9d51
	MOVT R1, #0xc526
	MOVW R2, #0xe189
	MOVT R2, #0x770c
	MOVW R3, #0xb1e7
	MOVT R3, #0x75df
	MOVW R4, #0x1f51
	MOVT R4, #0xdd30
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x96ae
	MOVT R1, #0xf08
	MOVW R2, #0xba7b
	MOVT R2, #0xb4c8
	MOVW R3, #0x6f05
	MOVT R3, #0xbb40
	MOVW R4, #0xd932
	MOVT R4, #0xb8ad
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x29f4
	MOVT R1, #0x8c92
	MOVW R2, #0xad38
	MOVT R2, #0xc7e1
	MOVW R3, #0x4cb2
	MOVT R3, #0xff52
	MOVW R4, #0xca11
	MOVT R4, #0x3323
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

    END 
