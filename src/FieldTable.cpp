//
// Created by Alan Ihre on 2020-09-10.
//

#include "FieldTable.h"

Field *FieldTable::getField(const std::string &name) {
    auto it = map.find(name);
    if (it != map.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

FieldTable::FieldTable(ClassFile *classFile) {
    for (int i = 0; i < classFile->fields_count; ++i) {
        field_info fieldInfo = classFile->fields[i];

        auto *field = new Field();
        field->accessFlags = fieldInfo.access_flags;
        field->name = std::string(
                (char *) ((CONSTANT_Utf8_info *) classFile->constant_pool[fieldInfo.name_index - 1].info)->bytes);
        field->descriptor = std::string(
                (char *) ((CONSTANT_Utf8_info *) classFile->constant_pool[fieldInfo.descriptor_index - 1].info)->bytes);

        field->classFile = classFile;

        field->index = i;

        map.insert(std::pair<std::string, Field *>(field->name, field));
    }
}
