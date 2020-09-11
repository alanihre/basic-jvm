//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef LAB7_METHODLOOKUP_H
#define LAB7_METHODLOOKUP_H

#include "MethodTable.h"
#include "ClassInstance.h"

class MethodNotFoundException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Method not found";
    }
};

inline Method *lookupMethod(const std::string &signature, ClassFile *classFile) {
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

#endif //LAB7_METHODLOOKUP_H
