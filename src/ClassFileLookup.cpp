//
// Created by Alan Ihre on 2020-09-08.
//

#include "ClassFileLookup.h"
#include "ClassFileReader.h"
#include <sys/stat.h>

ClassFileLookup::ClassFileLookup() = default;

void ClassFileLookup::insertClassFile(const std::string &className, ClassFile *classFile) {
    map.insert(std::pair<std::string, ClassFile *>(className, classFile));
}

inline bool fileExists(const char *fileName) {
    struct stat buffer;
    return stat(fileName, &buffer) == 0;
}

ClassFile *ClassFileLookup::getClassFile(const std::string &className) {
    if (map.find(className) == map.end()) {
        auto *classFile = new ClassFile{};
        loadClassFile(className, classFile);
        insertClassFile(className, classFile);
        return classFile;
    }
    return map[className];
}

void ClassFileLookup::loadClassFile(const std::string &className, ClassFile *classFile) {
    std::string fileNameString = className + ".class";
    const char *fileName = fileNameString.c_str();
    if (!fileExists(fileName)) {
        throw ClassFileNotFoundException();
    }
    return readClassFile(fileName, this, classFile);
}

ClassFileLookup::~ClassFileLookup() {
    for(auto & elem : map) {
        delete elem.second;
    }
}
