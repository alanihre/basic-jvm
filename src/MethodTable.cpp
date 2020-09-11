//
// Created by Alan Ihre on 2020-09-10.
//

#include "MethodTable.h"

Method *MethodTable::getMethod(const std::string &signature) {
    auto it = map.find(signature);
    if (it != map.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

int countArguments(const std::string &methodDescriptor) {
    int count = 0;

    auto it = methodDescriptor.cbegin();
    it++;

    while (it != methodDescriptor.cend() && *it != ')') {
        switch (*it) {
            case FIELD_TYPE_BYTE: // Fall through
            case FIELD_TYPE_INT: // Fall through
            case FIELD_TYPE_DOUBLE: // Fall through
            case FIELD_TYPE_FLOAT: // Fall through
            case FIELD_TYPE_LONG: // Fall through
            case FIELD_TYPE_SHORT: // Fall through
            case FIELD_TYPE_BOOLEAN: // Fall through
            case FIELD_TYPE_ARRAY: // Fall through
            case FIELD_TYPE_CHAR: {
                count++;
                break;
            }
            case FIELD_TYPE_CLASS_REF: {
                do {
                    it++;
                } while (*it != ';');
                count++;
                break;
            }
        }
        it++;
    }

    return count;
}


MethodTable::MethodTable(ClassFile *classFile) {
    for (int i = 0; i < classFile->methods_count; ++i) {
        method_info methodInfo = classFile->methods[i];

        auto *method = new Method();
        method->accessFlags = methodInfo.access_flags;
        method->name = std::string(
                (char *) ((CONSTANT_Utf8_info *) classFile->constant_pool[methodInfo.name_index - 1].info)->bytes);
        method->descriptor = std::string(
                (char *) ((CONSTANT_Utf8_info *) classFile->constant_pool[methodInfo.descriptor_index -
                                                                          1].info)->bytes);

        for (int j = 0; j < methodInfo.attributes_count; ++j) {
            attribute_info attributeInfo = methodInfo.attributes[j];
            char *attrName = (char *) ((CONSTANT_Utf8_info *) classFile->constant_pool[
                    attributeInfo.attribute_name_index - 1].info)->bytes;
            if (strcmp(attrName, ATTRIBUTE_TYPE_CODE) == 0) {
                method->codeAttribute = (Code_attribute *) attributeInfo.info;
            }
        }

        method->numArguments = countArguments(method->descriptor);
        method->classFile = classFile;

        std::string signature = method->name + method->descriptor;
        map.insert(std::pair<std::string, Method *>(signature, method));
    }
}
