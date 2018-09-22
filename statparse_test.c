#include <stdio.h>
#include "statparse.h"

int main(int argc, char** argv) {
    char* pid = argv[1]; 
    char* state = (char*) getstate(pid);
    printf("%s\n", state);
    printf("%s\n", getutime(pid)); 
    printf("%s\n", getstime(pid));
    printf("%s\n", getvmem(pid));
    printf("%s\n", getcmdline(pid));  
}
