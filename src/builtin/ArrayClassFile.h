//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef LAB7_ARRAYCLASSFILE_H
#define LAB7_ARRAYCLASSFILE_H

#include "../ClassFile.h"
#include "ObjectClassFile.h"

#define BUILTIN_ARRAY_CLASS_NAME "array"

struct ArrayClassFile : public ClassFile {
    ArrayClassFile() : ClassFile() {
        magic = MAGIC;
        minor_version = 0;
        major_version = 49;
        access_flags = ACC_PUBLIC;
        this_class = 4;
        super_class = 0;
        interfaces_count = 0;
        methods_count = 0;
        //method_info*   methods;
        attributes_count = 0;
        //attribute_info* attributes;

        constant_pool_count = 9;
        constant_pool = new cp_info[constant_pool_count];

        const char *lengthFieldName = "length";
        cp_info *lengthFieldNameCpEntry = &constant_pool[0];
        lengthFieldNameCpEntry->tag = CONSTANT_TYPE_UTF8;
        lengthFieldNameCpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *lengthFieldNameCpInfo = (CONSTANT_Utf8_info *) lengthFieldNameCpEntry->info;
        size_t lengthFieldNameStrLen = strlen(lengthFieldName) + 1;
        lengthFieldNameCpInfo->length = lengthFieldNameStrLen;
        lengthFieldNameCpInfo->bytes = new u1[lengthFieldNameCpInfo->length];
        strcpy((char *) lengthFieldNameCpInfo->bytes, lengthFieldName);
        lengthFieldNameCpInfo->bytes[lengthFieldNameStrLen - 1] = '\0';

        const char *lengthFieldType = "I";
        cp_info *lengthFieldTypeCpEntry = &constant_pool[1];
        lengthFieldTypeCpEntry->tag = CONSTANT_TYPE_UTF8;
        lengthFieldTypeCpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *lengthFieldTypeCpInfo = (CONSTANT_Utf8_info *) lengthFieldTypeCpEntry->info;
        size_t lengthFieldTypeStrLen = strlen(lengthFieldType) + 1;
        lengthFieldTypeCpInfo->length = lengthFieldTypeStrLen;
        lengthFieldTypeCpInfo->bytes = new u1[lengthFieldTypeCpInfo->length];
        strcpy((char *) lengthFieldTypeCpInfo->bytes, lengthFieldType);
        lengthFieldTypeCpInfo->bytes[lengthFieldTypeStrLen - 1] = '\0';

        const char *thisClassUtf8 = BUILTIN_ARRAY_CLASS_NAME;
        cp_info *thisClassUtf8CpEntry = &constant_pool[2];
        thisClassUtf8CpEntry->tag = CONSTANT_TYPE_UTF8;
        thisClassUtf8CpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *thisClassUtf8CpInfo = (CONSTANT_Utf8_info *) thisClassUtf8CpEntry->info;
        size_t thisClassStrLen = strlen(thisClassUtf8) + 1;
        thisClassUtf8CpInfo->length = thisClassStrLen;
        thisClassUtf8CpInfo->bytes = new u1[thisClassUtf8CpInfo->length];
        strcpy((char *) thisClassUtf8CpInfo->bytes, thisClassUtf8);
        thisClassUtf8CpInfo->bytes[thisClassStrLen - 1] = '\0';

        cp_info *thisClassClassCpEntry = &constant_pool[3];
        thisClassClassCpEntry->tag = CONSTANT_TYPE_CLASS;
        thisClassClassCpEntry->info = new u1[sizeof(CONSTANT_Class_info)];
        auto *thisClassClassCpInfo = (CONSTANT_Class_info *) thisClassClassCpEntry->info;
        thisClassClassCpInfo->name_index = 3;

        fields_count = 1;
        fields = new field_info[fields_count];
        field_info *valueField = &fields[0];
        valueField->access_flags = ACC_PRIVATE;
        valueField->name_index = 1;
        valueField->descriptor_index = 2;

        char *classNameChar = new char[thisClassUtf8CpInfo->length];
        strcpy(classNameChar, (char *) thisClassUtf8CpInfo->bytes);
        className = std::string(classNameChar);

        methodTable = new MethodTable(this);
        fieldTable = new FieldTable(this);
    }
};


#endif //LAB7_ARRAYCLASSFILE_H
