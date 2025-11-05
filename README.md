# Valgrind-Minus


Valgrind-Minus is a library that:
- Intercepts all malloc calls in an application and outputs after each malloc call the number of bytes allocated so far by the program on the stream stderr ([src/malloc_intercept.c](src/malloc_intercept.c))
- LLVM pass that counts the number of functions and basic blocks in a program ([src/llvm_pass.cpp](src/llvm_pass.cpp))


## Malloc Intercepter
To run the malloc intercepter, run:

```bash
gcc -shared -fPIC -o malloc_intercept.so malloc_intercept.c -ldl
```

This generates an executable. In order to run the executable, run:

```bash
LD_PRELOAD=./malloc_intercept.so [./your_program]
```

## LLVM Pass
To build and run the LLVM pass, run:

```bash
clang++ -shared -fPIC -o llvm_pass.so src/llvm_pass.cpp `llvm-config --cxxflags --ldflags`
```

To use the pass on a C program:

```bash
clang -emit-llvm -S your_program.c -o your_program.ll
opt -load-pass-plugin=./llvm_pass.so -passes=countpass your_program.ll -o /dev/null
```