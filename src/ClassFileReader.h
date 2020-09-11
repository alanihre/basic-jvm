//
// Created by Alan Ihre on 2020-09-07.
//

#ifndef LAB7_CLASSFILEREADER_H
#define LAB7_CLASSFILEREADER_H

#include <iostream>
#include <fstream>
#include "ClassFile.h"
#include "ClassFileLookup.h"

enum ENDIANNESS {
    LITTLEENDIAN, BIGENDIAN
};

ENDIANNESS CheckArchEndianalityV1(void) {
    int Endian = 0x00000001; // assuming target architecture is 32-bit

    // as Endian = 0x00000001 so MSB (Most Significant Byte) = 0x00 and LSB (Least     Significant Byte) = 0x01
    // casting down to a single byte value LSB discarding higher bytes

    return (*(char *) &Endian == 0x01) ? LITTLEENDIAN : BIGENDIAN;
}


inline void
parseAttributeInfo(attribute_info *attributeInfo, cp_info *constantPool, std::fstream *fh, ENDIANNESS endian) {
    fh->read((char *) &attributeInfo->attribute_name_index, sizeof(attributeInfo->attribute_name_index));
    fh->read((char *) &attributeInfo->attribute_length, sizeof(attributeInfo->attribute_length));
    if (endian == LITTLEENDIAN) attributeInfo->SwapEndian();

    char *attrName = (char *) ((CONSTANT_Utf8_info *) constantPool[attributeInfo->attribute_name_index -
                                                                   1].info)->bytes;
    if (strcmp(attrName, ATTRIBUTE_TYPE_CODE) == 0) {
        attributeInfo->info = new u1[sizeof(Code_attribute)];
        auto *code = (Code_attribute *) attributeInfo->info;
        fh->read((char *) &code->max_stack, sizeof(code->max_stack));
        fh->read((char *) &code->max_locals, sizeof(code->max_locals));
        fh->read((char *) &code->code_length, sizeof(code->code_length));

        u4 codeLength = code->code_length;
        if (endian == LITTLEENDIAN) SwapEndian(codeLength);
        code->code = new u1[codeLength];
        fh->read((char *) code->code, codeLength);

        fh->read((char *) &code->exception_table_length, sizeof(code->exception_table_length));
        u4 exceptionTableLength = code->exception_table_length;
        if (endian == LITTLEENDIAN) SwapEndian(exceptionTableLength);
        code->exception_table = new exception_table[exceptionTableLength];
        for (int i = 0; i < exceptionTableLength; ++i) {
            exception_table *exceptionTable = &code->exception_table[i];
            fh->read((char *) &exceptionTable->start_pc, sizeof(exceptionTable->start_pc));
            fh->read((char *) &exceptionTable->end_pc, sizeof(exceptionTable->end_pc));
            fh->read((char *) &exceptionTable->handler_pc, sizeof(exceptionTable->handler_pc));
            fh->read((char *) &exceptionTable->catch_type, sizeof(exceptionTable->catch_type));
            exceptionTable->SwapEndian();
        }

        fh->read((char *) &code->attributes_count, sizeof(code->attributes_count));
        u2 attributesCount = code->attributes_count;
        SwapEndian(attributesCount);
        code->attributes = new attribute_info[code->attributes_count];
        for (int i = 0; i < attributesCount; ++i) {
            auto *attr = new attribute_info;
            ::parseAttributeInfo(attr, constantPool, fh, endian);
            code->attributes[i] = *attr;
        }
        if (endian == LITTLEENDIAN) code->SwapEndian();
    } else if (strcmp(attrName, ATTRIBUTE_TYPE_CONSTANT_VALUE) == 0) {
        attributeInfo->info = new u1[sizeof(ConstantValue_attribute)];
        auto *constValueAttr = (ConstantValue_attribute *) attributeInfo->info;
        fh->read((char *) &constValueAttr->constantvalue_index, sizeof(constValueAttr->constantvalue_index));
        if (endian == LITTLEENDIAN) constValueAttr->SwapEndian();
    } else {
        attributeInfo->info = new u1[attributeInfo->attribute_length];
        fh->read((char *) attributeInfo->info, attributeInfo->attribute_length);
    }

    //TODO: Handle different attributes
}

class UnhandledConstantTypeException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Unhandled constant type";
    }
};


inline ClassFile *readClassFile(const char *file, ClassFileLookup *classFileLookup) {
    ENDIANNESS endian = CheckArchEndianalityV1();

    auto *classFile = new ClassFile;

    std::fstream fh;
    fh.open(file, std::fstream::in | std::fstream::binary);

    fh.read((char *) &classFile->magic, sizeof(classFile->magic));
    fh.read((char *) &classFile->minor_version, sizeof(classFile->minor_version));
    fh.read((char *) &classFile->major_version, sizeof(classFile->major_version));
    fh.read((char *) &classFile->constant_pool_count, sizeof(classFile->constant_pool_count));

    u2 constantPoolCount = classFile->constant_pool_count;
    if (endian == LITTLEENDIAN) SwapEndian(constantPoolCount);
    classFile->constant_pool = new cp_info[constantPoolCount - 1];
    for (int i = 0; i < constantPoolCount - 1; ++i) {
        cp_info *constantPoolInfo = &classFile->constant_pool[i];
        fh.read((char *) &constantPoolInfo->tag, sizeof(constantPoolInfo->tag));

        switch (constantPoolInfo->tag) {
            case CONSTANT_TYPE_CLASS: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_Class_info)];
                auto *info = (CONSTANT_Class_info *) constantPoolInfo->info;
                fh.read((char *) &info->name_index, sizeof(info->name_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_FIELD_REF: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_Fieldref_info)];
                auto *info = (CONSTANT_Fieldref_info *) constantPoolInfo->info;
                fh.read((char *) &info->class_index, sizeof(info->class_index));
                fh.read((char *) &info->name_and_type_index, sizeof(info->name_and_type_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_METHOD_REF: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_Methodref_info)];
                auto *info = (CONSTANT_Methodref_info *) constantPoolInfo->info;
                fh.read((char *) &info->class_index, sizeof(info->class_index));
                fh.read((char *) &info->name_and_type_index, sizeof(info->name_and_type_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_INSTANCE_METHOD_REF: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_InterfaceMethodref_info)];
                auto *info = (CONSTANT_InterfaceMethodref_info *) constantPoolInfo->info;
                fh.read((char *) &info->class_index, sizeof(info->class_index));
                fh.read((char *) &info->name_and_type_index, sizeof(info->name_and_type_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_STRING: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_String_info)];
                auto *info = (CONSTANT_String_info *) constantPoolInfo->info;
                fh.read((char *) &info->string_index, sizeof(info->string_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_INTEGER: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_Integer_info)];
                auto *info = (CONSTANT_Integer_info *) constantPoolInfo->info;
                fh.read((char *) &info->bytes, sizeof(info->bytes));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_NAME_AND_TYPE: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_NameAndType_info)];
                auto *info = (CONSTANT_NameAndType_info *) constantPoolInfo->info;
                fh.read((char *) &info->name_index, sizeof(info->name_index));
                fh.read((char *) &info->descriptor_index, sizeof(info->descriptor_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_UTF8: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_Utf8_info)];
                auto *info = (CONSTANT_Utf8_info *) constantPoolInfo->info;
                fh.read((char *) &info->length, sizeof(info->length));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                info->bytes = new u1[info->length + 1];
                fh.read((char *) info->bytes, info->length);
                //Null-terminate
                info->length += 1;
                info->bytes[info->length - 1] = '\0';
                break;
            }
            case CONSTANT_TYPE_METHOD_HANDLE: {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_MethodHandle_info)];
                auto *info = (CONSTANT_MethodHandle_info *) constantPoolInfo->info;
                fh.read((char *) &info->reference_kind, sizeof(info->reference_kind));
                fh.read((char *) &info->reference_index, sizeof(info->reference_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            case CONSTANT_TYPE_METHOD_TYPE : {
                constantPoolInfo->info = new u1[sizeof(CONSTANT_MethodType_info)];
                auto *info = (CONSTANT_MethodType_info *) constantPoolInfo->info;
                fh.read((char *) &info->descriptor_index, sizeof(info->descriptor_index));
                if (endian == LITTLEENDIAN) info->SwapEndian();
                break;
            }
            default: {
                throw UnhandledConstantTypeException();
            }
        }
    }

    fh.read((char *) &classFile->access_flags, sizeof(classFile->access_flags));
    fh.read((char *) &classFile->this_class, sizeof(classFile->this_class));
    fh.read((char *) &classFile->super_class, sizeof(classFile->super_class));
    fh.read((char *) &classFile->interfaces_count, sizeof(classFile->interfaces_count));

    u2 interfacesCount = classFile->interfaces_count;
    SwapEndian(interfacesCount);
    classFile->interfaces = new u2[interfacesCount];
    for (int i = 0; i < interfacesCount; ++i) {
        fh.read((char *) &classFile->interfaces[i], sizeof(u2));
        if (endian == LITTLEENDIAN) SwapEndian(classFile->interfaces[i]);
    }

    fh.read((char *) &classFile->fields_count, sizeof(classFile->fields_count));
    u2 fieldsCount = classFile->fields_count;
    SwapEndian(fieldsCount);
    classFile->fields = new field_info[fieldsCount];
    for (int i = 0; i < fieldsCount; ++i) {
        field_info fieldInfo = {};
        fh.read((char *) &fieldInfo.access_flags, sizeof(fieldInfo.access_flags));
        fh.read((char *) &fieldInfo.name_index, sizeof(fieldInfo.name_index));
        fh.read((char *) &fieldInfo.descriptor_index, sizeof(fieldInfo.descriptor_index));
        fh.read((char *) &fieldInfo.attributes_count, sizeof(fieldInfo.attributes_count));
        if (endian == LITTLEENDIAN) fieldInfo.SwapEndian();

        fieldInfo.attributes = new attribute_info[fieldInfo.attributes_count];
        for (int j = 0; j < fieldInfo.attributes_count; ++j) {
            auto *attributeInfo = new attribute_info;
            parseAttributeInfo(attributeInfo, classFile->constant_pool, &fh, endian);
            fieldInfo.attributes[j] = *attributeInfo;
        }

        classFile->fields[i] = fieldInfo;
    }

    fh.read((char *) &classFile->methods_count, sizeof(classFile->methods_count));
    u2 methodsCount = classFile->methods_count;
    SwapEndian(methodsCount);
    classFile->methods = new method_info[methodsCount];
    for (int i = 0; i < methodsCount; ++i) {
        method_info methodInfo = {};
        fh.read((char *) &methodInfo.access_flags, sizeof(methodInfo.access_flags));
        fh.read((char *) &methodInfo.name_index, sizeof(methodInfo.name_index));
        fh.read((char *) &methodInfo.descriptor_index, sizeof(methodInfo.descriptor_index));
        fh.read((char *) &methodInfo.attributes_count, sizeof(methodInfo.attributes_count));
        if (endian == LITTLEENDIAN) methodInfo.SwapEndian();

        methodInfo.attributes = new attribute_info[methodInfo.attributes_count];
        for (int j = 0; j < methodInfo.attributes_count; ++j) {
            auto *attributeInfo = new attribute_info;
            parseAttributeInfo(attributeInfo, classFile->constant_pool, &fh, endian);
            methodInfo.attributes[j] = *attributeInfo;
        }

        classFile->methods[i] = methodInfo;
    }

    fh.read((char *) &classFile->attributes_count, sizeof(classFile->attributes_count));
    u2 attributesCount = classFile->attributes_count;
    SwapEndian(attributesCount);
    classFile->attributes = new attribute_info[classFile->attributes_count];
    for (int i = 0; i < attributesCount; ++i) {
        auto *attributeInfo = new attribute_info;
        parseAttributeInfo(attributeInfo, classFile->constant_pool, &fh, endian);
        classFile->attributes[i] = *attributeInfo;
    }

    fh.close();

    if (endian == LITTLEENDIAN) classFile->SwapEndian();

    cp_info *thisClassCpEntry = &classFile->constant_pool[classFile->this_class - 1];
    auto *thisClassNameInfo = (CONSTANT_Class_info *) thisClassCpEntry->info;
    cp_info *thisClassNameEntry = &classFile->constant_pool[thisClassNameInfo->name_index - 1];
    auto *thisClassNameUtf8Info = (CONSTANT_Utf8_info *) thisClassNameEntry->info;
    char *thisClassName = new char[thisClassNameUtf8Info->length];
    strcpy(thisClassName, (char *) thisClassNameUtf8Info->bytes);
    classFile->className = std::string(thisClassName);

    classFile->methodTable = new MethodTable(classFile);
    classFile->fieldTable = new FieldTable(classFile);

    if (classFile->super_class != 0) {
        cp_info cpEntry = classFile->constant_pool[classFile->super_class - 1];
        auto *superClassInfo = (CONSTANT_Class_info *) cpEntry.info;
        cp_info superClassNameEntry = classFile->constant_pool[superClassInfo->name_index - 1];
        auto *superClassNameInfo = (CONSTANT_Utf8_info *) superClassNameEntry.info;
        char *superClassName = (char *) superClassNameInfo->bytes;

        classFile->superClassFile = classFileLookup->getClassFile(std::string(superClassName));
    }

    return classFile;
}

#endif //LAB7_CLASSFILEREADER_H
