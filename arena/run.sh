#!/usr/bin/env bash

set -o xtrace

#EXE=processes
EXE=threads
#TYPE=cpu
#TYPE=balanced
#TYPE=io

for TYPE in balanced io
do
	time ./${EXE} localhost 8888 512 ${TYPE}
done
