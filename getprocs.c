#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define UIDFIELD 6
#define STATUSSIZE 7
#define BUFFSIZE 50

// This Struct acts as a linked list for the process IDs that the user has a matching uid to
typedef struct Procnode{
	char *pid;
	struct Procnode* next;
}Procnode;     

char* strconcat(char* str1, char* str2) {
	char* str3 = (char*) malloc(strlen(str1) + strlen(str2) + 1);
	if (str3 == NULL) {
		fprintf(stderr, "Out of memory\n");
		return NULL;
	}
	strcpy(str3, str1);
	strcat(str3, str2);
	return str3;
}

// This method generates a list of processes that the user has access to
Procnode* getproclist(){
	DIR *procs;  // This object is a pointer to the /proc directory
	DIR *subdir;  // This object keeps track of the current process directory within /proc
	struct dirent *proc_info;  // This object contains the current process directory information
	char *proc = "/proc/";  // Used to help open /proc and its subdirectories
	int uid = getuid();  // Variable that stores the uid of the user
	FILE *uid_find;  // This opens the status file to find the UID of the process
	int uid_line;  // Stores the line containing the UID within status
	char buff[BUFFSIZE];  // Storage for the line within the status file containing the UID
	char *filename;  // Stores the name of the file currently trying to be opened

	Procnode *head = (Procnode*) malloc(sizeof(Procnode));
	Procnode *current = head;

	if ((procs = opendir(proc)) == NULL) {
	free(current);
	free(procs);
		perror("Couldn't open /procs");
		return NULL;
	}

	// Runs a while loop through all the processes as long as it can access them
	do {
		errno = 0;
		if ((proc_info = readdir(procs)) != NULL) {
			char *procdir = strconcat(proc, proc_info->d_name);  // Used to help open a process subdirectory within /proc
			if (procdir == NULL) {
				free(current);
				return NULL;
			}
				
				// Accesses the directory as long as it is not null and not a string
			if((atoi(proc_info->d_name) != 0) && (subdir = opendir(procdir)) != NULL){
				uid_line = 0;
				filename = (char*) malloc(sizeof(procdir) + sizeof(char)*7);
				strcpy(filename, procdir);
				strcat(filename, "/status");

				// Attempts to open the status file within process directory
				uid_find = fopen(filename, "r");
				if(uid_find != NULL){
					while(uid_line < 9){
							fgets(buff, BUFFSIZE, uid_find);
							uid_line++;
					}
					fclose(uid_find);
								 
					// Get the UID from the status file
					char *uidcomp;  // stores the uid obtained from the status file
					char *charptr = buff;  // used to iterate through the line from the status file
					uid_line = 0;

					// Parses the line to retrieve the UID associated with the process
					while((uidcomp = strtok_r(charptr, "\t", &charptr)) != NULL && uid_line < 2){
						// if uid and pid match, return the PID
						if(uid == atoi(uidcomp)){
							// Add the PID to an array to return
							current->pid = malloc(1 + sizeof(proc_info->d_name));
							strcpy(current->pid, proc_info->d_name);
							current->next = malloc(sizeof(Procnode));
							current = current->next;
							current->pid = NULL;
						}
						uid_line++;                             
					}
				}
			
				// Frees the file pointer and close the subdirectory
				free(filename);
				if(closedir(subdir) == -1){
					free(current);
					free(procdir);
					perror("closedir");
					return NULL;
				}
			
			}
			free(procdir);
		}
	} while (proc_info != NULL);

	// Closes /proc
	if(closedir(procs) == -1){
	free(current);
			perror("closedir");
		return NULL;
	}

	return head;
}


int getproc(char* pid){
	DIR *procs;  // This object is a pointer to the /proc directory
	DIR *subdir;  // This object keeps track of the current process directory within /proc
	struct dirent *proc_info;  // This object contains the current process directory information
	char *proc = "/proc/";  // Used to help open /proc and its subdirectories
	FILE *uid_find;  // This opens the status file
	char *filename;  // Stores the name of the file currently trying to be opened

	if ((procs = opendir(proc)) == NULL) {
	free(procs);
		perror("Couldn't open /procs");
		return 0;
	}

	// Runs a while loop through all the processes as long as it can access them
	while((proc_info = readdir(procs)) != NULL){
		if(atoi(pid) == atoi(proc_info->d_name)){
			char* procdir = strconcat(proc, proc_info->d_name);
			if (procdir == NULL) {
				return 0;
			}

			// Accesses the directory as long as it is not null
			if((subdir = opendir(procdir)) != NULL){
				filename = (char*) malloc(sizeof(procdir) + sizeof(char)*STATUSSIZE + 1);
				strcpy(filename, procdir);
				strcat(filename, "/status");

				// Attempts to open the status file within process directory
				uid_find = fopen(filename, "r");
				if(uid_find != NULL){
				// Closes the status file
				fclose(uid_find);
				// Frees the filename pointer
				free(filename);
				if(closedir(subdir) == -1){
					free(procdir);
					perror("closedir");
					return 0;
				}
				// Frees the process directory pointer
				free(procdir);
				// Closes /proc
				if(closedir(procs) == -1){
					perror("closedir");
					return 0;
				}
				return 1;
			}else{
				fclose(uid_find);
				// Frees the filename pointer
				free(filename);
				if(closedir(subdir) == -1){
					free(procdir);
					perror("closedir");
					return 0;
				}
				// Frees the process directory pointer
				free(procdir);
				// Closes /proc
				if(closedir(procs) == -1){
					perror("closedir");
					return 0;
				}
				return 0;
			 }
		
			// Frees the file pointer and close the subdirectory
			free(filename);
			if(closedir(subdir) == -1){
					perror("closedir");
					return 0;
			}
			}
			free(procdir);
		}
	}
	if(closedir(procs) == -1){
		 perror("closedir");
		 return 0;
	}
	return -1;
}

