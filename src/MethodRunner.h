//
// Created by Alan Ihre on 2020-08-30.
//

#include <cstdint>
#include <exception>
#include <string>
#include <sstream>
#include <stack>
#include "Instructions.h"
#include <vector>
#include "ClassFile.h"
#include "StringPool.h"
#include "ClassInstantiator.h"
#include "MethodLookup.h"
#include "ClassFileLookup.h"
#include "FieldLookup.h"

#ifndef BASIC_JVM_INSTRUCTION_PARSER_H
#define BASIC_JVM_INSTRUCTION_PARSER_H


class MethodRunner {
public:
    MethodRunner(Code_attribute *code, ClassFile *classFile, std::stack<int> *operandStack, int numArgs,
                 const int *args, StringPool *stringPool, ObjectPool *objectPool, ClassInstantiator *classInstantiator,
                 ClassFileLookup *classFileLookup);

    ~MethodRunner();

    void run();

protected:
    std::stack<int> *operandStack;
    StringPool *stringPool;
    ObjectPool *objectPool;
    ClassInstantiator *classInstantiator;
    ClassFileLookup *classFileLookup;
    int *locals;
    bool shouldReturn = false;
    uint8_t *instructions;
    Code_attribute *code;
    ClassFile *classFile;
    int pc = 0;
    int stackEntrySize;

    void runInstruction();

    uint8_t next();

    void jump(int jumpAddr);

    void pushReturnAddress();

    int calculateJumpAddress();

    void handleReturn();

    int popOperand();

    int readTwoBytes();
};

class InstructionNotImplementedException : public std::exception {
    uint8_t instr;

public:
    explicit InstructionNotImplementedException(uint8_t instr) : std::exception() {
        this->instr = instr;
    }

    virtual const char *what() const throw() {
        std::ostringstream buf;
        buf << "Instruction 0x" << std::hex << this->instr << " not implemented";

        std::string str = buf.str();
        const char *c_str = str.c_str();
        return c_str;
    }
};

class NoMoreInstructionsException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "There are no more instructions for the method, yet it has not returned";
    }
};

class InvalidJumpAddressException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Invalid jump address";
    }
};

class NullPointerException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Pointer is null";
    }
};

class StackFrameAccessOutOfBoundsException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Trying to pop from outside of the stack frame";
    }
};

#endif //BASIC_JVM_INSTRUCTION_PARSER_H
