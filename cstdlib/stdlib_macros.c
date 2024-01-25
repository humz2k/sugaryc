#include <stdlib.h>
#include <stdio.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define GET(x) x

#define OUTPUT_MACRO_VALUE(name,MACRO_NAME) printf("#define %s %d\n",name,(int)GET(MACRO_NAME))

#define OUTPUT_TYPEDEF(t1,t2) printf("typedef %s %s;\n",TOSTRING(t1),TOSTRING(t2))

#define error_out(str) printf("%s\n",str);exit(1)

#define __restrict restrict

int main(){

    printf("#ifndef _STDLIB_MACROS_H_\n#define _STDLIB_MACROS_H_\n");

    switch (sizeof(size_t)){
        case sizeof(unsigned long):
            OUTPUT_TYPEDEF(unsigned long,size_t);
            break;
        case sizeof(unsigned int):
            OUTPUT_TYPEDEF(unsigned int,size_t);
            break;
        default:
            error_out("couldn't determine sizeof(size_t)");
    }
    printf("#endif\n");
    return 0;
}