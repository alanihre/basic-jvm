//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef LAB7_OBJECTCLASSFILE_H
#define LAB7_OBJECTCLASSFILE_H

#include "../Instructions.h"

#define MAGIC 3405691582
#define BUILTIN_OBJECT_CLASS_NAME "java/lang/Object"
#define INIT_METHOD_NAME "<init>"
#define DEFAULT_INIT_METHOD_SIGNATURE "()V"

struct ObjectClassFile : public ClassFile {
    ObjectClassFile() : ClassFile() {
        magic = MAGIC;
        minor_version = 0;
        major_version = 49;
        access_flags = ACC_PUBLIC;
        this_class = 2;
        super_class = 0;
        interfaces_count = 0;
        attributes_count = 0;
        fields_count = 0;

        constant_pool_count = 5;
        constant_pool = new cp_info[constant_pool_count];

        const char* thisClassUtf8 = BUILTIN_OBJECT_CLASS_NAME;
        cp_info* thisClassUtf8CpEntry = &constant_pool[0];
        thisClassUtf8CpEntry->tag = CONSTANT_TYPE_UTF8;
        thisClassUtf8CpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto* thisClassUtf8CpInfo = (CONSTANT_Utf8_info*)thisClassUtf8CpEntry->info;
        size_t thisClassStrLen = strlen(thisClassUtf8) + 1;
        thisClassUtf8CpInfo->length = thisClassStrLen;
        thisClassUtf8CpInfo->bytes = new u1[thisClassUtf8CpInfo->length];
        strcpy((char*) thisClassUtf8CpInfo->bytes, thisClassUtf8);
        thisClassUtf8CpInfo->bytes[thisClassStrLen - 1] = '\0';

        cp_info* thisClassClassCpEntry = &constant_pool[1];
        thisClassClassCpEntry->tag = CONSTANT_TYPE_CLASS;
        thisClassClassCpEntry->info = new u1[sizeof(CONSTANT_Class_info)];
        auto* thisClassClassCpInfo = (CONSTANT_Class_info*)thisClassClassCpEntry->info;
        thisClassClassCpInfo->name_index = 2;

        const char* initMethodNameUtf8 = INIT_METHOD_NAME;
        cp_info* initMethodNameUtf8Entry = &constant_pool[2];
        initMethodNameUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodNameUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto* initMethodNameUtf8Info = (CONSTANT_Utf8_info*)initMethodNameUtf8Entry->info;
        size_t initMethodNameStrLen = strlen(initMethodNameUtf8) + 1;
        initMethodNameUtf8Info->length = initMethodNameStrLen;
        initMethodNameUtf8Info->bytes = new u1[initMethodNameUtf8Info->length];
        strcpy((char*) initMethodNameUtf8Info->bytes, initMethodNameUtf8);
        initMethodNameUtf8Info->bytes[initMethodNameStrLen - 1] = '\0';

        const char* initMethodSignatureUtf8 = DEFAULT_INIT_METHOD_SIGNATURE;
        cp_info* initMethodSignatureUtf8Entry = &constant_pool[3];
        initMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto* initMethodSignatureUtf8Info = (CONSTANT_Utf8_info*)initMethodSignatureUtf8Entry->info;
        size_t initMethodSignatureStrLen = strlen(initMethodSignatureUtf8) + 1;
        initMethodSignatureUtf8Info->length = initMethodSignatureStrLen;
        initMethodSignatureUtf8Info->bytes = new u1[initMethodSignatureUtf8Info->length];
        strcpy((char*) initMethodSignatureUtf8Info->bytes, initMethodSignatureUtf8);
        initMethodSignatureUtf8Info->bytes[initMethodSignatureStrLen - 1] = '\0';

        const char* codeUtf8 = ATTRIBUTE_TYPE_CODE;
        cp_info* codeUtf8Entry = &constant_pool[4];
        codeUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        codeUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto* codeUtf8Info = (CONSTANT_Utf8_info*)codeUtf8Entry->info;
        size_t codeStrLen = strlen(codeUtf8) + 1;
        codeUtf8Info->length = codeStrLen;
        codeUtf8Info->bytes = new u1[codeUtf8Info->length];
        strcpy((char*) codeUtf8Info->bytes, codeUtf8);
        codeUtf8Info->bytes[codeStrLen - 1] = '\0';

        methods_count = 1;
        methods = new method_info[methods_count];

        method_info* initMethod = &methods[0];
        initMethod->access_flags = ACC_PUBLIC;
        initMethod->name_index = 3;
        initMethod->descriptor_index = 4;
        initMethod->attributes_count = 1;
        initMethod->attributes = new attribute_info[initMethod->attributes_count];
        attribute_info* initMethodCodeAttr = &initMethod->attributes[0];
        initMethodCodeAttr->attribute_name_index = 5;

        auto* codeAttr = new Code_attribute();
        codeAttr->max_stack = 0;
        codeAttr->max_locals = 0;
        codeAttr->code_length = 1;
        codeAttr->code = new u1[codeAttr->code_length];
        codeAttr->code[0] = RETURN;
        codeAttr->exception_table_length = 0;
        codeAttr->attributes_count = 0;
        initMethodCodeAttr->attribute_length = sizeof(Code_attribute) + sizeof(u1) * codeAttr->code_length;
        initMethodCodeAttr->info = (u1*) codeAttr;

        char* classNameChar = new char[thisClassUtf8CpInfo->length];
        strcpy(classNameChar, (char*)thisClassUtf8CpInfo->bytes);
        className = std::string(classNameChar);

        methodTable = new MethodTable(this);
        fieldTable = new FieldTable(this);
    }
};

#endif //LAB7_CLASSINSTANCE_H
