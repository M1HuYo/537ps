#ifndef OPPROC_H
#define OPPROC_H

typedef struct flags{
    int pid_f;
    char* pid;
    int state;
    int utime;
    int stime;
    int vmem;
    int cargs;
    int fail;
}flags;

flags* parsecline(int, char**);
#endif
