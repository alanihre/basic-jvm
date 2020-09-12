//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef BASIC_JVM_METHODTABLE_H
#define BASIC_JVM_METHODTABLE_H

#include <unordered_map>
#include "ClassFile.h"
#include "ByteTypes.h"
#include <string>

struct Code_attribute;
struct ClassFile;
struct method_info;

struct Method {
    std::string name;
    std::string descriptor;
    Code_attribute *codeAttribute;
    u2 accessFlags;
    int numArguments;
    ClassFile *classFile;
};


class MethodTable {
private:
    std::unordered_map<std::string, Method *> map;

public:
    explicit MethodTable(ClassFile *classFile);

    ~MethodTable();

    Method *getMethod(const std::string &signature);
};

int countArguments(const std::string &methodDescriptor);

#endif //BASIC_JVM_METHODTABLE_H
