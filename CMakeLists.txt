cmake_minimum_required(VERSION 3.17)
project(lab7)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab7 src/main.cpp src/Instructions.h src/MethodRunner.cpp src/MethodRunner.h src/ClassInstance.cpp src/ClassInstance.h src/ClassFile.h src/ClassFileReader.h src/ObjectPool.cpp src/ObjectPool.h src/ClassFileLookup.cpp src/ClassFileLookup.h src/builtin/StringClassFile.h src/StringPool.cpp src/StringPool.h src/builtin/ObjectClassFile.h src/MethodTable.cpp src/MethodTable.h src/MethodLookup.h src/ClassInstantiator.cpp src/ClassInstantiator.h src/ByteTypes.h src/FieldLookup.h src/FieldTable.h src/FieldTable.cpp src/builtin/ArrayClassFile.h src/builtin/SystemClassFile.h src/builtin/PrintStreamClassFile.h src/BuiltinClassLoader.h src/builtin/StringBuilderClassFile.h src/Endian.h)