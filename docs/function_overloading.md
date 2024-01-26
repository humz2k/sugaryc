# Function Overloading

This works the same as in C++. Actually, the compiler currently literally generates C++, so the name mangling is identical to C++. This will probably change, so don't count on that being the case.

Use the `extern` keyword to stop name mangling. For example, the header for `free` in `stdlib.sgh` is
```
extern void free(void*);
```