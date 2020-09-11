//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef LAB7_FIELDLOOKUP_H
#define LAB7_FIELDLOOKUP_H

#include "FieldTable.h"
#include "ClassInstance.h"

class FieldNotFoundException: public std::exception
{
public:
    virtual const char* what() const throw() {
        return "Field not found";
    }
};


inline Field* lookupField(const std::string& name, ClassInstance *classInstance, ClassInstance **resultClassInstance) {
    ClassInstance *currentInstance = classInstance;
    while (currentInstance != nullptr) {
        Field* field = currentInstance->classFile->fieldTable->getField(name);
        if (field != nullptr) {
            *resultClassInstance = currentInstance;
            return field;
        }
        currentInstance = currentInstance->parentInstance;
    }

    throw FieldNotFoundException();
}

inline Field* lookupStaticField(const std::string& name, ClassFile *classFile) {
    ClassFile *currentClassFile = classFile;
    while (currentClassFile != nullptr) {
        Field* field = currentClassFile->fieldTable->getField(name);
        if (field != nullptr) {
            return field;
        }
        currentClassFile = currentClassFile->superClassFile;
    }

    throw FieldNotFoundException();
}

#endif //LAB7_FIELDLOOKUP_H
