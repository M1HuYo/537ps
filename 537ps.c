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

    Procnode *procs; 
    if (opts->pid_f) {
        if (getproc(opts->pid) == 0) {
            fprintf(stderr, "Cannot access proc with id %s\n", opts->pid);
            return 0;
        }
    } else {
        procs = getproclist();
        if (procs == NULL) {
            fprintf(stderr, "Cannot access process");
            return 0;
        }   
    }
    
    do
    {
        char* pid;
        if (opts->pid_f == 1)
        {
            pid = opts->pid;  
        } else {
            pid = procs->pid;
        }
        printf("%s:", pid);
        if (opts->state == 1)
            printf(" %s", getstate(pid));
        if (opts->utime == 1)
            printf(" utime=%s", getutime(pid));
        if (opts->stime == 1)
            printf(" stime=%s", getstime(pid));
        if (opts->vmem == 1)
            printf(" vmemory=%s", getvmem(pid));
        if (opts->cargs == 1)
            printf(" [%s]", getcmdline(pid));

        printf("\n");
        procs = procs->next;

    } while (opts->pid_f == 0 && procs->pid != NULL); 
}
