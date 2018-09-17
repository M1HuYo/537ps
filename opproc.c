#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Struct that holds whether or not the options are to be used
typedef struct flags{
    int pid;
    int state;
    int utime;
    int stime;
    int vmem;
    int cargs;
}flags;

/*
* Parses command line input for specific options
*/
flags* parsecline(int argc, char *argv[]) 
{    
    int option;
    opterr = 0; //Turns off getopt error messages

    flags *flag = malloc(sizeof(flags));
    if (flag == NULL)
    {
        fprintf(stderr, "Out of memory");
        return NULL;
    }     

    flag->pid = 0;
    flag->state = 0;
    flag->utime = 1;
    flag->stime = 0;
    flag->vmem = 0;
    flag->cargs = 1;
    
    int *last; //Holds the last option flag so it can set it to 
               //false when '-' is used

    while ((option = getopt(argc, argv, "p:sUSvc-")) != -1) 
    {
        switch(option)
        {
            case 'p':
                flag->pid = atoi(optarg);
                last = &flag->pid;
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
                
                break;
        }
    }
    
    return flag;
}
