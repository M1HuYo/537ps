#include <stdio.h>
#include "getprocs.h"
#include "opproc.h"
#include "statparse.h"

int main(int argc, char** argv) {

    flags* opts = parsecline(argc, argv);

    if (opts == NULL) {
        return 0;
    }
    if (opts->pid_f == 1) {

    } else {
        Procnode *procs = getproclist();
    }
}

