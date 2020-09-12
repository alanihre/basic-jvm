//
// Created by Alan Ihre on 2020-09-08.
//

#include "StringPool.h"
#include "builtin/ArrayClassFile.h"
#include "FieldLookup.h"

StringPool::StringPool(ObjectPool *objectPool, ClassFileLookup *classFileLookup, ClassInstantiator *classInstantiator) {
    this->objectPool = objectPool;
    this->classFileLookup = classFileLookup;
    this->classInstantiator = classInstantiator;
}

ObjectRef StringPool::getStringInstanceRef(const std::string &value) {
    auto it = map.find(value);
    if (it != map.end()) {
        return it->second;
    } else {
        ObjectRef stringObjectRef = objectPool->newObjectRef();
        classInstantiator->newInstance(std::string(BUILTIN_STRING_CLASS_NAME), stringObjectRef);

        ObjectRef arrayRef = objectPool->newObjectRef();
        auto *arrayClassFile = classFileLookup->getClassFile(BUILTIN_ARRAY_CLASS_NAME);
        objectPool->getObject(arrayRef)->initializeArray(arrayClassFile, value.size());

        const char *cStrValue = value.c_str();

        for (int i = 0; i < strlen(cStrValue); ++i) {
            objectPool->getObject(arrayRef)->putArrayElement(i, cStrValue[i]);
        }

        ObjectRef resultObjectRef = 0;

        Field *field = lookupField(BUILTIN_STRING_CLASS_VALUE_FIELD, "String", stringObjectRef, &resultObjectRef, objectPool);

        objectPool->getObject(resultObjectRef)->putField(field->index, arrayRef);

        map.insert(std::pair<std::string, ObjectRef>(value, stringObjectRef));
        return stringObjectRef;
    }
}
