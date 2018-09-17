#ifndef OPPROC_H
#define OPPROC_H

typedef struct flags{
    int pid;
    int state;
    int utime;
    int stime;
    int vmem;
    int cargs;
}flags;

flags* parsecline(int, char**);
#endif
