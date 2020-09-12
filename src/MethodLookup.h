//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef BASIC_JVM_METHODLOOKUP_H
#define BASIC_JVM_METHODLOOKUP_H

#include "MethodTable.h"
#include "ClassInstance.h"

class MethodNotFoundException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Method not found";
    }
};

inline Method *lookupMethod(const std::string &signature, ObjectRef objectRef, ObjectPool *objectPool) {
    ObjectRef currentObjectRef = objectRef;
    while (currentObjectRef != 0) {
        Method *method = objectPool->getObject(currentObjectRef)->classFile->methodTable->getMethod(signature);
        if (method != nullptr) {
            return method;
        }
        currentObjectRef = objectPool->getObject(currentObjectRef)->parentRef;
    }

    throw MethodNotFoundException();
}

inline Method *lookupStaticMethod(const std::string &signature, ClassFile *classFile) {
    ClassFile *currentClassFile = classFile;
    while (currentClassFile != nullptr) {
        Method *method = currentClassFile->methodTable->getMethod(signature);
        if (method != nullptr) {
            return method;
        }
        currentClassFile = currentClassFile->superClassFile;
    }

    throw MethodNotFoundException();
}

#endif //BASIC_JVM_METHODLOOKUP_H
