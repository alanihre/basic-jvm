//
// Created by Alan Ihre on 2020-09-08.
//

#ifndef LAB7_CLASSFILELOOKUP_H
#define LAB7_CLASSFILELOOKUP_H

#include <unordered_map>
#include "ClassFile.h"
#include <string>

class ClassFileLookup {
private:
    std::unordered_map<std::string, ClassFile *> map;

    ClassFile *loadClassFile(const std::string &className);

public:
    ClassFileLookup();

    void insertClassFile(const std::string &className, ClassFile *classFile);

    ClassFile *getClassFile(const std::string &className);
};

class ClassFileNotFoundException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Class file not found";
    }
};

#endif //LAB7_CLASSFILELOOKUP_H
