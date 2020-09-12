//
// Created by Alan Ihre on 2020-08-30.
//

#ifndef BASIC_JVM_INSTRUCTIONS_H
#define BASIC_JVM_INSTRUCTIONS_H

#define ARRAY_TYPE_BOOLEAN 4
#define ARRAY_TYPE_CHAR 5
#define ARRAY_TYPE_FLOAT 6
#define ARRAY_TYPE_DOUBLE 7
#define ARRAY_TYPE_BYTE 8
#define ARRAY_TYPE_SHORT 9
#define ARRAY_TYPE_INT 10
#define ARRAY_TYPE_LONG 11

#define IADD 0x60
#define ISUB 0x64
#define SIPUSH 0x11
#define BIPUSH 0x10
#define ICONST_M1 0x2
#define ICONST_0 0x3
#define ICONST_1 0x4
#define ICONST_2 0x5
#define ICONST_3 0x6
#define ICONST_4 0x7
#define ICONST_5 0x8
#define IMUL 0x68
#define INEG 0x74
#define IDIV 0x6c
#define DUP 0x59
#define DUP_X1 0x5a
#define DUP_X2 0x5b
#define DUP2 0x5c
#define DUP2_X1 0x5d
#define DUP2_X2 0x5e
#define IAND 0x7e
#define IOR 0x80
#define IREM 0x70
#define ISHL 0x78
#define ISHR 0x7a
#define IXOR 0x82
#define NOP 0x0
#define POP 0x57
#define POP2 0x58
#define SWAP 0x5f
#define ILOAD 0x15
#define ILOAD_0 0x1a
#define ILOAD_1 0x1b
#define ILOAD_2 0x1c
#define ILOAD_3 0x1d
#define ISTORE 0x36
#define ISTORE_0 0x3b
#define ISTORE_1 0x3c
#define ISTORE_2 0x3d
#define ISTORE_3 0x3e
#define ALOAD 0x19
#define ALOAD_0 0x2a
#define ALOAD_1 0x2b
#define ALOAD_2 0x2c
#define ALOAD_3 0x2d
#define ASTORE 0x3a
#define ASTORE_0 0x4b
#define ASTORE_1 0x4c
#define ASTORE_2 0x4d
#define ASTORE_3 0x4e
#define RETURN 0xb1
#define IRETURN 0xac
#define ARETURN 0xb0
#define I2B 0x91
#define I2C 0x92
#define I2S 0x93
#define IUSHR 0x7c
#define IINC 0x84
#define JSR 0xa8
#define JSR_W 0xc9
#define IFEQ 0x99
#define IFNE 0x9a
#define IFLT 0x9b
#define IFGE 0x9c
#define IFGT 0x9d
#define IFLE 0x9e
#define IF_ICMPEQ 0x9f
#define IF_ICMPNE 0xa0
#define IF_ICMPLT 0xa1
#define IF_ICMPGE 0xa2
#define IF_ICMPGT 0xa3
#define IF_ICMPLE 0xa4
#define GOTO 0xa7
#define GOTO_W 0xc8
#define RET 0xa9
#define ACONST_NULL 0x1
#define IF_ACMPEQ 0xa5
#define IF_ACMPNE 0xa6
#define IFNONNULL 0xc7
#define IFNULL 0xc6
#define LDC 0x12
#define LDC_W 0x13
#define NEW 0xbb
#define INVOKE_SPECIAL 0xb7
#define INVOKE_VIRTUAL 0xb6
#define INVOKE_STATIC 0xb8
#define PUT_FIELD 0xb5
#define PUT_STATIC 0xb3
#define GET_STATIC 0xb2
#define GET_FIELD 0xb4
#define NEW_ARRAY 0xbc
#define ARRAY_LENGTH 0xbe
#define IA_LOAD 0x2e
#define BA_LOAD 0x33
#define CA_LOAD 0x34
#define SA_LOAD 0x35
#define IA_STORE 0x4f
#define BA_STORE 0x54
#define CA_STORE 0x55
#define SA_STORE 0x56
#define INTERNAL_PRINTLN 0xfd

#endif //BASIC_JVM_INSTRUCTIONS_H
