all: server client

server: server.o
	gcc server.o -o server

client: client.o
	gcc client.o -o client

threads: clientThreads.o
	g++ -pthread clientThreads.o -o clientThreads

processes: clientProcesses.o
	g++ clientProcesses.o -o clientProcesses

clean: 
	rm -rf *.o server client threads processes
