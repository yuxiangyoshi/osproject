#include <stdio.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <iostream>
#include <string.h>
#include "Timer.h"
using namespace std;

#define N_THREADS 10
#define BUFSIZ 56

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

sockaddr_in make_server_addr(char *host, u_short port)
{
    sockaddr_in addr;
    bzero(&addr, sizeof addr);
    hostent *hp = gethostbyname(host);
    if (hp == 0)
    {
        herror(host);
        exit(-1);
    }
    addr.sin_family = AF_INET;
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    return addr;
}

int connect_socket(char *host, u_short port)
{
    int status;
    int tries = 3;
    sockaddr_in addr = make_server_addr(host, port);
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("socket()");
    status = connect(s, (sockaddr*)&addr, sizeof addr);
    if (status < 0)
        error("connect refused");
    return s;
}

void requestNumFromServer(int server_socket)
{
/*
    int len = strlen(file);
    int n = write(server_socket, file, len);
    if (n != len)
        error("short write");
*/
}

void readNumFromServer(int server_socket)
{
/*
    char buf[BUFSIZ];
    int n;
    mode_t mode = 0666;
    int ofd = open(file, O_WRONLY | O_CREAT, mode);
    if (ofd == -1)
        perror("open()");
    while ((n = read(server_socket, buf, BUFSIZ)) > 0)
        write(ofd, buf, n);
    close(ofd);
*/
}


struct Thread_data
{
    int id;
    pthread_t thread_id;
    char * host;
    u_short port;
    char path[BUFSIZ];
};

int executeAdd(Thread_data & data)
{
    int server_socket = connect_socket(data.host, data.port);
    requestNumFromServer(server_socket);
    readNumFromServer(server_socket);
    close(server_socket);
}

void *thread_work(void *arg)
{
    Thread_data data = *(Thread_data*)arg;
    executeAdd(data);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " host port\n";
        exit(-1);
    }

    char *host = argv[1];
    u_short port = atoi(argv[2]);
    Thread_data thread_args[N_THREADS];

	//Start Timer
	Timer time;
	double eTime;
	time.start();

	//Create Thread and do process
    for (int i = 0; i < N_THREADS; ++i)
    {

        Thread_data & t = thread_args[i];
        t.id = i;
        t.host = host;
        t.port = port;
        pthread_create(&t.thread_id, NULL, thread_work, &t);
    }
    
	//Wait for each thread to finish
    for (int i=0; i < N_THREADS; i++)
        pthread_join(thread_args[i].thread_id, NULL);

	//Stop timer and output elapsed time
	time.elapsedUserTime(eTime);
	cout << "Elapsed User Time: " << eTime << endl;

    pthread_exit(0);
}
