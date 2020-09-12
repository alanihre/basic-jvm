//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef LAB7_CLASSINSTANTIATOR_H
#define LAB7_CLASSINSTANTIATOR_H

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


#endif //LAB7_CLASSINSTANTIATOR_H
