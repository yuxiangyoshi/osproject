all: threads processes

threads: threads/clientThreads.o
	g++ -pthread threads/clientThreads.o -o threads/clientThreads

processes: processes/clientProcesses.o
	g++ processes/clientProcesses.o -o processes/clientProcesses

clean: 
	rm threads/*.o threads/clientThreads processes/*.o processes/clientProcesses
