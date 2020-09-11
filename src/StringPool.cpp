//
// Created by Alan Ihre on 2020-09-08.
//

#include "StringPool.h"
#include "builtin/ArrayClassFile.h"

StringPool::StringPool(ObjectPool *objectPool, ClassFileLookup *classFileLookup, ClassInstantiator *classInstantiator) {
    this->objectPool = objectPool;
    this->classFileLookup = classFileLookup;
    this->classInstantiator = classInstantiator;
}

int StringPool::getStringInstanceRef(const std::string &value) {
    auto it = map.find(value);
    if (it != map.end()) {
        return it->second;
    } else {
        ObjectRef objectRef = objectPool->newObjectRef();
        ClassInstance *stringObject = classInstantiator->newInstance(std::string(BUILTIN_STRING_CLASS_NAME), objectRef);

        ObjectRef arrayRef = objectPool->newObjectRef();
        ClassInstance *arrayObject = objectPool->getObject(arrayRef);
        auto *arrayClassFile = classFileLookup->getClassFile(BUILTIN_ARRAY_CLASS_NAME);
        arrayObject->initializeArray(arrayClassFile, value.size());

        const char *cStrValue = value.c_str();

        for (int i = 0; i < strlen(cStrValue); ++i) {
            arrayObject->putArrayElement(i, cStrValue[i]);
        }

        stringObject->putField(0, arrayRef);

        map.insert(std::pair<std::string, int>(value, objectRef));
        return objectRef;
    }
}
