//
// Created by Alan Ihre on 2020-09-07.
//

#ifndef BASIC_JVM_CLASSINSTANCE_H
#define BASIC_JVM_CLASSINSTANCE_H

#include "ClassFile.h"
#include <string>
#include "ObjectPool.h"
#include <vector>

typedef int ObjectRef;

class ClassInstance {
public:
    ClassFile *classFile;
    ObjectRef parentRef;
    std::vector<int> instanceData;
    int instanceDataSize;

    ClassInstance() = default;

    void initializeObject(ClassFile *classFile, ObjectRef parentRef);

    void initializeArray(ClassFile *classFile, int size);

    void putField(int index, int value);

    int getField(int index);

    int getArrayElement(int index);

    void putArrayElement(int index, int value);
};

class FieldIndexOutOfBoundsException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Field index out of bounds";
    }
};

class ArrayIndexOutOfBoundsException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Array index out of bounds";
    }
};


#endif //BASIC_JVM_CLASSINSTANCE_H
