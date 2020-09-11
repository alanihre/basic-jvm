//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef LAB7_STRINGPOOL_H
#define LAB7_STRINGPOOL_H

#include <unordered_map>
#include "builtin/StringClassFile.h"
#include "ObjectPool.h"
#include "ClassFileLookup.h"
#include <string>
#include "ClassInstantiator.h"

class StringPool {
private:
    std::unordered_map<std::string, int> map;
    ObjectPool *objectPool;
    ClassFileLookup *classFileLookup;
    ClassInstantiator *classInstantiator;

public:
    explicit StringPool(ObjectPool *objectPool, ClassFileLookup *classFileLookup, ClassInstantiator *classInstantiator);
    int getStringInstanceRef(const std::string& value);
};


#endif //LAB7_STRINGPOOL_H
