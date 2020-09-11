//
// Created by Alan Ihre on 2020-09-07.
//

#ifndef LAB7_CLASSINSTANCE_H
#define LAB7_CLASSINSTANCE_H

#include "ClassFile.h"
#include <string>

class ClassInstance {
public:
    ClassFile *classFile;
    ClassInstance *parentInstance;
    int *instanceData;
    int instanceDataSize;

    ClassInstance() = default;

    void initializeObject(ClassFile *classFile, ClassInstance *parentInstance);

    void initializeArray(ClassFile *classFile, int size);

    void putField(int index, int value);

    int getField(int index);

    int getArrayElement(int index);

    int putArrayElement(int index, int value);
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


#endif //LAB7_CLASSINSTANCE_H
