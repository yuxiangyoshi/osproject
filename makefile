all: server client threads

server: server.o
	gcc server.o -o server

client: client.o
	gcc client.o -o client

threads: clientThreads.o
	g++ client.o -o clientThreads

clean: 
	rm -rf *.o server client
