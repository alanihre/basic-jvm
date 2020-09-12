//
// Created by Alan Ihre on 2020-09-11.
//

#ifndef LAB7_STRINGBUILDERCLASSFILE_H
#define LAB7_STRINGBUILDERCLASSFILE_H

#include "../ClassFile.h"
#include "ObjectClassFile.h"

#define BUILTIN_STRING_BUILDER_CLASS_NAME "java/lang/StringBuilder"

struct StringBuilderClassFile : public ClassFile {
    StringBuilderClassFile() : ClassFile() {
        magic = MAGIC;
        minor_version = 0;
        major_version = 49;
        access_flags = ACC_PUBLIC;
        this_class = 2;
        super_class = 4;
        interfaces_count = 0;
        attributes_count = 0;
        //attribute_info* attributes;
        fields_count = 0;

        constant_pool_count = 19;
        constant_pool = new cp_info[constant_pool_count];

        const char *thisClassUtf8 = BUILTIN_STRING_BUILDER_CLASS_NAME;
        cp_info *thisClassUtf8CpEntry = &constant_pool[0];
        thisClassUtf8CpEntry->tag = CONSTANT_TYPE_UTF8;
        thisClassUtf8CpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *thisClassUtf8CpInfo = (CONSTANT_Utf8_info *) thisClassUtf8CpEntry->info;
        size_t thisClassStrLen = strlen(thisClassUtf8) + 1;
        thisClassUtf8CpInfo->length = thisClassStrLen;
        thisClassUtf8CpInfo->bytes = new u1[thisClassUtf8CpInfo->length];
        strcpy((char *) thisClassUtf8CpInfo->bytes, thisClassUtf8);
        thisClassUtf8CpInfo->bytes[thisClassStrLen - 1] = '\0';

        cp_info *thisClassClassCpEntry = &constant_pool[1];
        thisClassClassCpEntry->tag = CONSTANT_TYPE_CLASS;
        thisClassClassCpEntry->info = new u1[sizeof(CONSTANT_Class_info)];
        auto *thisClassClassCpInfo = (CONSTANT_Class_info *) thisClassClassCpEntry->info;
        thisClassClassCpInfo->name_index = 1;

        const char *superClassUtf8 = "StringBuilder";
        cp_info *superClassUtf8CpEntry = &constant_pool[2];
        superClassUtf8CpEntry->tag = CONSTANT_TYPE_UTF8;
        superClassUtf8CpEntry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *superClassUtf8CpInfo = (CONSTANT_Utf8_info *) superClassUtf8CpEntry->info;
        size_t superClassStrLen = strlen(superClassUtf8) + 1;
        superClassUtf8CpInfo->length = superClassStrLen;
        superClassUtf8CpInfo->bytes = new u1[superClassUtf8CpInfo->length];
        strcpy((char *) superClassUtf8CpInfo->bytes, superClassUtf8);
        superClassUtf8CpInfo->bytes[superClassStrLen - 1] = '\0';

        cp_info *superClassClassCpEntry = &constant_pool[3];
        superClassClassCpEntry->tag = CONSTANT_TYPE_CLASS;
        superClassClassCpEntry->info = new u1[sizeof(CONSTANT_Class_info)];
        auto *superClassClassCpInfo = (CONSTANT_Class_info *) superClassClassCpEntry->info;
        superClassClassCpInfo->name_index = 3;

        const char *initMethodNameUtf8 = INIT_METHOD_NAME;
        cp_info *initMethodNameUtf8Entry = &constant_pool[4];
        initMethodNameUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodNameUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *initMethodNameUtf8Info = (CONSTANT_Utf8_info *) initMethodNameUtf8Entry->info;
        size_t initMethodNameStrLen = strlen(initMethodNameUtf8) + 1;
        initMethodNameUtf8Info->length = initMethodNameStrLen;
        initMethodNameUtf8Info->bytes = new u1[initMethodNameUtf8Info->length];
        strcpy((char *) initMethodNameUtf8Info->bytes, initMethodNameUtf8);
        initMethodNameUtf8Info->bytes[initMethodNameStrLen - 1] = '\0';

        const char *initMethodSignatureUtf8 = DEFAULT_INIT_METHOD_SIGNATURE;
        cp_info *initMethodSignatureUtf8Entry = &constant_pool[5];
        initMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        initMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *initMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) initMethodSignatureUtf8Entry->info;
        size_t initMethodSignatureStrLen = strlen(initMethodSignatureUtf8) + 1;
        initMethodSignatureUtf8Info->length = initMethodSignatureStrLen;
        initMethodSignatureUtf8Info->bytes = new u1[initMethodSignatureUtf8Info->length];
        strcpy((char *) initMethodSignatureUtf8Info->bytes, initMethodSignatureUtf8);
        initMethodSignatureUtf8Info->bytes[initMethodSignatureStrLen - 1] = '\0';

        const char *codeUtf8 = ATTRIBUTE_TYPE_CODE;
        cp_info *codeUtf8Entry = &constant_pool[6];
        codeUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        codeUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *codeUtf8Info = (CONSTANT_Utf8_info *) codeUtf8Entry->info;
        size_t codeStrLen = strlen(codeUtf8) + 1;
        codeUtf8Info->length = codeStrLen;
        codeUtf8Info->bytes = new u1[codeUtf8Info->length];
        strcpy((char *) codeUtf8Info->bytes, codeUtf8);
        codeUtf8Info->bytes[codeStrLen - 1] = '\0';

        methods_count = 3;
        methods = new method_info[methods_count];

        method_info *initMethod = &methods[0];
        initMethod->access_flags = ACC_PUBLIC;
        initMethod->name_index = 5;
        initMethod->descriptor_index = 6;
        initMethod->attributes_count = 1;
        initMethod->attributes = new attribute_info[initMethod->attributes_count];
        attribute_info *initMethodCodeAttr = &initMethod->attributes[0];
        initMethodCodeAttr->attribute_name_index = 7;

        auto *codeAttr = new Code_attribute();
        codeAttr->max_stack = 0;
        codeAttr->max_locals = 0;
        codeAttr->code_length = 5;
        codeAttr->code = new u1[codeAttr->code_length];
        codeAttr->code[0] = ALOAD_0;
        codeAttr->code[1] = INVOKE_SPECIAL;
        codeAttr->code[2] = 0;
        codeAttr->code[3] = 9;
        codeAttr->code[4] = RETURN;
        codeAttr->exception_table_length = 0;
        codeAttr->attributes_count = 0;
        initMethodCodeAttr->attribute_length = sizeof(Code_attribute) + sizeof(u1) * codeAttr->code_length;
        initMethodCodeAttr->info = (u1 *) codeAttr;

        cp_info *superInitMethodRefNameAndTypeEntry = &constant_pool[7];
        superInitMethodRefNameAndTypeEntry->tag = CONSTANT_TYPE_NAME_AND_TYPE;
        superInitMethodRefNameAndTypeEntry->info = new u1[sizeof(CONSTANT_NameAndType_info)];
        auto *superInitMethodRefNameAndTypeInfo = (CONSTANT_NameAndType_info *) superInitMethodRefNameAndTypeEntry->info;
        superInitMethodRefNameAndTypeInfo->name_index = 5;
        superInitMethodRefNameAndTypeInfo->descriptor_index = 10;

        cp_info *superInitMethodRefEntry = &constant_pool[8];
        superInitMethodRefEntry->tag = CONSTANT_TYPE_FIELD_REF;
        superInitMethodRefEntry->info = new u1[sizeof(CONSTANT_Methodref_info)];
        auto *superInitMethodRefInfo = (CONSTANT_Methodref_info *) superInitMethodRefEntry->info;
        superInitMethodRefInfo->class_index = 4;
        superInitMethodRefInfo->name_and_type_index = 8;

        const char *superInitMethodSignatureUtf8 = DEFAULT_INIT_METHOD_SIGNATURE;
        cp_info *superInitMethodSignatureUtf8Entry = &constant_pool[9];
        superInitMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        superInitMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *superInitMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) superInitMethodSignatureUtf8Entry->info;
        size_t superInitMethodSignatureStrLen = strlen(superInitMethodSignatureUtf8) + 1;
        superInitMethodSignatureUtf8Info->length = superInitMethodSignatureStrLen;
        superInitMethodSignatureUtf8Info->bytes = new u1[superInitMethodSignatureUtf8Info->length];
        strcpy((char *) superInitMethodSignatureUtf8Info->bytes, superInitMethodSignatureUtf8);
        superInitMethodSignatureUtf8Info->bytes[superInitMethodSignatureStrLen - 1] = '\0';



        method_info *appendStrMethod = &methods[1];
        appendStrMethod->access_flags = ACC_PUBLIC;
        appendStrMethod->name_index = 14;
        appendStrMethod->descriptor_index = 15;
        appendStrMethod->attributes_count = 1;
        appendStrMethod->attributes = new attribute_info[appendStrMethod->attributes_count];
        attribute_info *appendStrMethodCodeAttr = &appendStrMethod->attributes[0];
        appendStrMethodCodeAttr->attribute_name_index = 7;

        auto *appendStrCodeAttr = new Code_attribute();
        appendStrCodeAttr->max_stack = 0;
        appendStrCodeAttr->max_locals = 0;
        appendStrCodeAttr->code_length = 6;
        appendStrCodeAttr->code = new u1[appendStrCodeAttr->code_length];
        appendStrCodeAttr->code[0] = ALOAD_0;
        appendStrCodeAttr->code[1] = ALOAD_1;
        appendStrCodeAttr->code[2] = INVOKE_VIRTUAL;
        appendStrCodeAttr->code[3] = 0;
        appendStrCodeAttr->code[4] = 12;
        appendStrCodeAttr->code[5] = ARETURN;
        appendStrCodeAttr->exception_table_length = 0;
        appendStrCodeAttr->attributes_count = 0;
        appendStrMethodCodeAttr->attribute_length = sizeof(Code_attribute) + sizeof(u1) * appendStrCodeAttr->code_length;
        appendStrMethodCodeAttr->info = (u1 *) appendStrCodeAttr;

        cp_info *appendStrMethodRefNameAndTypeEntry = &constant_pool[10];
        appendStrMethodRefNameAndTypeEntry->tag = CONSTANT_TYPE_NAME_AND_TYPE;
        appendStrMethodRefNameAndTypeEntry->info = new u1[sizeof(CONSTANT_NameAndType_info)];
        auto *appendStrMethodRefNameAndTypeInfo = (CONSTANT_NameAndType_info *) appendStrMethodRefNameAndTypeEntry->info;
        appendStrMethodRefNameAndTypeInfo->name_index = 14;
        appendStrMethodRefNameAndTypeInfo->descriptor_index = 13;

        cp_info *appendStrMethodRefEntry = &constant_pool[11];
        appendStrMethodRefEntry->tag = CONSTANT_TYPE_FIELD_REF;
        appendStrMethodRefEntry->info = new u1[sizeof(CONSTANT_Methodref_info)];
        auto *appendStrMethodRefInfo = (CONSTANT_Methodref_info *) appendStrMethodRefEntry->info;
        appendStrMethodRefInfo->class_index = 4;
        appendStrMethodRefInfo->name_and_type_index = 11;

        const char *appendStrMethodRefSignatureUtf8 = "(LString;)LStringBuilder;";
        cp_info *appendStrMethodSignatureRefUtf8Entry = &constant_pool[12];
        appendStrMethodSignatureRefUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        appendStrMethodSignatureRefUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *appendStrMethodSignatureRefUtf8Info = (CONSTANT_Utf8_info *) appendStrMethodSignatureRefUtf8Entry->info;
        size_t appendStrMethodSignatureRefStrLen = strlen(appendStrMethodRefSignatureUtf8) + 1;
        appendStrMethodSignatureRefUtf8Info->length = appendStrMethodSignatureRefStrLen;
        appendStrMethodSignatureRefUtf8Info->bytes = new u1[appendStrMethodSignatureRefUtf8Info->length];
        strcpy((char *) appendStrMethodSignatureRefUtf8Info->bytes, appendStrMethodRefSignatureUtf8);
        appendStrMethodSignatureRefUtf8Info->bytes[appendStrMethodSignatureRefStrLen - 1] = '\0';

        const char *appendUtf8 = "append";
        cp_info *appendUtf8Entry = &constant_pool[13];
        appendUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        appendUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *appendUtf8Info = (CONSTANT_Utf8_info *) appendUtf8Entry->info;
        size_t appendStrLen = strlen(appendUtf8) + 1;
        appendUtf8Info->length = appendStrLen;
        appendUtf8Info->bytes = new u1[appendUtf8Info->length];
        strcpy((char *) appendUtf8Info->bytes, appendUtf8);
        appendUtf8Info->bytes[appendStrLen - 1] = '\0';

        const char *appendStrMethodSignatureUtf8 = "(Ljava/lang/String;)Ljava/lang/StringBuilder;";
        cp_info *appendStrMethodSignatureUtf8Entry = &constant_pool[14];
        appendStrMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        appendStrMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *appendStrMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) appendStrMethodSignatureUtf8Entry->info;
        size_t appendStrMethodSignatureStrLen = strlen(appendStrMethodSignatureUtf8) + 1;
        appendStrMethodSignatureUtf8Info->length = appendStrMethodSignatureStrLen;
        appendStrMethodSignatureUtf8Info->bytes = new u1[appendStrMethodSignatureUtf8Info->length];
        strcpy((char *) appendStrMethodSignatureUtf8Info->bytes, appendStrMethodSignatureUtf8);
        appendStrMethodSignatureUtf8Info->bytes[appendStrMethodSignatureStrLen - 1] = '\0';



        method_info *appendIntMethod = &methods[2];
        appendIntMethod->access_flags = ACC_PUBLIC;
        appendIntMethod->name_index = 14;
        appendIntMethod->descriptor_index = 19;
        appendIntMethod->attributes_count = 1;
        appendIntMethod->attributes = new attribute_info[appendIntMethod->attributes_count];
        attribute_info *appendIntMethodCodeAttr = &appendIntMethod->attributes[0];
        appendIntMethodCodeAttr->attribute_name_index = 7;

        auto *appendIntCodeAttr = new Code_attribute();
        appendIntCodeAttr->max_stack = 0;
        appendIntCodeAttr->max_locals = 0;
        appendIntCodeAttr->code_length = 6;
        appendIntCodeAttr->code = new u1[appendIntCodeAttr->code_length];
        appendIntCodeAttr->code[0] = ALOAD_0;
        appendIntCodeAttr->code[1] = ILOAD_1;
        appendIntCodeAttr->code[2] = INVOKE_VIRTUAL;
        appendIntCodeAttr->code[3] = 0;
        appendIntCodeAttr->code[4] = 17;
        appendIntCodeAttr->code[5] = ARETURN;
        appendIntCodeAttr->exception_table_length = 0;
        appendIntCodeAttr->attributes_count = 0;
        appendIntMethodCodeAttr->attribute_length = sizeof(Code_attribute) + sizeof(u1) * appendIntCodeAttr->code_length;
        appendIntMethodCodeAttr->info = (u1 *) appendIntCodeAttr;

        cp_info *appendIntMethodRefNameAndTypeEntry = &constant_pool[15];
        appendIntMethodRefNameAndTypeEntry->tag = CONSTANT_TYPE_NAME_AND_TYPE;
        appendIntMethodRefNameAndTypeEntry->info = new u1[sizeof(CONSTANT_NameAndType_info)];
        auto *appendIntMethodRefNameAndTypeInfo = (CONSTANT_NameAndType_info *) appendIntMethodRefNameAndTypeEntry->info;
        appendIntMethodRefNameAndTypeInfo->name_index = 14;
        appendIntMethodRefNameAndTypeInfo->descriptor_index = 18;

        cp_info *appendIntMethodRefEntry = &constant_pool[16];
        appendIntMethodRefEntry->tag = CONSTANT_TYPE_FIELD_REF;
        appendIntMethodRefEntry->info = new u1[sizeof(CONSTANT_Methodref_info)];
        auto *appendIntMethodRefInfo = (CONSTANT_Methodref_info *) appendIntMethodRefEntry->info;
        appendIntMethodRefInfo->class_index = 4;
        appendIntMethodRefInfo->name_and_type_index = 16;

        const char *appendIntMethodRefSignatureUtf8 = "(I)LStringBuilder;";
        cp_info *appendIntMethodSignatureRefUtf8Entry = &constant_pool[17];
        appendIntMethodSignatureRefUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        appendIntMethodSignatureRefUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *appendIntMethodSignatureRefUtf8Info = (CONSTANT_Utf8_info *) appendIntMethodSignatureRefUtf8Entry->info;
        size_t appendIntMethodSignatureRefStrLen = strlen(appendIntMethodRefSignatureUtf8) + 1;
        appendIntMethodSignatureRefUtf8Info->length = appendIntMethodSignatureRefStrLen;
        appendIntMethodSignatureRefUtf8Info->bytes = new u1[appendIntMethodSignatureRefUtf8Info->length];
        strcpy((char *) appendIntMethodSignatureRefUtf8Info->bytes, appendIntMethodRefSignatureUtf8);
        appendIntMethodSignatureRefUtf8Info->bytes[appendIntMethodSignatureRefStrLen - 1] = '\0';

        const char *appendIntMethodSignatureUtf8 = "(I)Ljava/lang/StringBuilder;";
        cp_info *appendIntMethodSignatureUtf8Entry = &constant_pool[18];
        appendIntMethodSignatureUtf8Entry->tag = CONSTANT_TYPE_UTF8;
        appendIntMethodSignatureUtf8Entry->info = new u1[sizeof(CONSTANT_Utf8_info)];
        auto *appendIntMethodSignatureUtf8Info = (CONSTANT_Utf8_info *) appendIntMethodSignatureUtf8Entry->info;
        size_t appendIntMethodSignatureStrLen = strlen(appendIntMethodSignatureUtf8) + 1;
        appendIntMethodSignatureUtf8Info->length = appendIntMethodSignatureStrLen;
        appendIntMethodSignatureUtf8Info->bytes = new u1[appendIntMethodSignatureUtf8Info->length];
        strcpy((char *) appendIntMethodSignatureUtf8Info->bytes, appendIntMethodSignatureUtf8);
        appendIntMethodSignatureUtf8Info->bytes[appendIntMethodSignatureStrLen - 1] = '\0';



        char *classNameChar = new char[thisClassUtf8CpInfo->length];
        strcpy(classNameChar, (char *) thisClassUtf8CpInfo->bytes);
        className = std::string(classNameChar);

        methodTable = new MethodTable(this);
        fieldTable = new FieldTable(this);
    }
};

#endif //LAB7_STRINGBUILDERCLASSFILE_H
