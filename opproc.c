#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Struct that holds whether or not the options are to be used
typedef struct flags{
    int pid_f; // Flag variable for the PID, 1 if -p is used
    char* pid;
    int state;
    int utime;
    int stime;
    int vmem;
    int cargs;
    int fail;
}flags;

/*
* Parses command line input for specific options
*/
flags* parsecline(int argc, char *argv[]) 
{    
    int option;
    opterr = 0; //Turns off getopt error messages

    flags *flag = malloc(sizeof(flags));
    if (flag == NULL) {
        fprintf(stderr, "Out of memory\n");
        return NULL;
    }     

    flag->pid_f = 0;
    flag->pid = 0;
    flag->state = 0;
    flag->utime = 1;
    flag->stime = 0;
    flag->vmem = 0;
    flag->cargs = 1;
    flag->fail = 0;
    
    int *last; //Holds the last option flag so it can set it to 
               //false when '-' is used

    while ((option = getopt(argc, argv, "p:sUSvc-")) != -1) {
        switch(option) {
            case 'p':
                flag->pid_f = 1;
                flag->pid = optarg;
                if (atoi(optarg) == 0) {
                    fprintf(stderr, "PID has to be an integer >= 0\n");
                    return NULL;
                }
                last = &flag->pid_f;
                break;
            case 's':
                flag->state = 1;
                last = &flag->state;
                break;
            case 'U':
                flag->utime = 0;
                last = &flag->utime;
                break;
            case 'S':
                flag->stime = 1;
                last = &flag->stime;
                break;
            case 'v':
                flag->vmem = 1;
                last = &flag->vmem;
                break;
            case 'c':
                flag->cargs = 0;
                last = &flag->cargs;
                break;   
            case '-':
                *last = 0;
                break;
            case '?':
                flag->fail = 1;
                return flag;
        }
    }
    
    // If there is any garbage input, set fail
    if (optind < argc) {
        flag->fail = 1;
    }

    return flag;
}
