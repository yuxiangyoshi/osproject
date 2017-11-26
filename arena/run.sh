#!/usr/bin/env bash

set -o xtrace

#EXE=processes
EXE=threads
#TYPE=cpu
#TYPE=balanced
TYPE=io

time ./${EXE} localhost 8888 1 ${TYPE}
time ./${EXE} localhost 8888 2 ${TYPE}
time ./${EXE} localhost 8888 4 ${TYPE}
time ./${EXE} localhost 8888 8 ${TYPE}
time ./${EXE} localhost 8888 16 ${TYPE}
