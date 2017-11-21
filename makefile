all: threads processes

threads: clientThreads.o
	g++ -pthread clientThreads.o -o clientThreads

processes: clientProcesses.o
	g++ clientProcesses.o -o clientProcesses

clean: 
	rm -rf *.o threads processes
