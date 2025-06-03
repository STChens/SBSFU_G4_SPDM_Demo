	.section .SE_Key_Data,"a",%progbits
	.syntax unified
	.thumb 
	.global SE_ReadKey_1_0
SE_ReadKey_1_0:
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
	.global SE_ReadKey_1_0_Hash
SE_ReadKey_1_0_Hash:
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

	.global SE_ReadKey_1_1
SE_ReadKey_1_1:
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
	.global SE_ReadKey_1_1_Hash
SE_ReadKey_1_1_Hash:
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

	.global SE_ReadKey_1_2
SE_ReadKey_1_2:
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
	.global SE_ReadKey_1_2_Hash
SE_ReadKey_1_2_Hash:
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

	.global SE_ReadKey_1_3
SE_ReadKey_1_3:
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
	.global SE_ReadKey_1_3_Hash
SE_ReadKey_1_3_Hash:
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

	.global SE_ReadKey_1_4
SE_ReadKey_1_4:
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
	.global SE_ReadKey_1_4_Hash
SE_ReadKey_1_4_Hash:
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

	.global SE_ReadKey_1_5
SE_ReadKey_1_5:
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
	.global SE_ReadKey_1_5_Hash
SE_ReadKey_1_5_Hash:
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

	.global SE_ReadKey_1_6
SE_ReadKey_1_6:
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
	.global SE_ReadKey_1_6_Hash
SE_ReadKey_1_6_Hash:
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

	.global SE_ReadKey_1_7
SE_ReadKey_1_7:
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
	.global SE_ReadKey_1_7_Hash
SE_ReadKey_1_7_Hash:
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

	.global SE_ReadKey_1_Pub_0
SE_ReadKey_1_Pub_0:
	PUSH {R1-R5}
	MOVW R1, #0x67b5
	MOVT R1, #0x8861
	MOVW R2, #0x91eb
	MOVT R2, #0x3524
	MOVW R3, #0x81e3
	MOVT R3, #0xce4a
	MOVW R4, #0x7583
	MOVT R4, #0x3948
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbc1c
	MOVT R1, #0x7b6b
	MOVW R2, #0x9a48
	MOVT R2, #0x3faa
	MOVW R3, #0x1efc
	MOVT R3, #0x6f14
	MOVW R4, #0xd0ff
	MOVT R4, #0x84d2
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8749
	MOVT R1, #0xc250
	MOVW R2, #0x7c1a
	MOVT R2, #0xc69f
	MOVW R3, #0xb395
	MOVT R3, #0xffe5
	MOVW R4, #0x1127
	MOVT R4, #0xcde8
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xb35d
	MOVT R1, #0x74d7
	MOVW R2, #0xb5e1
	MOVT R2, #0xcb6e
	MOVW R3, #0x9d21
	MOVT R3, #0x878c
	MOVW R4, #0xe174
	MOVT R4, #0xa5a9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x344f
	MOVT R1, #0x75ef
	MOVW R2, #0x9d1a
	MOVT R2, #0xc5a2
	MOVW R3, #0x498f
	MOVT R3, #0x37c1
	MOVW R4, #0xcb7b
	MOVT R4, #0x6c26
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xdfef
	MOVT R1, #0x2658
	MOVW R2, #0x835c
	MOVT R2, #0x2888
	MOVW R3, #0x8fd8
	MOVT R3, #0x6bd5
	MOVW R4, #0x2957
	MOVT R4, #0xff9b
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_0_Hash
SE_ReadKey_1_Pub_0_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x5fc7
	MOVT R1, #0xa6bb
	MOVW R2, #0x44dd
	MOVT R2, #0xe8bb
	MOVW R3, #0xf4df
	MOVT R3, #0x32bf
	MOVW R4, #0x840d
	MOVT R4, #0xd1ec
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6506
	MOVT R1, #0x7b2e
	MOVW R2, #0x35cb
	MOVT R2, #0xb910
	MOVW R3, #0x8531
	MOVT R3, #0xe7d6
	MOVW R4, #0xfc82
	MOVT R4, #0x6501
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4927
	MOVT R1, #0x73d
	MOVW R2, #0x1adf
	MOVT R2, #0x75f4
	MOVW R3, #0x3817
	MOVT R3, #0x10b4
	MOVW R4, #0x13d1
	MOVT R4, #0x9fcb
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_1
SE_ReadKey_1_Pub_1:
	PUSH {R1-R5}
	MOVW R1, #0x49c7
	MOVT R1, #0xe3c7
	MOVW R2, #0x7832
	MOVT R2, #0x99fc
	MOVW R3, #0xcf2a
	MOVT R3, #0xd89b
	MOVW R4, #0x9135
	MOVT R4, #0xc678
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xfbcf
	MOVT R1, #0xb14e
	MOVW R2, #0xf349
	MOVT R2, #0xe6a0
	MOVW R3, #0x537
	MOVT R3, #0x90c9
	MOVW R4, #0x9770
	MOVT R4, #0xbc33
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xddcd
	MOVT R1, #0x2a7b
	MOVW R2, #0x4436
	MOVT R2, #0x5806
	MOVW R3, #0xcfb2
	MOVT R3, #0xe517
	MOVW R4, #0x3ae1
	MOVT R4, #0xab2e
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1af0
	MOVT R1, #0xa139
	MOVW R2, #0xee1d
	MOVT R2, #0x3ae8
	MOVW R3, #0x6a34
	MOVT R3, #0xa8b9
	MOVW R4, #0xd708
	MOVT R4, #0xc37f
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x26d9
	MOVT R1, #0xed02
	MOVW R2, #0x74bb
	MOVT R2, #0x2c58
	MOVW R3, #0xf14f
	MOVT R3, #0x1cb5
	MOVW R4, #0x9557
	MOVT R4, #0x5331
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2985
	MOVT R1, #0x7abe
	MOVW R2, #0x4527
	MOVT R2, #0xb0e8
	MOVW R3, #0xfa
	MOVT R3, #0x2582
	MOVW R4, #0xc023
	MOVT R4, #0x95b0
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_1_Hash
SE_ReadKey_1_Pub_1_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x4940
	MOVT R1, #0xfe3f
	MOVW R2, #0x34bc
	MOVT R2, #0x4129
	MOVW R3, #0x16d1
	MOVT R3, #0x3c40
	MOVW R4, #0x8137
	MOVT R4, #0x2f78
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x286b
	MOVT R1, #0xb85b
	MOVW R2, #0x5109
	MOVT R2, #0x5107
	MOVW R3, #0xed8f
	MOVT R3, #0x148d
	MOVW R4, #0x2f05
	MOVT R4, #0x1c2
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xf1d7
	MOVT R1, #0x2303
	MOVW R2, #0xbe49
	MOVT R2, #0x190e
	MOVW R3, #0x9d52
	MOVT R3, #0x901d
	MOVW R4, #0x7ed3
	MOVT R4, #0x307e
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_2
SE_ReadKey_1_Pub_2:
	PUSH {R1-R5}
	MOVW R1, #0xd98f
	MOVT R1, #0xd8d4
	MOVW R2, #0xa0bb
	MOVT R2, #0x6cfa
	MOVW R3, #0x1c2
	MOVT R3, #0x48b7
	MOVW R4, #0x5e3d
	MOVT R4, #0x3b8c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x776c
	MOVT R1, #0xd61f
	MOVW R2, #0x8f69
	MOVT R2, #0x66c3
	MOVW R3, #0x96a8
	MOVT R3, #0xc98d
	MOVW R4, #0x3e97
	MOVT R4, #0x6e50
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x58e4
	MOVT R1, #0xf7fc
	MOVW R2, #0x8fb7
	MOVT R2, #0x8f72
	MOVW R3, #0xc2c8
	MOVT R3, #0xcf8e
	MOVW R4, #0x5d1a
	MOVT R4, #0x16de
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xb69e
	MOVT R1, #0x372b
	MOVW R2, #0xc31f
	MOVT R2, #0x64e0
	MOVW R3, #0x1c2c
	MOVT R3, #0x9277
	MOVW R4, #0xfe91
	MOVT R4, #0x958c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xd7c4
	MOVT R1, #0x3d00
	MOVW R2, #0xc5e3
	MOVT R2, #0x9580
	MOVW R3, #0xcc81
	MOVT R3, #0x9912
	MOVW R4, #0xd6f0
	MOVT R4, #0x12fe
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4430
	MOVT R1, #0xc6d4
	MOVW R2, #0xd575
	MOVT R2, #0x5a6d
	MOVW R3, #0x6308
	MOVT R3, #0x9142
	MOVW R4, #0x4b1b
	MOVT R4, #0x6e07
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_2_Hash
SE_ReadKey_1_Pub_2_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x33e6
	MOVT R1, #0x7180
	MOVW R2, #0xffba
	MOVT R2, #0x9cf3
	MOVW R3, #0x7ec3
	MOVT R3, #0xdefd
	MOVW R4, #0xe4eb
	MOVT R4, #0x8d1d
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xfcbf
	MOVT R1, #0xb1b6
	MOVW R2, #0xe486
	MOVT R2, #0x56ae
	MOVW R3, #0x99ad
	MOVT R3, #0x393d
	MOVW R4, #0x6840
	MOVT R4, #0xf401
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3dd8
	MOVT R1, #0x97d4
	MOVW R2, #0xbdaf
	MOVT R2, #0x116d
	MOVW R3, #0xf7e6
	MOVT R3, #0x6f6e
	MOVW R4, #0xbeb1
	MOVT R4, #0x7ffa
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_3
SE_ReadKey_1_Pub_3:
	PUSH {R1-R5}
	MOVW R1, #0x2a0d
	MOVT R1, #0xc4fc
	MOVW R2, #0x51f
	MOVT R2, #0x1608
	MOVW R3, #0x1276
	MOVT R3, #0x45b4
	MOVW R4, #0x1f01
	MOVT R4, #0x1220
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x5f08
	MOVT R1, #0xd7e
	MOVW R2, #0xa403
	MOVT R2, #0x78a8
	MOVW R3, #0x6d7
	MOVT R3, #0x473f
	MOVW R4, #0xd9b4
	MOVT R4, #0x5f44
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe441
	MOVT R1, #0x5a03
	MOVW R2, #0x9eaa
	MOVT R2, #0x414f
	MOVW R3, #0xccea
	MOVT R3, #0x7ec5
	MOVW R4, #0x66c8
	MOVT R4, #0xfcd4
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe9d8
	MOVT R1, #0xfda9
	MOVW R2, #0xf73b
	MOVT R2, #0x52c7
	MOVW R3, #0xa284
	MOVT R3, #0x2379
	MOVW R4, #0x228b
	MOVT R4, #0x7751
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xd570
	MOVT R1, #0x9028
	MOVW R2, #0x716f
	MOVT R2, #0x54dd
	MOVW R3, #0x3f3c
	MOVT R3, #0xe5cb
	MOVW R4, #0xa679
	MOVT R4, #0x46dc
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc35e
	MOVT R1, #0xeb23
	MOVW R2, #0xcab3
	MOVT R2, #0xb1a2
	MOVW R3, #0x7acf
	MOVT R3, #0x4d32
	MOVW R4, #0x6dd8
	MOVT R4, #0x3461
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_3_Hash
SE_ReadKey_1_Pub_3_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x2277
	MOVT R1, #0x1ad9
	MOVW R2, #0xa30e
	MOVT R2, #0x8005
	MOVW R3, #0x6731
	MOVT R3, #0xad4f
	MOVW R4, #0xfabf
	MOVT R4, #0x5311
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8b48
	MOVT R1, #0x59bf
	MOVW R2, #0x4a36
	MOVT R2, #0x4eaf
	MOVW R3, #0xd99a
	MOVT R3, #0x961f
	MOVW R4, #0xef03
	MOVT R4, #0x997b
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe5a9
	MOVT R1, #0x97ee
	MOVW R2, #0xb378
	MOVT R2, #0x2f05
	MOVW R3, #0x3056
	MOVT R3, #0x3c22
	MOVW R4, #0xad
	MOVT R4, #0x1ea7
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_4
SE_ReadKey_1_Pub_4:
	PUSH {R1-R5}
	MOVW R1, #0x7e16
	MOVT R1, #0xecb
	MOVW R2, #0x4f06
	MOVT R2, #0x422f
	MOVW R3, #0xa5fc
	MOVT R3, #0xe1c4
	MOVW R4, #0x81c3
	MOVT R4, #0xde76
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x8d02
	MOVT R1, #0xd463
	MOVW R2, #0x4a68
	MOVT R2, #0xc957
	MOVW R3, #0xac44
	MOVT R3, #0x983e
	MOVW R4, #0x6b3f
	MOVT R4, #0xc490
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4637
	MOVT R1, #0x570f
	MOVW R2, #0x7eb6
	MOVT R2, #0xb097
	MOVW R3, #0x1f0e
	MOVT R3, #0x990c
	MOVW R4, #0xa189
	MOVT R4, #0x9c04
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x4bf3
	MOVT R1, #0xdfbe
	MOVW R2, #0x4ccd
	MOVT R2, #0xa768
	MOVW R3, #0xf1b8
	MOVT R3, #0x5304
	MOVW R4, #0x5052
	MOVT R4, #0xf5c9
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x73c1
	MOVT R1, #0xdccd
	MOVW R2, #0xcdbb
	MOVT R2, #0x6284
	MOVW R3, #0x4a7d
	MOVT R3, #0x3461
	MOVW R4, #0x7c89
	MOVT R4, #0x68a8
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x9a45
	MOVT R1, #0x468f
	MOVW R2, #0x9c8f
	MOVT R2, #0x1d5
	MOVW R3, #0x7d34
	MOVT R3, #0x46ed
	MOVW R4, #0x1b0a
	MOVT R4, #0x53df
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_4_Hash
SE_ReadKey_1_Pub_4_Hash:
	PUSH {R1-R5}
	MOVW R1, #0xc5a1
	MOVT R1, #0x96cd
	MOVW R2, #0xee7d
	MOVT R2, #0x8e1a
	MOVW R3, #0x1969
	MOVT R3, #0xefc0
	MOVW R4, #0xe308
	MOVT R4, #0x3c8c
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc0d4
	MOVT R1, #0xd2bd
	MOVW R2, #0x253b
	MOVT R2, #0x91f8
	MOVW R3, #0xfede
	MOVT R3, #0x76ff
	MOVW R4, #0xb2ae
	MOVT R4, #0xe9c0
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xcf9a
	MOVT R1, #0xd790
	MOVW R2, #0x59d0
	MOVT R2, #0x3061
	MOVW R3, #0x7c26
	MOVT R3, #0xa5ed
	MOVW R4, #0xe56e
	MOVT R4, #0xc560
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_5
SE_ReadKey_1_Pub_5:
	PUSH {R1-R5}
	MOVW R1, #0x7302
	MOVT R1, #0x27fe
	MOVW R2, #0xad5
	MOVT R2, #0x4b5
	MOVW R3, #0xeb02
	MOVT R3, #0x72cb
	MOVW R4, #0x2623
	MOVT R4, #0xa8ff
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xecb
	MOVT R1, #0x5008
	MOVW R2, #0x1f34
	MOVT R2, #0x823
	MOVW R3, #0xf690
	MOVT R3, #0x417c
	MOVW R4, #0x72e6
	MOVT R4, #0x6342
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbade
	MOVT R1, #0x1f5a
	MOVW R2, #0x6649
	MOVT R2, #0x4c7b
	MOVW R3, #0x7cc2
	MOVT R3, #0xed57
	MOVW R4, #0xd4c3
	MOVT R4, #0xc6b5
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xe786
	MOVT R1, #0x4f49
	MOVW R2, #0x2eb4
	MOVT R2, #0x474b
	MOVW R3, #0xad14
	MOVT R3, #0xb093
	MOVW R4, #0xd72a
	MOVT R4, #0x1337
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xb659
	MOVT R1, #0x83d7
	MOVW R2, #0x776a
	MOVT R2, #0xccbb
	MOVW R3, #0x8080
	MOVT R3, #0x6cb8
	MOVW R4, #0x3cec
	MOVT R4, #0xab1e
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x2099
	MOVT R1, #0xf41d
	MOVW R2, #0xa1e6
	MOVT R2, #0x4254
	MOVW R3, #0x3b9b
	MOVT R3, #0xfd03
	MOVW R4, #0x13e9
	MOVT R4, #0x25ff
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_5_Hash
SE_ReadKey_1_Pub_5_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x4451
	MOVT R1, #0x513
	MOVW R2, #0x658c
	MOVT R2, #0x47df
	MOVW R3, #0x76c5
	MOVT R3, #0x3dea
	MOVW R4, #0x7f31
	MOVT R4, #0x6371
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x55b4
	MOVT R1, #0xe4cd
	MOVW R2, #0x8073
	MOVT R2, #0xfec6
	MOVW R3, #0xc324
	MOVT R3, #0xacc5
	MOVW R4, #0xb2cb
	MOVT R4, #0x92e3
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x9155
	MOVT R1, #0x91a8
	MOVW R2, #0x2f4
	MOVT R2, #0xe84a
	MOVW R3, #0x2b83
	MOVT R3, #0xc883
	MOVW R4, #0x9bc5
	MOVT R4, #0x86ae
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_6
SE_ReadKey_1_Pub_6:
	PUSH {R1-R5}
	MOVW R1, #0xa27a
	MOVT R1, #0xe99b
	MOVW R2, #0x2a8f
	MOVT R2, #0xf9d0
	MOVW R3, #0x75de
	MOVT R3, #0x7b5f
	MOVW R4, #0x3019
	MOVT R4, #0x6c59
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbb78
	MOVT R1, #0x3b04
	MOVW R2, #0x1dbd
	MOVT R2, #0x90a2
	MOVW R3, #0xedfc
	MOVT R3, #0x6a52
	MOVW R4, #0x2d1e
	MOVT R4, #0xb192
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xf865
	MOVT R1, #0xdfeb
	MOVW R2, #0xe1da
	MOVT R2, #0xeda
	MOVW R3, #0xcfc2
	MOVT R3, #0xa21a
	MOVW R4, #0xdb55
	MOVT R4, #0x5655
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1266
	MOVT R1, #0xfdde
	MOVW R2, #0x660a
	MOVT R2, #0xdc84
	MOVW R3, #0x5aca
	MOVT R3, #0x818c
	MOVW R4, #0x35ee
	MOVT R4, #0xe5e7
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x9864
	MOVT R1, #0xde9d
	MOVW R2, #0x149f
	MOVT R2, #0xb29a
	MOVW R3, #0x423a
	MOVT R3, #0xb88a
	MOVW R4, #0x3904
	MOVT R4, #0xb4ab
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xa5f1
	MOVT R1, #0x35b5
	MOVW R2, #0xa60
	MOVT R2, #0x2ea7
	MOVW R3, #0xb8ce
	MOVT R3, #0xb6ae
	MOVW R4, #0xfd07
	MOVT R4, #0xd9a
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_6_Hash
SE_ReadKey_1_Pub_6_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x26b1
	MOVT R1, #0x1554
	MOVW R2, #0x5b1d
	MOVT R2, #0x7093
	MOVW R3, #0xef95
	MOVT R3, #0x8258
	MOVW R4, #0xd56a
	MOVT R4, #0x8d9e
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xa380
	MOVT R1, #0xa15f
	MOVW R2, #0x2c76
	MOVT R2, #0xcda3
	MOVW R3, #0x1377
	MOVT R3, #0xcc69
	MOVW R4, #0xe1a6
	MOVT R4, #0x4f28
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x223c
	MOVT R1, #0x9a2
	MOVW R2, #0x49f
	MOVT R2, #0x7032
	MOVW R3, #0x634
	MOVT R3, #0xafba
	MOVW R4, #0xee73
	MOVT R4, #0x627
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_1_Pub_7
SE_ReadKey_1_Pub_7:
	PUSH {R1-R5}
	MOVW R1, #0xddf3
	MOVT R1, #0x6422
	MOVW R2, #0x4e1b
	MOVT R2, #0xfa1c
	MOVW R3, #0xb0ec
	MOVT R3, #0x3a7c
	MOVW R4, #0xe160
	MOVT R4, #0xd778
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x54c7
	MOVT R1, #0x18c4
	MOVW R2, #0x56b2
	MOVT R2, #0x22be
	MOVW R3, #0x8d29
	MOVT R3, #0x3633
	MOVW R4, #0x68db
	MOVT R4, #0x3f04
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc83f
	MOVT R1, #0xe6c0
	MOVW R2, #0x954e
	MOVT R2, #0xe1c9
	MOVW R3, #0xc608
	MOVT R3, #0x2933
	MOVW R4, #0xdcd4
	MOVT R4, #0x172a
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x3727
	MOVT R1, #0x781b
	MOVW R2, #0x1a3
	MOVT R2, #0x9648
	MOVW R3, #0x31f7
	MOVT R3, #0xf9cc
	MOVW R4, #0xb665
	MOVT R4, #0x1be2
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x9c43
	MOVT R1, #0x61a0
	MOVW R2, #0x39d8
	MOVT R2, #0xcdde
	MOVW R3, #0x9905
	MOVT R3, #0x84d4
	MOVW R4, #0xab72
	MOVT R4, #0xa217
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xbcee
	MOVT R1, #0xe5ca
	MOVW R2, #0x98af
	MOVT R2, #0x4e1e
	MOVW R3, #0xc504
	MOVT R3, #0x2071
	MOVW R4, #0x9d02
	MOVT R4, #0xab76
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.global SE_ReadKey_1_Pub_7_Hash
SE_ReadKey_1_Pub_7_Hash:
	PUSH {R1-R5}
	MOVW R1, #0x3666
	MOVT R1, #0x8b99
	MOVW R2, #0x5b84
	MOVT R2, #0xb7ae
	MOVW R3, #0xa135
	MOVT R3, #0xa972
	MOVW R4, #0xb0bb
	MOVT R4, #0xdf56
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x6a6c
	MOVT R1, #0x4c31
	MOVW R2, #0xd5cf
	MOVT R2, #0x99fa
	MOVW R3, #0x8626
	MOVT R3, #0x77c3
	MOVW R4, #0xf3ed
	MOVT R4, #0xab59
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0xc967
	MOVT R1, #0x7f68
	MOVW R2, #0xd1fc
	MOVT R2, #0xd750
	MOVW R3, #0x2c3c
	MOVT R3, #0x68e4
	MOVW R4, #0x39e3
	MOVT R4, #0x880
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

    .end
