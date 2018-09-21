#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 128
#define STATEFIELD 3
#define UTIMEFIELD 14
#define STIMEFIELD 15
#define VMEMFIELD 1

/*
* Opens the file at: /proc/<pid>/<filename> where filename is either stat
* or statm
*/
FILE* getfile(char* pid, char* filename)
{
    // Creates a char* with the right format
    char *proc = "/proc/";
    char *proc_dir = (char*) malloc(1 + strlen(proc) + strlen(filename) + strlen(pid));
    strcpy(proc_dir, proc);
    strcat(proc_dir, pid);
    strcat(proc_dir, filename);
    
    FILE *file = fopen(proc_dir, "r");
    free(proc_dir);

    return file;
}

/*
* Calls getfile to open the statm file
*/
FILE* getstatmfile(char* pid)
{
    char *filename = "/statm";
    return getfile(pid, filename);
}

/*
* Calls getfile to open the stat file
*/ 
FILE* getstatfile(char* pid) 
{
    char *filename = "/stat";
    return getfile(pid, filename);
}

/*
* Gets the k-th field in a space delimited list
*/
char* getkfield(FILE* file, int k)
{
    char buff[BUFFSIZE];

    int i;
    
    // Gets the next token in the file k times, so it ends up getting
    // the k-th token
    for (i = 0; i < k; i++)
    {
        fscanf(file, "%s", buff);
    }  

    char *field = malloc(1 + strlen(buff));
    strcpy(field, buff);

    fclose(file);

    return field;
}

/*
* Gets the state of the given process
* Returns NULL on failure
*/
char* getstate(char* pid) 
{
    FILE *stat_file = getstatfile(pid);
    
    if (stat_file == NULL) 
    {
        fprintf(stderr, "Unable to open stat file of proc with id %s\n", pid);
        return NULL;
    }
    
    char* state = getkfield(stat_file, STATEFIELD);    

    return state; 
}

/*
* Gets the utime of the given process
* Returns NULL on failure
*/
char* getutime(char* pid)
{
    FILE *stat_file = getstatfile(pid);

    if (stat_file == NULL) 
    {
        fprintf(stderr, "Unable to open stat file of proc with id %s\n", pid);
        return NULL;
    }

    char *utime = getkfield(stat_file, UTIMEFIELD);
    
    return utime;
}

/*
* Gets the stime of the given process
* Returns NULL on failure
*/
char* getstime(char* pid)
{
    FILE *stat_file = getstatfile(pid);

    if (stat_file == NULL) 
    {
        fprintf(stderr, "Unable to open stat file of proc with id %s\n", pid);
        return NULL;
    }

    char *stime = getkfield(stat_file, STIMEFIELD);

    return stime;
}

/*
* Gets the svmem of the given process
* Returns NULL on failure
*/
char* getvmem(char* pid)
{
    FILE *statm_file = getstatmfile(pid);

    if (statm_file == NULL) 
    {
        fprintf(stderr, "Unable to open statm file of proc with id %s\n", pid);
        return NULL;
    }

    char* vmem = getkfield(statm_file, VMEMFIELD);

    return vmem;
}
