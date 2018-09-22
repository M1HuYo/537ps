#include <stdio.h>
#include "opproc.h"
#include "getprocs.h"
#include "statparse.h"

int main(int argc, char** argv)
{
    flags* opts = parsecline(argc, argv);
    
    if (opts == NULL)
    {
        fprintf(stderr, "Usage: 537ps -p <pid> -[sUSvc]\n");
        return 0;
    }
    
    printf("Gets here\n");

    Procnode *procs; 
    if (opts->pid_f) {
        if (getproc(opts->pid) == 0) {
            fprintf(stderr, "Cannot access proc with id %s\n", opts->pid);
            return 0;
        }
    } else {
        printf("Gets here\n");
        procs = getproclist();
        if (procs == NULL) {
            fprintf(stderr, "Cannot access process");
            return 0;
        }   
    }
    
    do
    {
        printf("%s:", opts->pid);
        if (opts->state == 1)
            printf(" %s", getstate(opts->pid));
        if (opts->utime == 1)
            printf("utime= %s", getutime(opts->pid));
        if (opts->stime == 1)
            printf("stime= %s", getstime(opts->pid));
        if (opts->vmem == 1)
            printf("vmemory= %s", getvmem(opts->pid));
        if (opts->cargs == 1)
            printf(" [%s]", getcmdline(opts->pid));

        printf("\n");
        procs = procs->next;

    } while (opts->pid_f == 0 && procs->pid != NULL); 
}
