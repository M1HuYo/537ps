#ifndef GETPROCS_H
#define GETPROCS_H

typedef struct Procnode{
    char* pid;
    struct Procnode* next;
}Procnode;

Procnode* getproclist();

int getproc(char*);

#endif
