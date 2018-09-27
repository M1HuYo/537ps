#include <stdio.h>
#include <stdlib.h>
#include "opproc.h"
#include "getprocs.h"
#include "statparse.h"

/*
* Prints out information about user processes in this form:
*
* <pid>: <state> utime=<user time> stime=<system time> vmemory=<virtual memory> [<command line>]
*
* Usage: 537ps -p <pid> -[sUSvc]
*/
int main(int argc, char** argv) {
    flags* opts = parsecline(argc, argv);
    
    if (opts == NULL) {
        return 0;
    }
    if (opts->fail == 1) {
        fprintf(stderr, "Usage: 537ps -p <pid> -[sUSvc]\n");
        return 0;
    }
    
    // The list of processes
    Procnode *procs = NULL; 

    if (opts->pid_f) {
        // Checks to see if the given PID is valid
        if (getproc(opts->pid) == 0) {
            fprintf(stderr, "Cannot access the process with id: %s\n", opts->pid);
            return 0;
        }
	else if (getproc(opts->pid) == -1) {
	    fprintf(stderr, "Process with id %s does not exist.\n", opts->pid);
	    return 0;
	}
    } else {
        procs = getproclist();
        if (procs == NULL) {
            fprintf(stderr, "You do not have access to any current running processes.");
            return 0;
        }   
    }
    
    do {
        char* pid = NULL;
        if (opts->pid_f == 1) {
            pid = opts->pid;  
        } else {
	    if(procs != NULL) 
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
        
        // Goes to next process and frees the last one (if -p wasn't used)
        if (opts->pid_f == 0) {
            Procnode *temp = procs;
            procs = procs->next;
            free(temp);
        }
        printf("\n");

    } while (opts->pid_f == 0 && procs->pid != NULL); 

    free(opts);
}
