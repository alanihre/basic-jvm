#include "MethodRunner.h"
#include "ClassFileLookup.h"
#include <iostream>
#include "ClassInstantiator.h"
#include "BuiltinClassLoader.h"
#include "StringPool.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No main class specified as argument" << std::endl;
        return 1;
    }

    std::string classIncludePath;
    if(const char* path = std::getenv("SIMPLE_JVM_INCLUDE_PATH")) {
        classIncludePath = path;
        classIncludePath.append("/");
    }

    std::string mainClassName = std::string(argv[1]);

    ClassFileLookup classFileLookup(classIncludePath);

    auto *operandStack = new std::stack<int>;

    ObjectPool objectPool = ObjectPool();

    ClassInstantiator classInstantiator(&classFileLookup, &objectPool);

    StringPool stringPool = StringPool(&objectPool, &classFileLookup, &classInstantiator);

    loadBuiltinClasses(&classFileLookup, &objectPool, &classInstantiator);

    ClassFile *mainClass = classFileLookup.getClassFile(mainClassName);

    //Load command line arguments
    int numArgs = argc - 2;
    int *args = new int[1];
    ObjectRef argsArrayRef = objectPool.newObjectRef();
    ClassFile *arrayClassFile = classFileLookup.getClassFile(std::string(BUILTIN_ARRAY_CLASS_NAME));
    objectPool.getObject(argsArrayRef)->initializeArray(arrayClassFile, numArgs);
    for (int i = 0; i < numArgs; ++i) {
        ObjectRef stringRef = stringPool.getStringInstanceRef(std::string(argv[i + 2]));
        objectPool.getObject(argsArrayRef)->putArrayElement(i, stringRef);
    }
    args[0] = argsArrayRef;

    Method *method = lookupStaticMethod("main([Ljava/lang/String;)V", mainClass);
    MethodRunner methodRunner(method->codeAttribute, mainClass, operandStack, numArgs, args, &stringPool, &objectPool,
                              &classInstantiator, &classFileLookup);
    methodRunner.run();

    delete[] args;
    delete operandStack;

    return 0;
}
