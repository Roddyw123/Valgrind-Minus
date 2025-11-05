# Valgrind-Minus


Valgrind-Minus is a library that:
- Intercepts all malloc calls in an application and outputs after each malloc call the number of bytes allocated so far by the program on the stream stderr (malloc_interept.c)
- TBA


## Malloc Intercepter
To run the malloc intercepter, run:

```bash
gcc -shared -fPIC -o malloc_intercept.so malloc_intercept.c -ldl
```

This generates an executable. In order to run the executable, run:

```bash
LD_PRELOAD=./malloc_intercept.so [./your_program]
```