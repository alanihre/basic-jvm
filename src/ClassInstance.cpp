//
// Created by Alan Ihre on 2020-09-07.
//

#include "ClassInstance.h"
#include <cstdlib>

void ClassInstance::initializeObject(ClassFile *classFile, ObjectRef parentRef) {
    this->classFile = classFile;
    this->parentRef = parentRef;

    instanceDataSize = classFile->fields_count;
    instanceData = std::vector<int>(classFile->fields_count, 0);
}

void ClassInstance::initializeArray(ClassFile *_classFile, int size) {
    this->classFile = _classFile;
    this->parentRef = 0;

    instanceDataSize = size + 1;

    instanceData = std::vector<int>(instanceDataSize, 0);

    //Length field
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

void ClassInstance::putArrayElement(int index, int value) {
    if (index > instanceData[0] - 1) {
        throw ArrayIndexOutOfBoundsException();
    }
    instanceData[index + 1] = value;
}
