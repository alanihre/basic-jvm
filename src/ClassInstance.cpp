//
// Created by Alan Ihre on 2020-09-07.
//

#include "ClassInstance.h"
#include <cstdlib>

void ClassInstance::initializeObject(ClassFile *_classFile, ClassInstance *_parentInstance) {
    this->classFile = _classFile;
    this->parentInstance = _parentInstance;

    if (instanceData != nullptr) {
        free(instanceData);
    }
    instanceData = (int *) calloc(classFile->fields_count, sizeof(int));
    instanceDataSize = classFile->fields_count;
}

void ClassInstance::initializeArray(ClassFile *_classFile, int size) {
    this->classFile = _classFile;
    this->parentInstance = nullptr;

    if (instanceData != nullptr) {
        free(instanceData);
    }
    instanceData = (int *) calloc(size, sizeof(int));

    //Length field
    instanceDataSize = size + 1;
    instanceData[0] = size;
}


void ClassInstance::putField(int index, int value) {
    if (index > classFile->fields_count - 1) {
        throw FieldIndexOutOfBoundsException();
    }
    instanceData[index] = value;
}

int ClassInstance::getField(int index) {
    if (index > classFile->fields_count - 1) {
        throw FieldIndexOutOfBoundsException();
    }
    return instanceData[index];
}

int ClassInstance::getArrayElement(int index) {
    if (index > instanceData[0] - 1) {
        throw ArrayIndexOutOfBoundsException();
    }
    return instanceData[index + 1];
}

int ClassInstance::putArrayElement(int index, int value) {
    if (index > instanceData[0] - 1) {
        throw ArrayIndexOutOfBoundsException();
    }
    instanceData[index + 1] = value;
}
