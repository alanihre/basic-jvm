//
// Created by Alan Ihre on 2020-09-07.
//


#ifndef BASIC_JVM_CLASSFILE_H
#define BASIC_JVM_CLASSFILE_H

#include "MethodTable.h"
#include "FieldTable.h"
#include "ByteTypes.h"
#include <string>
#include "Endian.h"

#define CONSTANT_TYPE_CLASS 7
#define CONSTANT_TYPE_FIELD_REF 9
#define CONSTANT_TYPE_METHOD_REF 10
#define CONSTANT_TYPE_INSTANCE_METHOD_REF 11
#define CONSTANT_TYPE_STRING 8
#define CONSTANT_TYPE_INTEGER 3
#define CONSTANT_TYPE_NAME_AND_TYPE 12
#define CONSTANT_TYPE_UTF8 1
#define CONSTANT_TYPE_METHOD_HANDLE 15
#define CONSTANT_TYPE_METHOD_TYPE 16

#define ATTRIBUTE_TYPE_CONSTANT_VALUE "ConstantValue"
#define ATTRIBUTE_TYPE_CODE "Code"
#define ATTRIBUTE_TYPE_SOURCE_FILE "SourceFile"
#define ATTRIBUTE_TYPE_LINE_NUMBER_TABLE "LineNumberTable"

#define ACC_PUBLIC    0x0001    //Declared public; may be accessed from outside its package.
#define ACC_PRIVATE    0x0002    //Declared private; usable only within the defining class.
#define ACC_PROTECTED    0x0004    //Declared protected; may be accessed within subclasses.
#define ACC_STATIC    0x0008    //Declared static.
#define ACC_FINAL    0x0010    //Declared final; never directly assigned to after object construction (JLS §17.5).
#define ACC_VOLATILE    0x0040    //Declared volatile; cannot be cached.
#define ACC_TRANSIENT    0x0080    //Declared transient; not written or read by a persistent object manager.
#define ACC_SYNTHETIC    0x1000    //Declared synthetic; not present in the source code.
#define ACC_ENUM    0x4000    //Declared as an enum type.
#define ACC_SUPER 0x0020 //Treat superclass methods specially when invoked by the invokespecial instruction.
#define ACC_INTERFACE 0x0200 //Is an interface, not a class.
#define ACC_ABSTRACT 0x0400 //Declared abstract; must not be instantiated.
#define ACC_ANNOTATION    0x2000    //Declared as an annotation type.

#define FIELD_TYPE_BYTE 'B' //signed byte
#define FIELD_TYPE_CHAR 'C' //Unicode character code point in the Basic Multilingual Plane, encoded with UTF-16
#define FIELD_TYPE_DOUBLE 'D' //double-precision floating-point value
#define FIELD_TYPE_FLOAT 'F' //single-precision floating-point value
#define FIELD_TYPE_INT 'I' //integer
#define FIELD_TYPE_LONG 'J' //long integer
#define FIELD_TYPE_CLASS_REF 'L' //an instance of class ClassName
#define FIELD_TYPE_SHORT 'S' //signed short
#define FIELD_TYPE_BOOLEAN 'Z' //boolean true or false
#define FIELD_TYPE_ARRAY '[' //one array dimension

struct cp_info {
    u1 tag;
    u1 *info;

    void SwapEndian() {

    }
};


struct CONSTANT_Class_info {
    u2 name_index;

    void SwapEndian() {
        ::SwapEndian(name_index);
    }
};


struct CONSTANT_Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;

    void SwapEndian() {
        ::SwapEndian(class_index);
        ::SwapEndian(name_and_type_index);
    }
};


struct CONSTANT_Methodref_info {
    u2 class_index;
    u2 name_and_type_index;

    void SwapEndian() {
        ::SwapEndian(class_index);
        ::SwapEndian(name_and_type_index);
    }
};


struct CONSTANT_InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;

    void SwapEndian() {
        ::SwapEndian(class_index);
        ::SwapEndian(name_and_type_index);
    }
};


struct CONSTANT_String_info {
    u2 string_index;

    void SwapEndian() {
        ::SwapEndian(string_index);
    }
};


struct CONSTANT_Integer_info {
    u4 bytes;

    void SwapEndian() {
        ::SwapEndian(bytes);
    }
};


struct CONSTANT_NameAndType_info {
    u2 name_index;
    u2 descriptor_index;

    void SwapEndian() {
        ::SwapEndian(name_index);
        ::SwapEndian(descriptor_index);
    }
};


struct CONSTANT_Utf8_info {
    u2 length;
    u1 *bytes;

    void SwapEndian() {
        ::SwapEndian(length);
    }
};


struct CONSTANT_MethodHandle_info {
    u1 reference_kind;
    u2 reference_index;

    void SwapEndian() {
        ::SwapEndian(reference_index);
    }
};


struct CONSTANT_MethodType_info {
    u2 descriptor_index;

    void SwapEndian() {
        ::SwapEndian(descriptor_index);
    }
};


struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;

    void SwapEndian() {
        ::SwapEndian(attribute_name_index);
        ::SwapEndian(attribute_length);
    }
};


struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;

    void SwapEndian() {
        ::SwapEndian(access_flags);
        ::SwapEndian(name_index);
        ::SwapEndian(descriptor_index);
        ::SwapEndian(attributes_count);
    }
};


struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;

    void SwapEndian() {
        ::SwapEndian(access_flags);
        ::SwapEndian(name_index);
        ::SwapEndian(descriptor_index);
        ::SwapEndian(attributes_count);
    }
};

struct exception_table {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;

    void SwapEndian() {
        ::SwapEndian(start_pc);
        ::SwapEndian(end_pc);
        ::SwapEndian(handler_pc);
        ::SwapEndian(catch_type);
    }
};

struct Code_attribute {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    exception_table *exception_table;
    u2 attributes_count;
    attribute_info *attributes;

    void SwapEndian() {
        ::SwapEndian(max_stack);
        ::SwapEndian(max_locals);
        ::SwapEndian(code_length);
        ::SwapEndian(exception_table_length);
        ::SwapEndian(attributes_count);
    }
};

struct ConstantValue_attribute {
    u2 constantvalue_index;

    void SwapEndian() {
        ::SwapEndian(constantvalue_index);
    }
};

class MethodTable;

class FieldTable;

struct ClassFile {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    method_info *methods;
    u2 attributes_count;
    attribute_info *attributes;
    MethodTable *methodTable;
    FieldTable *fieldTable;
    ClassFile *superClassFile;
    std::string className;

    void SwapEndian() {
        ::SwapEndian(magic);
        ::SwapEndian(minor_version);
        ::SwapEndian(major_version);
        ::SwapEndian(constant_pool_count);
        ::SwapEndian(access_flags);
        ::SwapEndian(this_class);
        ::SwapEndian(super_class);
        ::SwapEndian(interfaces_count);
        ::SwapEndian(fields_count);
        ::SwapEndian(methods_count);
        ::SwapEndian(attributes_count);
    }
};


#endif //BASIC_JVM_CLASSFILE_H
