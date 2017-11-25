#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>

using namespace std;

static const int COUNT = 100;
static const int BUFSIZE = 56;
static const char *typeRequest[] = {"cpu", "balanced", "io", "end"};

class Commons
{
    public:
        sockaddr_in make_server_addr(char *host, u_short port);
        int connect_socket(char *host, u_short port);
        void requestNumFromServer(int server_socket, char *request);
        void readNumFromServer(int server_socket, int *response);
        void task(char * host, u_short port, char * reqType);
        void executeSummation(char * host, u_short port, char * reqType);

    private:
       void error(char *msg);     
};    

void Commons::error(char *msg)
{
    perror(msg);
    exit(-1);
}

sockaddr_in Commons::make_server_addr(char * host, u_short port)
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

int Commons::connect_socket(char * host, u_short port)
{
    int status;
    int tries = 3;

    sockaddr_in addr = make_server_addr(host, port);
    int s = socket(AF_INET, SOCK_STREAM, 0);

    if (s == -1) {
        char errMsg[] = "connect refused";
        error(errMsg);
    }

    status = connect(s, (sockaddr*)&addr, sizeof addr);

    if (status < 0) {
        char errMsg[] = "connect refused";
        error(errMsg);
    }

    return s;
}

void Commons::requestNumFromServer(int server_socket, char *request)
{
    int len = strlen(request);
    int n = write(server_socket, request, len);

    if (n != len) {
        char errMsg[] = "short write";
        error(errMsg);
    }
}

void Commons::readNumFromServer(int server_socket, int *response)
{
    char buf[BUFSIZE];
    int n;
  
    n = read(server_socket, buf, BUFSIZE);
    *response = atoi(buf);
}

void Commons::executeSummation(char * host, u_short port, char * reqType)
{
    int server_socket;
    char *request;
    int response;

    srand( time(NULL) );

    if (strcmp(reqType, typeRequest[0]) == 0)  
      request = (char *) typeRequest[0];
    else if (strcmp(reqType, typeRequest[1]) == 0)  
      request = (char *) typeRequest[1];
    else if (strcmp(reqType, typeRequest[2]) == 0)  
      request = (char *) typeRequest[2];
    else {
        char errMsg[] = "invalid request";
        error(errMsg);
        return;
    }

    server_socket = connect_socket(host, port);
    requestNumFromServer(server_socket, request);
    readNumFromServer(server_socket, &response);

    long sum = 0;
    for (int i=1; i<=response; i++) {
      sum += i;
    }

    printf("%s, %ld\n", request, sum);

    request = (char *) typeRequest[3];
    requestNumFromServer(server_socket, request);
    close(server_socket);
}

void Commons::task(char * host, u_short port, char * reqType)
{
    executeSummation(host, port, reqType);
}
