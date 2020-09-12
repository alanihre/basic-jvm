//
// Created by Alan Ihre on 2020-09-11.
//

#ifndef BASIC_JVM_SYSTEMCLASSFILE_H
#define BASIC_JVM_SYSTEMCLASSFILE_H

#include "../ClassFile.h"
#include "ObjectClassFile.h"

#define BUILTIN_SYSTEM_CLASS_NAME "java/lang/System"
#define BUILTIN_SYSTEM_CLASS_OUT_FIELD "out"

struct SystemClassFile : public ClassFile {
    SystemClassFile() : ClassFile() {
        magic = MAGIC;
        minor_version = 0;
        major_version = 49;
        access_flags = ACC_PUBLIC | ACC_FINAL; // NOLINT(hicpp-signed-bitwise)
        this_class = 4;
        super_class = 6;
        interfaces_count = 0;
        methods_count = 0;
        attributes_count = 0;

        constant_pool_count = 12;
        constant_pool = new cp_info[constant_pool_count];

        const char *valueFieldName = BUILTIN_SYSTEM_CLASS_OUT_FIELD;
        cp_info *valueFieldNameCpEntry = &constant_pool[0];
        valueFieldNameCpEntry->tag = CONSTANT_TYPE_UTF8;
        valueFieldNameCpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *valueFieldNameCpInfo = (CONSTANT_Utf8_info *) valueFieldNameCpEntry->info;
        size_t valueFieldNameStrLen = strlen(valueFieldName) + 1;
        valueFieldNameCpInfo->length = valueFieldNameStrLen;
        valueFieldNameCpInfo->bytes = new u1[valueFieldNameCpInfo->length];
        strcpy((char *) valueFieldNameCpInfo->bytes, valueFieldName);
        valueFieldNameCpInfo->bytes[valueFieldNameStrLen - 1] = '\0';

        const char *valueFieldType = "Ljava/io/PrintStream;";
        cp_info *valueFieldTypeCpEntry = &constant_pool[1];
        valueFieldTypeCpEntry->tag = CONSTANT_TYPE_UTF8;
        valueFieldTypeCpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *valueFieldTypeCpInfo = (CONSTANT_Utf8_info *) valueFieldTypeCpEntry->info;
        size_t valueFieldTypeStrLen = strlen(valueFieldType) + 1;
        valueFieldTypeCpInfo->length = valueFieldTypeStrLen;
        valueFieldTypeCpInfo->bytes = new u1[valueFieldTypeCpInfo->length];
        strcpy((char *) valueFieldTypeCpInfo->bytes, valueFieldType);
        valueFieldTypeCpInfo->bytes[valueFieldTypeStrLen - 1] = '\0';

        const char *thisClassUtf8 = BUILTIN_SYSTEM_CLASS_NAME;
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

        const char *superClassUtf8 = BUILTIN_OBJECT_CLASS_NAME;
        cp_info *superClassUtf8CpEntry = &constant_pool[4];
        superClassUtf8CpEntry->tag = CONSTANT_TYPE_UTF8;
        superClassUtf8CpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *superClassUtf8CpInfo = (CONSTANT_Utf8_info *) superClassUtf8CpEntry->info;
        size_t superClassStrLen = strlen(superClassUtf8) + 1;
        superClassUtf8CpInfo->length = superClassStrLen;
        superClassUtf8CpInfo->bytes = new u1[superClassUtf8CpInfo->length];
        strcpy((char *) superClassUtf8CpInfo->bytes, superClassUtf8);
        superClassUtf8CpInfo->bytes[superClassStrLen - 1] = '\0';

        cp_info *superClassClassCpEntry = &constant_pool[5];
        superClassClassCpEntry->tag = CONSTANT_TYPE_CLASS;
        superClassClassCpEntry->info = new u1[sizeof(CONSTANT_Class_info)];
        auto *superClassClassCpInfo = (CONSTANT_Class_info *) superClassClassCpEntry->info;
        superClassClassCpInfo->name_index = 5;

        const char *initMethodNameUtf8 = INIT_METHOD_NAME;
        cp_info *initMethodNameUtf8Entry = &constant_pool[6];
        initMethodNameUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodNameUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *initMethodNameUtf8Info = (CONSTANT_Utf8_info *) initMethodNameUtf8Entry->info;
        size_t initMethodNameStrLen = strlen(initMethodNameUtf8) + 1;
        initMethodNameUtf8Info->length = initMethodNameStrLen;
        initMethodNameUtf8Info->bytes = new u1[initMethodNameUtf8Info->length];
        strcpy((char *) initMethodNameUtf8Info->bytes, initMethodNameUtf8);
        initMethodNameUtf8Info->bytes[initMethodNameStrLen - 1] = '\0';

        const char *initMethodSignatureUtf8 = DEFAULT_INIT_METHOD_SIGNATURE;
        cp_info *initMethodSignatureUtf8Entry = &constant_pool[7];
        initMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *initMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) initMethodSignatureUtf8Entry->info;
        size_t initMethodSignatureStrLen = strlen(initMethodSignatureUtf8) + 1;
        initMethodSignatureUtf8Info->length = initMethodSignatureStrLen;
        initMethodSignatureUtf8Info->bytes = new u1[initMethodSignatureUtf8Info->length];
        strcpy((char *) initMethodSignatureUtf8Info->bytes, initMethodSignatureUtf8);
        initMethodSignatureUtf8Info->bytes[initMethodSignatureStrLen - 1] = '\0';

        const char *codeUtf8 = ATTRIBUTE_TYPE_CODE;
        cp_info *codeUtf8Entry = &constant_pool[8];
        codeUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        codeUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *codeUtf8Info = (CONSTANT_Utf8_info *) codeUtf8Entry->info;
        size_t codeStrLen = strlen(codeUtf8) + 1;
        codeUtf8Info->length = codeStrLen;
        codeUtf8Info->bytes = new u1[codeUtf8Info->length];
        strcpy((char *) codeUtf8Info->bytes, codeUtf8);
        codeUtf8Info->bytes[codeStrLen - 1] = '\0';

        methods_count = 1;
        methods = new method_info[methods_count];

        method_info *initMethod = &methods[0];
        initMethod->access_flags = ACC_PRIVATE;
        initMethod->name_index = 7;
        initMethod->descriptor_index = 8;
        initMethod->attributes_count = 1;
        initMethod->attributes = new attribute_info[initMethod->attributes_count];
        attribute_info *initMethodCodeAttr = &initMethod->attributes[0];
        initMethodCodeAttr->attribute_name_index = 9;

        auto *codeAttr = new Code_attribute();
        codeAttr->max_stack = 0;
        codeAttr->max_locals = 0;
        codeAttr->code_length = 5;
        codeAttr->code = new u1[codeAttr->code_length];
        codeAttr->code[0] = ALOAD_0;
        codeAttr->code[1] = INVOKE_SPECIAL;
        codeAttr->code[2] = 0;
        codeAttr->code[3] = 11;
        codeAttr->code[4] = RETURN;
        codeAttr->exception_table_length = 0;
        codeAttr->attributes_count = 0;
        initMethodCodeAttr->attribute_length = sizeof(Code_attribute) + sizeof(u1) * codeAttr->code_length;
        initMethodCodeAttr->info = (u1 *) codeAttr;

        cp_info *superInitMethodRefNameAndTypeEntry = &constant_pool[9];
        superInitMethodRefNameAndTypeEntry->tag = CONSTANT_TYPE_NAME_AND_TYPE;
        superInitMethodRefNameAndTypeEntry->info = new u1[sizeof(CONSTANT_NameAndType_info)];
        auto *superInitMethodRefNameAndTypeInfo = (CONSTANT_NameAndType_info *) superInitMethodRefNameAndTypeEntry->info;
        superInitMethodRefNameAndTypeInfo->name_index = 7;
        superInitMethodRefNameAndTypeInfo->descriptor_index = 12;

        cp_info *superInitMethodRefEntry = &constant_pool[10];
        superInitMethodRefEntry->tag = CONSTANT_TYPE_FIELD_REF;
        superInitMethodRefEntry->info = new u1[sizeof(CONSTANT_Methodref_info)];
        auto *superInitMethodRefInfo = (CONSTANT_Methodref_info *) superInitMethodRefEntry->info;
        superInitMethodRefInfo->class_index = 6;
        superInitMethodRefInfo->name_and_type_index = 10;

        const char *superInitMethodSignatureUtf8 = DEFAULT_INIT_METHOD_SIGNATURE;
        cp_info *superInitMethodSignatureUtf8Entry = &constant_pool[11];
        superInitMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        superInitMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *superInitMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) superInitMethodSignatureUtf8Entry->info;
        size_t superInitMethodSignatureStrLen = strlen(superInitMethodSignatureUtf8) + 1;
        superInitMethodSignatureUtf8Info->length = superInitMethodSignatureStrLen;
        superInitMethodSignatureUtf8Info->bytes = new u1[superInitMethodSignatureUtf8Info->length];
        strcpy((char *) superInitMethodSignatureUtf8Info->bytes, superInitMethodSignatureUtf8);
        superInitMethodSignatureUtf8Info->bytes[superInitMethodSignatureStrLen - 1] = '\0';

        fields_count = 1;
        fields = new field_info[fields_count];
        field_info *valueField = &fields[0];
        valueField->access_flags = ACC_PUBLIC | ACC_STATIC | ACC_FINAL; // NOLINT(hicpp-signed-bitwise)
        valueField->name_index = 1;
        valueField->descriptor_index = 2;

        char *classNameChar = new char[thisClassUtf8CpInfo->length];
        strcpy(classNameChar, (char *) thisClassUtf8CpInfo->bytes);
        className = std::string(classNameChar);

        methodTable = new MethodTable(this);
        fieldTable = new FieldTable(this);
    }
};

#endif //BASIC_JVM_SYSTEMCLASSFILE_H
