//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef LAB7_METHODTABLE_H
#define LAB7_METHODTABLE_H

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

    Method *getMethod(const std::string &signature);
};


#endif //LAB7_METHODTABLE_H
