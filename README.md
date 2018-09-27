# 537ps

Programming assignment for CS 537 at UW-Madison

Written by Logan Mahan and Sam Ware

Assignment details: http://pages.cs.wisc.edu/~bart/537/programs/program1.html

## About

Prints out information about user processes in this form:

\<pid>: \<state> utime=\<user time> stime=\<system time> vmemory=\<virtual memory> [\<command line>]
  
Usage: 537ps -p \<pid> -[sUSvc]

## Modules:

### 537ps.c

The main C file. This calls all the apporpriate methods with the given command line arguments and prints out the correct information. Look at the assignment details for info on what each flag does.

### opproc.c

Parses the command line arguments and sends the results back in a flags struct. The struct has an int for each flag - 1 if the option is to be printed and 0 if not.

### statparse.c

Gets the single-character state information, amount of user time consumed, amount of system time, amount of virtual memory and command-line information from the stat, statm and cmdline files in the proccesses directory.

### getprocs.c

Gets the list of processes with the same UID as the user. Also determines if a given PID exists.
