//
// Created by Alan Ihre on 2020-09-10.
//

#ifndef LAB7_FIELDTABLE_H
#define LAB7_FIELDTABLE_H

#include <unordered_map>
#include "ClassFile.h"
#include "ByteTypes.h"
#include <string>

struct ClassFile;
struct field_info;

struct Field {
    std::string name;
    std::string descriptor;
    u2 accessFlags;
    ClassFile *classFile;
    int index;
    int staticValue = 0;
};


class FieldTable {
private:
    std::unordered_map<std::string, Field *> map;

public:
    explicit FieldTable(ClassFile *classFile);

    ~FieldTable();

    Field *getField(const std::string &signature);
};


#endif //LAB7_FIELDTABLE_H
