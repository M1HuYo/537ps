#include <stdio.h>
#include "opproc.h"

int main(int argc, char *argv[])
{
    flags *flag = parsecline(argc, argv);

    
    printf("PID: %d\n", flag->pid);
    printf("State: %d\n", flag->state);
    printf("utime: %d\n", flag->utime);
    printf("stime: %d\n", flag->stime);
    printf("vmem: %d\n", flag->vmem);
    printf("cargs: %d\n", flag->cargs);
}
