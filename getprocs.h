#ifndef GETPROCS_H
#define GETPROCS_H

typedef struct Procnode{
    char* pid;
    Procnode* next;
}

Procnode* getproclist();

int getproc(char* pid);

#endif
