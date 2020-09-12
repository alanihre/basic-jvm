//
// Created by Alan Ihre on 2020-08-30.
//

#include "MethodRunner.h"
#include "builtin/ArrayClassFile.h"
#include <iostream>

#define SHAMT_MASK 0x1F
#define BYTE_MASK 0xFF
#define CHAR_MASK 0xFFFF
#define SHORT_MASK 0xFFFF
#define NULL_REF 0

MethodRunner::MethodRunner(Code_attribute *code, ClassFile *classFile, std::stack<int> *operandStack, int numArgs,
                           const int *args, StringPool *stringPool, ObjectPool *objectPool,
                           ClassInstantiator *classInstantiator, ClassFileLookup *classFileLookup) {
    this->operandStack = operandStack;
    this->code = code;
    this->classInstantiator = classInstantiator;
    this->objectPool = objectPool;
    this->stringPool = stringPool;
    this->classFile = classFile;
    this->classFileLookup = classFileLookup;
    locals = new int[code->max_locals];
    //Copy arguments
    for (int i = 0; i < numArgs; ++i) {
        locals[i] = args[i];
    }
    instructions = (uint8_t *) code->code;
}

void MethodRunner::run() {
    while (!shouldReturn) {
        runInstruction();
    }
}

uint8_t MethodRunner::next() {
    if (pc > code->code_length - 1) {
        throw NoMoreInstructionsException();
    }
    return instructions[pc++];
}

void MethodRunner::jump(int jumpAddr) {
    if (jumpAddr > code->code_length - 1) {
        throw InvalidJumpAddressException();
    }
    pc = jumpAddr;
}

void MethodRunner::handleReturn() {
    shouldReturn = true;
}

void MethodRunner::runInstruction() {
    uint8_t instr = next();

    switch (instr) {
        case IADD: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 + value2;
            operandStack->push(res);
            break;
        }
        case ISUB: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 - value2;
            operandStack->push(res);
            break;
        }
        case IMUL: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 * value2;
            operandStack->push(res);
            break;
        }
        case IDIV: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 / value2;
            operandStack->push(res);
            break;
        }
        case IAND: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 & value2; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case IOR: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 | value2; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case IXOR: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 ^value2; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case IREM: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 % value2;
            operandStack->push(res);
            break;
        }
        case INEG: {
            int value = operandStack->top();
            operandStack->pop();
            int res = -value;
            operandStack->push(res);
            break;
        }
        case ISHL: {
            int shamt = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 << (shamt & SHAMT_MASK); // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case ISHR: {
            int shamt = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = value1 >> (shamt & SHAMT_MASK); // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case IUSHR: {
            int shamt = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            int res = (int) ((unsigned int) value1 >> (shamt & SHAMT_MASK)); // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case BIPUSH: {
            int8_t byte = next();
            operandStack->push(byte);
            break;
        }
        case SIPUSH: {
            uint8_t byte1 = next();
            uint8_t byte2 = next();
            int16_t res = (byte1 << 8) | byte2; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case ICONST_M1:
            operandStack->push(-1);
            break;
        case ICONST_0:
            operandStack->push(0);
            break;
        case ICONST_1:
            operandStack->push(1);
            break;
        case ICONST_2:
            operandStack->push(2);
            break;
        case ICONST_3:
            operandStack->push(3);
            break;
        case ICONST_4:
            operandStack->push(4);
            break;
        case ICONST_5:
            operandStack->push(5);
            break;
        case DUP:
            operandStack->push(operandStack->top());
            break;
        case DUP_X1: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();

            operandStack->push(value1);
            operandStack->push(value2);
            operandStack->push(value1);
            break;
        }
        case DUP_X2: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();
            int value3 = operandStack->top();
            operandStack->pop();

            operandStack->push(value1);
            operandStack->push(value3);
            operandStack->push(value2);
            operandStack->push(value1);
            break;
        }
        case DUP2: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();

            operandStack->push(value2);
            operandStack->push(value1);
            operandStack->push(value2);
            operandStack->push(value1);
            break;
        }
        case DUP2_X1: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();
            int value3 = operandStack->top();
            operandStack->pop();

            operandStack->push(value2);
            operandStack->push(value1);
            operandStack->push(value3);
            operandStack->push(value2);
            operandStack->push(value1);
            break;
        }
        case DUP2_X2: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();
            int value3 = operandStack->top();
            operandStack->pop();
            int value4 = operandStack->top();
            operandStack->pop();

            operandStack->push(value2);
            operandStack->push(value1);
            operandStack->push(value4);
            operandStack->push(value3);
            operandStack->push(value2);
            operandStack->push(value1);
            break;
        }
        case NOP:
            break;
        case POP:
            operandStack->pop();
            break;
        case POP2:
            operandStack->pop();
            operandStack->pop();
            break;
        case SWAP: {
            int value1 = operandStack->top();
            operandStack->pop();
            int value2 = operandStack->top();
            operandStack->pop();

            operandStack->push(value1);
            operandStack->push(value2);
            break;
        }
        case ILOAD: // Fall through
        case ALOAD: {
            uint8_t index = next();
            int value = locals[index];
            operandStack->push(value);
            break;
        }
        case ILOAD_0: // Fall through
        case ALOAD_0: {
            int value = locals[0];
            operandStack->push(value);
            break;
        }
        case ILOAD_1: // Fall through
        case ALOAD_1: {
            int value = locals[1];
            operandStack->push(value);
            break;
        }
        case ILOAD_2: // Fall through
        case ALOAD_2: {
            int value = locals[2];
            operandStack->push(value);
            break;
        }
        case ILOAD_3: // Fall through
        case ALOAD_3: {
            int value = locals[3];
            operandStack->push(value);
            break;
        }
        case ISTORE: // Fall through
        case ASTORE: {
            uint8_t index = next();
            int value = operandStack->top();
            operandStack->pop();
            locals[index] = value;
            break;
        }
        case ISTORE_0: // Fall through
        case ASTORE_0: {
            int value = operandStack->top();
            operandStack->pop();
            locals[0] = value;
            break;
        }
        case ISTORE_1: // Fall through
        case ASTORE_1: {
            int value = operandStack->top();
            operandStack->pop();
            locals[1] = value;
            break;
        }
        case ISTORE_2: // Fall through
        case ASTORE_2: {
            int value = operandStack->top();
            operandStack->pop();
            locals[2] = value;
            break;
        }
        case ISTORE_3: // Fall through
        case ASTORE_3: {
            int value = operandStack->top();
            operandStack->pop();
            locals[3] = value;
            break;
        }
        case RETURN: // Fall through
        case IRETURN: // Fall through
        case ARETURN: {
            handleReturn();
            break;
        }
        case I2B: {
            int value = operandStack->top();
            operandStack->pop();
            int res = value & BYTE_MASK; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case I2C: {
            int value = operandStack->top();
            operandStack->pop();
            int res = value & CHAR_MASK; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case I2S: {
            int value = operandStack->top();
            operandStack->pop();
            int res = value & SHORT_MASK; // NOLINT(hicpp-signed-bitwise)
            operandStack->push(res);
            break;
        }
        case IINC: {
            uint8_t index = next();
            int value = locals[index];
            int8_t imm = next();
            value += imm;
            locals[index] = value;
            break;
        }
        case JSR: {
            pushReturnAddress();
            int jumpAddr = calculateJumpAddress();
            jump(jumpAddr);
            break;
        }
        case JSR_W: {
            pushReturnAddress();

            uint8_t branchByte1 = next();
            uint8_t branchByte2 = next();
            uint8_t branchByte3 = next();
            uint8_t branchByte4 = next();
            int32_t jumpOffset = (branchByte1 << 24) | (branchByte2 << 16) | (branchByte3 << 8) |
                             branchByte4; // NOLINT(hicpp-signed-bitwise)
            int jumpAddr = pc + jumpOffset;
            jump(jumpAddr);
            break;
        }
        case IFEQ: {
            int value = operandStack->top();
            operandStack->pop();
            if (value == 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFNE: {
            int value = operandStack->top();
            operandStack->pop();
            if (value != 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFLT: {
            int value = operandStack->top();
            operandStack->pop();
            if (value < 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFGE: {
            int value = operandStack->top();
            operandStack->pop();
            if (value >= 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFGT: {
            int value = operandStack->top();
            operandStack->pop();
            if (value > 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFLE: {
            int value = operandStack->top();
            operandStack->pop();
            if (value <= 0) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPEQ: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 == value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPNE: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 != value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPLT: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 < value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPLE: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 <= value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPGT: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 > value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ICMPGE: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 >= value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();;
            }
            break;
        }
        case GOTO: {
            int jumpAddr = calculateJumpAddress();
            jump(jumpAddr);
            break;
        }
        case GOTO_W: {
            uint8_t branchByte1 = next();
            uint8_t branchByte2 = next();
            uint8_t branchByte3 = next();
            uint8_t branchByte4 = next();
            int32_t jumpOffset = (branchByte1 << 24) | (branchByte2 << 16) | (branchByte3 << 8) |
                             branchByte4; // NOLINT(hicpp-signed-bitwise)
            int jumpAddr = pc + jumpOffset;
            jump(jumpAddr);
            break;
        }
        case RET: {
            uint8_t index = next();
            int jumpAddr = locals[index];
            jump(jumpAddr);
            break;
        }
        case ACONST_NULL: {
            operandStack->push(NULL_REF);
            break;
        }
        case IF_ACMPEQ: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 == value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IF_ACMPNE: {
            int value2 = operandStack->top();
            operandStack->pop();
            int value1 = operandStack->top();
            operandStack->pop();
            if (value1 != value2) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFNONNULL: {
            int value = operandStack->top();
            operandStack->pop();
            if (value != NULL_REF) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case IFNULL: {
            int value = operandStack->top();
            operandStack->pop();
            if (value == NULL_REF) {
                int jumpAddr = calculateJumpAddress();
                jump(jumpAddr);
            } else {
                next();
                next();
            }
            break;
        }
        case LDC_W: // Fall through
        case LDC: {
            int index;
            if (instr == LDC_W) {
                uint8_t indexByte1 = next();
                uint8_t indexByte2 = next();
                index = (uint16_t) ((indexByte1 << 8) | indexByte2); // NOLINT(hicpp-signed-bitwise)
            } else {
                index = next();
            }

            cp_info cpEntry = classFile->constant_pool[index - 1];

            int value;

            switch (cpEntry.tag) {
                case CONSTANT_TYPE_INTEGER: {
                    auto *integerInfo = (CONSTANT_Integer_info *) cpEntry.info;
                    value = integerInfo->bytes;
                    break;
                }
                case CONSTANT_TYPE_STRING: {
                    auto *stringInfo = (CONSTANT_String_info *) cpEntry.info;
                    cp_info utf8Entry = classFile->constant_pool[stringInfo->string_index - 1];
                    auto *utf8Info = (CONSTANT_Utf8_info *) utf8Entry.info;
                    const char *stringValue = (char *) utf8Info->bytes;
                    ObjectRef stringRef = stringPool->getStringInstanceRef(stringValue);
                    value = stringRef;
                    break;
                }
                case CONSTANT_TYPE_METHOD_TYPE: {
                    //TODO
                    break;
                }
                case CONSTANT_TYPE_METHOD_HANDLE: {
                    //TODO
                    break;
                }
                case CONSTANT_TYPE_CLASS: {
                    //TODO
                    break;
                }
            }

            operandStack->push(value);
            break;
        }
        case NEW: {
            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *classInfo = (CONSTANT_Class_info *) cpEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            ObjectRef objectRef = objectPool->newObjectRef();
            classInstantiator->newInstance(std::string(className), objectRef);

            operandStack->push(objectRef);
            break;
        }
        case INVOKE_VIRTUAL: // Fall through
        case INVOKE_STATIC: // Fall through
        case INVOKE_SPECIAL: {
            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *methodRef = (CONSTANT_Methodref_info *) cpEntry.info;

            cp_info classEntry = classFile->constant_pool[methodRef->class_index - 1];
            auto *classInfo = (CONSTANT_Class_info *) classEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            cp_info nameAndTypeEntry = classFile->constant_pool[methodRef->name_and_type_index - 1];
            auto *nameAndTypeInfo = (CONSTANT_NameAndType_info *) nameAndTypeEntry.info;

            cp_info methodNameEntry = classFile->constant_pool[nameAndTypeInfo->name_index - 1];
            auto *methodNameInfo = (CONSTANT_Utf8_info *) methodNameEntry.info;
            const char *methodName = (char *) methodNameInfo->bytes;

            cp_info methodDescriptorEntry = classFile->constant_pool[nameAndTypeInfo->descriptor_index - 1];
            auto *descriptorInfo = (CONSTANT_Utf8_info *) methodDescriptorEntry.info;
            const char *descriptor = (char *) descriptorInfo->bytes;

            std::string signature = std::string(methodName) + std::string(descriptor);

            //This-argument and the other arguments
            int numArgs = countArguments(std::string(descriptor));
            if (instr == INVOKE_VIRTUAL || instr == INVOKE_SPECIAL) {
                numArgs++;
            }
            int *args = new int[numArgs];
            for (int i = numArgs - 1; i >= 0; --i) {
                int value = operandStack->top();
                operandStack->pop();
                args[i] = value;
            }

            Method *method;
            ObjectRef objectRef;
            if (instr == INVOKE_VIRTUAL || instr == INVOKE_SPECIAL) {
                objectRef = args[0];
                if (objectRef == NULL_REF) {
                    throw NullPointerException();
                }
            }
            if (instr == INVOKE_VIRTUAL) {
                method = lookupMethod(signature, objectRef, objectPool);
            } else if (instr == INVOKE_STATIC || instr == INVOKE_SPECIAL) {
                ClassFile *methodClassFile = classFileLookup->getClassFile(std::string(className));
                method = lookupStaticMethod(signature, methodClassFile);
            }

            MethodRunner methodRunner(method->codeAttribute, method->classFile, operandStack, numArgs, args, stringPool,
                                      objectPool, classInstantiator, classFileLookup);
            methodRunner.run();

            delete[] args;

            break;
        }
        case PUT_FIELD: {
            int value = operandStack->top();
            operandStack->pop();
            int objectRef = operandStack->top();
            operandStack->pop();

            if (objectRef == NULL_REF) {
                throw NullPointerException();
            }

            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *fieldRef = (CONSTANT_Fieldref_info *) cpEntry.info;

            cp_info classEntry = classFile->constant_pool[fieldRef->class_index - 1];
            auto *classInfo = (CONSTANT_Class_info *) classEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            cp_info nameAndTypeEntry = classFile->constant_pool[fieldRef->name_and_type_index - 1];
            auto *nameAndTypeInfo = (CONSTANT_NameAndType_info *) nameAndTypeEntry.info;

            cp_info fieldNameEntry = classFile->constant_pool[nameAndTypeInfo->name_index - 1];
            auto *fieldNameInfo = (CONSTANT_Utf8_info *) fieldNameEntry.info;
            const char *fieldName = (char *) fieldNameInfo->bytes;

            cp_info fieldDescriptorEntry = classFile->constant_pool[nameAndTypeInfo->descriptor_index - 1];
            auto *descriptorInfo = (CONSTANT_Utf8_info *) fieldDescriptorEntry.info;
            const char *descriptor = (char *) descriptorInfo->bytes;

            ObjectRef resultObjectRef = 0;

            ClassFile *fieldClassFile = classFileLookup->getClassFile(std::string(className));
            Field *field = lookupField(fieldName, className, objectRef, &resultObjectRef, objectPool);

            objectPool->getObject(resultObjectRef)->putField(field->index, value);

            break;
        }
        case PUT_STATIC: {
            int value = operandStack->top();
            operandStack->pop();

            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *fieldRef = (CONSTANT_Fieldref_info *) cpEntry.info;

            cp_info classEntry = classFile->constant_pool[fieldRef->class_index - 1];
            auto *classInfo = (CONSTANT_Class_info *) classEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            cp_info nameAndTypeEntry = classFile->constant_pool[fieldRef->name_and_type_index - 1];
            auto *nameAndTypeInfo = (CONSTANT_NameAndType_info *) nameAndTypeEntry.info;

            cp_info fieldNameEntry = classFile->constant_pool[nameAndTypeInfo->name_index - 1];
            auto *fieldNameInfo = (CONSTANT_Utf8_info *) fieldNameEntry.info;
            const char *fieldName = (char *) fieldNameInfo->bytes;

            cp_info fieldDescriptorEntry = classFile->constant_pool[nameAndTypeInfo->descriptor_index - 1];
            auto *descriptorInfo = (CONSTANT_Utf8_info *) fieldDescriptorEntry.info;
            const char *descriptor = (char *) descriptorInfo->bytes;

            ClassFile *fieldClassFile = classFileLookup->getClassFile(std::string(className));
            Field *field = lookupStaticField(fieldName, fieldClassFile);

            field->staticValue = value;

            break;
        }
        case GET_STATIC: {
            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *fieldRef = (CONSTANT_Fieldref_info *) cpEntry.info;

            cp_info classEntry = classFile->constant_pool[fieldRef->class_index - 1];
            auto *classInfo = (CONSTANT_Class_info *) classEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            cp_info nameAndTypeEntry = classFile->constant_pool[fieldRef->name_and_type_index - 1];
            auto *nameAndTypeInfo = (CONSTANT_NameAndType_info *) nameAndTypeEntry.info;

            cp_info fieldNameEntry = classFile->constant_pool[nameAndTypeInfo->name_index - 1];
            auto *fieldNameInfo = (CONSTANT_Utf8_info *) fieldNameEntry.info;
            const char *fieldName = (char *) fieldNameInfo->bytes;

            cp_info fieldDescriptorEntry = classFile->constant_pool[nameAndTypeInfo->descriptor_index - 1];
            auto *descriptorInfo = (CONSTANT_Utf8_info *) fieldDescriptorEntry.info;
            const char *descriptor = (char *) descriptorInfo->bytes;

            ClassFile *fieldClassFile = classFileLookup->getClassFile(std::string(className));
            Field *field = lookupStaticField(fieldName, fieldClassFile);

            operandStack->push(field->staticValue);

            break;
        }
        case GET_FIELD: {
            int objectRef = operandStack->top();
            operandStack->pop();

            if (objectRef == NULL_REF) {
                throw NullPointerException();
            }

            uint8_t indexByte1 = next();
            uint8_t indexByte2 = next();
            int index = (indexByte1 << 8) | indexByte2; // NOLINT(hicpp-signed-bitwise)

            cp_info cpEntry = classFile->constant_pool[index - 1];
            auto *fieldRef = (CONSTANT_Fieldref_info *) cpEntry.info;

            cp_info classEntry = classFile->constant_pool[fieldRef->class_index - 1];
            auto *classInfo = (CONSTANT_Class_info *) classEntry.info;
            cp_info classNameEntry = classFile->constant_pool[classInfo->name_index - 1];
            auto *classNameInfo = (CONSTANT_Utf8_info *) classNameEntry.info;
            const char *className = (char *) classNameInfo->bytes;

            cp_info nameAndTypeEntry = classFile->constant_pool[fieldRef->name_and_type_index - 1];
            auto *nameAndTypeInfo = (CONSTANT_NameAndType_info *) nameAndTypeEntry.info;

            cp_info fieldNameEntry = classFile->constant_pool[nameAndTypeInfo->name_index - 1];
            auto *fieldNameInfo = (CONSTANT_Utf8_info *) fieldNameEntry.info;
            const char *fieldName = (char *) fieldNameInfo->bytes;

            cp_info fieldDescriptorEntry = classFile->constant_pool[nameAndTypeInfo->descriptor_index - 1];
            auto *descriptorInfo = (CONSTANT_Utf8_info *) fieldDescriptorEntry.info;
            const char *descriptor = (char *) descriptorInfo->bytes;


            ObjectRef resultObjectRef = 0;

            ClassFile *fieldClassFile = classFileLookup->getClassFile(std::string(className));
            Field *field = lookupField(fieldName, className, objectRef, &resultObjectRef, objectPool);
            int value = objectPool->getObject(resultObjectRef)->getField(field->index);

            operandStack->push(value);
            break;
        }
        case NEW_ARRAY: {
            int count = operandStack->top();
            operandStack->pop();
            //TODO: Check positive count

            uint8_t arrayType = next();

            ObjectRef objectRef = objectPool->newObjectRef();

            ClassFile *arrayClassFile = classFileLookup->getClassFile(std::string(BUILTIN_ARRAY_CLASS_NAME));
            objectPool->getObject(objectRef)->initializeArray(arrayClassFile, count);

            operandStack->push(objectRef);
            break;
        }
        case ARRAY_LENGTH: {
            int arrayRef = operandStack->top();
            operandStack->pop();

            if (arrayRef == NULL_REF) {
                throw NullPointerException();
            }

            //Length is in field 0
            int length = objectPool->getObject(arrayRef)->getField(0);
            operandStack->push(length);

            break;
        }
        case BA_LOAD: // Fall through
        case CA_LOAD: // Fall through
        case SA_LOAD: // Fall through
        case IA_LOAD: {
            int index = operandStack->top();
            operandStack->pop();
            int arrayRef = operandStack->top();
            operandStack->pop();

            if (arrayRef == NULL_REF) {
                throw NullPointerException();
            }

            int value = objectPool->getObject(arrayRef)->getArrayElement(index);
            operandStack->push(value);

            break;
        }
        case BA_STORE: // Fall through
        case CA_STORE: // Fall through
        case SA_STORE: // Fall through
        case IA_STORE: {
            int value = operandStack->top();
            operandStack->pop();
            int index = operandStack->top();
            operandStack->pop();
            int arrayRef = operandStack->top();
            operandStack->pop();

            if (arrayRef == NULL_REF) {
                throw NullPointerException();
            }

            objectPool->getObject(arrayRef)->putArrayElement(index, value);
            break;
        }
        case INTERNAL_PRINTLN: {
            int stringObjectRef = operandStack->top();
            operandStack->pop();

            ObjectRef resultObjectRef = 0;

            Field *field = lookupField(BUILTIN_STRING_CLASS_VALUE_FIELD, "String", stringObjectRef, &resultObjectRef, objectPool);
            ObjectRef valueArrayRef = objectPool->getObject(resultObjectRef)->getField(field->index);

            int length = objectPool->getObject(valueArrayRef)->getField(0);

            for (int i = 0; i < length; ++i) {
                char c = objectPool->getObject(valueArrayRef)->getArrayElement(i) &
                         CHAR_MASK; // NOLINT(hicpp-signed-bitwise,cppcoreguidelines-narrowing-conversions)
                std::cout << c;
            }
            std::cout << std::endl;


            break;
        }
        default:
            throw InstructionNotImplementedException(instr);
    }
}

void MethodRunner::pushReturnAddress() {
    int returnAddress = pc + 1;
    operandStack->push(returnAddress);
}

int MethodRunner::calculateJumpAddress() {
    u1 branchByte1 = next();
    u1 branchByte2 = next();
    int16_t jumpOffset = (branchByte1 << 8) | branchByte2; // NOLINT(hicpp-signed-bitwise)

    //-2 for the two branch bytes and -1 since pc was increased by 1 during the call to next
    int jumpAddr = pc + jumpOffset - 2 - 1;
    return jumpAddr;
}

MethodRunner::~MethodRunner() {
    delete[] locals;
}
