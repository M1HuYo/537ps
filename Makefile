CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps

all: main.o getprocs.o opproc.o statparse.o
	$(CC) -o $(EXE) main.o getprocs.o opproc.o statparse.o

main.o: main.c getprocs.h opproc.h statparse.h
	$(CC) $(WARNING_FLAGS) -c main.c

getprocs.o: getprocs.c getprocs.h
	$(CC) $(WARNING_FLAGS) -c getprocs.c
  
opproc.o: opproc.c opproc.h
	$(CC) $(WARNING_FLAGS) -c opproc.c

statparse.o: statparse.c statparse.h
	$(CC) $(WARNING_FLAGS) -c statparse.c

clean:
	rm $(EXE) *.o

