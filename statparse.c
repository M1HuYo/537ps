#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 255
#define STATEFIELD 3
#define UTIMEFIELD 14
#define STIMEFIELD 15
#define VMEMFIELD 1

/*
* Opens the file at: /proc/<pid>/<filename> where filename is either stat
* or statm or cmdline
*/
FILE* getfile(char* pid, char* filename)
{
    // Creates a char* with the right format
    char *proc = "/proc/";
    char *proc_dir = (char*) malloc(1 + strlen(proc) + strlen(filename) + strlen(pid));
    if(proc_dir == NULL) {
        fprintf(stderr, "Out of memory\n");
        return NULL;
    }
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
* Calls getfile to open the cmdline file
*/
FILE* getcmdlinefile(char* pid)
{
    char *filename = "/cmdline";
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
    if (field == NULL) {
        fprintf(stderr, "Out of memory\n");
        return NULL;
    }
    strcpy(field, buff);

    if (fclose(file) == -1) {
        free(field);
        fprintf(stderr, "Unable to close stat/statm/cmdline file\n");
        return NULL;
    }
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

    char *vmem = getkfield(statm_file, VMEMFIELD);

    return vmem;
}

/*
* Gets the cmdline file of the given process
* Returns NULL on failure
*/
char* getcmdline(char* pid)
{
    FILE *cmdline_file = getcmdlinefile(pid);
    
    if (cmdline_file == NULL) 
    {
        fprintf(stderr, "Unable to open cmdline file of proc with id %s\n", pid);
        return NULL;
    }

    char* buff = malloc(sizeof(char) * BUFFSIZE);	

    int i;
    int c;
    for (i = 0; i < BUFFSIZE; i++) {
        c = fgetc(cmdline_file);
        buff[i] = c;
        if (c == 0)
            break;
    }        

    char* cmdline = malloc(1 + strlen(buff));
    if (cmdline == NULL) {
        fprintf(stderr, "Out of memory\n");
    } else{ 
	if(buff != NULL){
	    strcpy(cmdline, buff);
	}
    }

    if (fclose(cmdline_file) == -1) {
	free(cmdline);
	free(buff);
        fprintf(stderr, "Unable to close stat/statm/cmdline file\n");
        return NULL;
    }

    free(buff);
    return cmdline;
}
