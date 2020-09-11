
//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef LAB7_OBJECTPOOL_H
#define LAB7_OBJECTPOOL_H

#include <unordered_map>
#include "ClassInstance.h"

#define INITIAL_POOL_SIZE 100
#define POOL_SIZE_CHUNK 100
#define REF_OFFSET 1

typedef int ObjectRef;

class ObjectPool {
private:
    ClassInstance *objects;
    int size;
    int capacity;

    void increaseSizeIfRequired();

public:
    ObjectPool();

    ~ObjectPool();

    int newObjectRef();

    ClassInstance *getObject(int ref);
};

class InvalidObjectReferenceException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Invalid object reference";
    }
};


#endif //LAB7_OBJECTPOOL_H
