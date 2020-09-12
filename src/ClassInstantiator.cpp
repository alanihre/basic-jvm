//
// Created by Alan Ihre on 2020-09-10.
//

#include "ClassInstantiator.h"

ClassInstantiator::ClassInstantiator(ClassFileLookup *classFileLookup, ObjectPool *objectPool) {
    this->classFileLookup = classFileLookup;
    this->objectPool = objectPool;
}

void ClassInstantiator::newInstance(const std::string &className, ObjectRef objectRef) {
    ClassFile *classFile = classFileLookup->getClassFile(className);
    ObjectRef parentRef = 0;

    if (classFile->super_class != 0) {
        std::string superClassName = classFile->superClassFile->className;

        parentRef = objectPool->newObjectRef();
        newInstance(superClassName, parentRef);
    }

    objectPool->getObject(objectRef)->initializeObject(classFile, parentRef);
}
