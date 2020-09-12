//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef BASIC_JVM_STRINGPOOL_H
#define BASIC_JVM_STRINGPOOL_H

#include <unordered_map>
#include "builtin/StringClassFile.h"
#include "ObjectPool.h"
#include "ClassFileLookup.h"
#include <string>
#include "ClassInstantiator.h"

class StringPool {
private:
    std::unordered_map<std::string, ObjectRef> map;
    ObjectPool *objectPool;
    ClassFileLookup *classFileLookup;
    ClassInstantiator *classInstantiator;

public:
    explicit StringPool(ObjectPool *objectPool, ClassFileLookup *classFileLookup, ClassInstantiator *classInstantiator);

    ObjectRef getStringInstanceRef(const std::string &value);
};


#endif //BASIC_JVM_STRINGPOOL_H
