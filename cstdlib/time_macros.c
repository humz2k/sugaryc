#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define GET(x) x

#define OUTPUT_MACRO_VALUE(name,MACRO_NAME) printf("#define %s %d\n",name,(int)GET(MACRO_NAME))

#define OUTPUT_TYPEDEF(t1,t2) printf("typedef %s %s;\n",TOSTRING(t1),TOSTRING(t2))

#define error_out(str) printf("%s\n",str);exit(1)

int main(){

    printf("#ifndef _TIME_MACROS_H_\n#define _TIME_MACROS_H_\n");

    switch (sizeof(clock_t)){
        case sizeof(unsigned long):
            OUTPUT_TYPEDEF(unsigned long,clock_t);
            break;
        case sizeof(unsigned int):
            OUTPUT_TYPEDEF(unsigned int,clock_t);
            break;
        default:
            error_out("couldn't determine sizeof(clock_t)");
    }

    switch (sizeof(time_t)){
        case sizeof(long):
            OUTPUT_TYPEDEF(long,time_t);
            break;
        case sizeof(int):
            OUTPUT_TYPEDEF(int,time_t);
            break;
        default:
            error_out("couldn't determine sizeof(time_t)");
    }

    OUTPUT_MACRO_VALUE("CLOCKS_PER_SEC",CLOCKS_PER_SEC);

    printf("#endif\n");
    return 0;
}