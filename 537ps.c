#include <stdio.h>
#include <stdlib.h>
#include "opproc.h"
#include "getprocs.h"
#include "statparse.h"

int main(int argc, char** argv) {
    flags* opts = parsecline(argc, argv);
    
    if (opts == NULL) {
        return 0;
    }
    if (opts->fail == 1) {
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
    
    do {
        char* pid;
        if (opts->pid_f == 1) {
            pid = opts->pid;  
        } else {
            pid = procs->pid;
        }

        printf("%s:", pid);

        if (opts->state == 1) {
            char *state = getstate(pid);
            if (state == NULL) {
                return 0;
            }
            printf(" %s", state);
            free(state);
        }
        if (opts->utime == 1) {
            char *utime = getutime(pid);
            if (utime == NULL) {
                return 0;
            }
            printf(" utime=%s", utime);
            free(utime);
        }
        if (opts->stime == 1) {
            char *stime = getstime(pid);
            if (stime == NULL) {
                return 0;
            }
            printf(" stime=%s", stime);
            free(stime);
        }
        if (opts->vmem == 1) {
            char *vmem = getvmem(pid);
            if (vmem == NULL) {
                return 0;
            }
            printf(" vmemory=%s", vmem);
            free(vmem);
        }
        if (opts->cargs == 1) {
            char *cargs = getcmdline(pid);
            if (cargs == NULL) {
                return 0;
            }
            printf(" [%s]", cargs);
            free(cargs);
        }

        printf("\n");

        Procnode *temp = procs;
        procs = procs->next;
        free(temp);
        free(pid);

    } while (opts->pid_f == 0 && procs->pid != NULL); 

    free(opts);
}
