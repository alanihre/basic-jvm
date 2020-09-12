//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef BASIC_JVM_CLASSFILELOOKUP_H
#define BASIC_JVM_CLASSFILELOOKUP_H

#include <unordered_map>
#include "ClassFile.h"
#include <string>

class ClassFileLookup {
private:
    std::unordered_map<std::string, ClassFile *> map;
    std::string classIncludePath;

    void loadClassFile(const std::string &className, ClassFile *classFile);

public:
    ClassFileLookup(std::string classIncludePath);
    ~ClassFileLookup();

    void insertClassFile(const std::string &className, ClassFile *classFile);

    ClassFile *getClassFile(const std::string &className);
};

class ClassFileNotFoundException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Class file not found";
    }
};

#endif //BASIC_JVM_CLASSFILELOOKUP_H
