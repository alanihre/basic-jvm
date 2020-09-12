//
// Created by Alan Ihre on 2020-09-08.
//

#include "ObjectPool.h"

ObjectPool::ObjectPool() {
    size = 0;
    capacity = INITIAL_POOL_SIZE;
    objects = std::vector<ClassInstance>(capacity);
}

void ObjectPool::increaseSizeIfRequired() {
    if (size == capacity) {
        capacity += POOL_SIZE_CHUNK;
        objects.resize(capacity);
    }
}

ObjectRef ObjectPool::newObjectRef() {
    increaseSizeIfRequired();
    return size++ + REF_OFFSET;
}

ClassInstance *ObjectPool::getObject(ObjectRef ref) {
    ref -= REF_OFFSET;
    if (ref >= size) {
        throw InvalidObjectReferenceException();
    }
    return &objects[ref];
}
