//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef BASIC_JVM_FIELDLOOKUP_H
#define BASIC_JVM_FIELDLOOKUP_H

#include "FieldTable.h"
#include "ClassInstance.h"

class FieldNotFoundException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Field not found";
    }
};


inline Field *lookupField(const std::string &name, const std::string &className, ObjectRef objectRef, ObjectRef *resultObjectRef, ObjectPool *objectPool) {
    ObjectRef currentObjectRef = objectRef;
    while (currentObjectRef != 0 && objectPool->getObject(currentObjectRef)->classFile->className != className) {
        currentObjectRef = objectPool->getObject(currentObjectRef)->parentRef;
    }
    if (currentObjectRef == 0) {
        throw FieldNotFoundException();

    }
    Field *field = objectPool->getObject(currentObjectRef)->classFile->fieldTable->getField(name);
    if (field == nullptr) {
        throw FieldNotFoundException();
    }
    *resultObjectRef = currentObjectRef;
    return field;
}

inline Field *lookupStaticField(const std::string &name, ClassFile *classFile) {
    ClassFile *currentClassFile = classFile;
    while (currentClassFile != nullptr) {
        Field *field = currentClassFile->fieldTable->getField(name);
        if (field != nullptr) {
            return field;
        }
        currentClassFile = currentClassFile->superClassFile;
    }

    throw FieldNotFoundException();
}

#endif //BASIC_JVM_FIELDLOOKUP_H
