//
// Created by Alan Ihre on 2020-09-10.
//

#include "ClassInstantiator.h"

ClassInstantiator::ClassInstantiator(ClassFileLookup *classFileLookup, ObjectPool *objectPool) {
    this->classFileLookup = classFileLookup;
    this->objectPool = objectPool;
}

ClassInstance *ClassInstantiator::newInstance(const std::string &className, ObjectRef objectRef) {
    ClassInstance *classInstance = objectPool->getObject(objectRef);

    ClassFile *classFile = classFileLookup->getClassFile(className);
    ClassInstance *parentInstance = nullptr;

    if (classFile->super_class != 0) {
        std::string superClassName = classFile->superClassFile->className;

        int superObjectRef = objectPool->newObjectRef();
        parentInstance = newInstance(superClassName, superObjectRef);
    }

    classInstance->initializeObject(classFile, parentInstance);

    return classInstance;
}
