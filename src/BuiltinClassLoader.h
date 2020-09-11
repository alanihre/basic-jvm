//
// Created by Alan Ihre on 2020-09-11.
//

#ifndef LAB7_BUILTINCLASSLOADER_H
#define LAB7_BUILTINCLASSLOADER_H

#include "builtin/StringClassFile.h"
#include "builtin/ObjectClassFile.h"
#include "builtin/ArrayClassFile.h"
#include "builtin/SystemClassFile.h"
#include "builtin/PrintStreamClassFile.h"
#include "ClassFileLookup.h"
#include "ObjectPool.h"
#include "ClassInstantiator.h"
#include "ClassInstance.h"
#include "FieldLookup.h"

inline void
loadBuiltinClasses(ClassFileLookup *classFileLookup, ObjectPool *objectPool, ClassInstantiator *classInstantiator) {
    auto *objectClassFile = new ObjectClassFile();
    classFileLookup->insertClassFile(BUILTIN_OBJECT_CLASS_NAME, objectClassFile);

    auto *stringClassFile = new StringClassFile();
    stringClassFile->superClassFile = objectClassFile;
    classFileLookup->insertClassFile(BUILTIN_STRING_CLASS_NAME, stringClassFile);

    auto *arrayClassFile = new ArrayClassFile();
    classFileLookup->insertClassFile(BUILTIN_ARRAY_CLASS_NAME, arrayClassFile);

    auto *systemClassFile = new SystemClassFile();
    systemClassFile->superClassFile = objectClassFile;
    classFileLookup->insertClassFile(BUILTIN_SYSTEM_CLASS_NAME, systemClassFile);

    auto *printStreamClassFile = new PrintStreamClassFile();
    printStreamClassFile->superClassFile = objectClassFile;
    classFileLookup->insertClassFile(BUILTIN_PRINT_STREAM_CLASS_NAME, printStreamClassFile);

    ObjectRef stdoutPrintStreamRef = objectPool->newObjectRef();
    ClassInstance *stdoutPrintStream = classInstantiator->newInstance(BUILTIN_PRINT_STREAM_CLASS_NAME,
                                                                      stdoutPrintStreamRef);

    Field *field = lookupStaticField(BUILTIN_SYSTEM_CLASS_OUT_FIELD, systemClassFile);
    field->staticValue = stdoutPrintStreamRef;
}

#endif //LAB7_BUILTINCLASSLOADER_H
