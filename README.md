# basic-jvm
This is an implementation of a JVM according to the [Java® Virtual Machine Specification](https://docs.oracle.com/javase/specs/jvms/se7/html/index.html).
This project started out as a school project and is then something that I have been working on during my free time. It is yet not a complete implementation of the specification and the code needs a bit of structuring and testing.

## Limitations
Some parts of the JVM specification are not yet implemented. Here is a list of some of the missing features which I aim to implement in the future.

- Not all bytecodes are implemented. For example, double, float and long bytecode instructions are not supported as well as multidimensional array instructions. A full list of unsupported bytecodes is available [here](unsupported_instructions.md). 
- Modifiers like public, private, final, etc. are ignored since they are not implemented. However, the static modifier is implemented.
- Since not all bytecodes and modifiers are implemented, the Java base package can not be loaded. Therefore some necessary classes have been implemented in a more basic form and are automatically loaded from the path specified at the environment variable SIMPLE_JVM_INCLUDE_PATH. These are String, StringBuilder, PrintStream, System and Object. 
- Exceptions are not supported.
- Nested classes are not supported.
- Synchronization is not supported.

## Running programs
```basic-jvm <main class file> <optional arguments>```

The environment variable SIMPLE_JVM_INCLUDE_PATH must be set to include the base classes located in src/builtin/classfiles.

## Improvements
- Unit tests
- Array packing. Currently all array elements are casted to int before being stored in the array where they take up the space of an int even if the element stored is of type byte or char. Array elements should be packed according to type.
- Usage of smart pointers.
- Code cleanup. Currently the files and functions are very large and they should be broken up into smaller units.
- Better error information containing more details about errors that occur, including stack traces with line numbers.
- Debugging functionality
