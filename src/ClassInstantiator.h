//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef BASIC_JVM_CLASSINSTANTIATOR_H
#define BASIC_JVM_CLASSINSTANTIATOR_H

#include "ClassFileLookup.h"
#include "ClassInstance.h"
#include "ObjectPool.h"

class ClassInstantiator {
private:
    ClassFileLookup *classFileLookup;
    ObjectPool *objectPool;

public:
    explicit ClassInstantiator(ClassFileLookup *classFileLookup, ObjectPool *objectPool);

    void newInstance(const std::string &className, ObjectRef objectRef);
};


#endif //BASIC_JVM_CLASSINSTANTIATOR_H
