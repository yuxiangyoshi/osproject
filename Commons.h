#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
using namespace std;

class Commons
{
    public:
        sockaddr_in make_server_addr(char *host, u_short port);
        int connect_socket(char *host, u_short port);
        void requestNumFromServer(int server_socket);
        void readNumFromServer(int server_socket);
        void task(char * host, u_short port);
        void executeAdd(char * host, u_short port);
        int COUNT = 10;
        int BUFSIZE = 56;
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
        if (s == -1)
            error("socket()");
        status = connect(s, (sockaddr*)&addr, sizeof addr);
        if (status < 0)
            error("connect refused");
        return s;
    }

    void Commons::requestNumFromServer(int server_socket)
    {
    /*
        int len = strlen(file);
        int n = write(server_socket, file, len);
        if (n != len)
            error("short write");
    */
    }

    void Commons::readNumFromServer(int server_socket)
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

    void Commons::executeAdd(char * host, u_short port)
    {
        int server_socket = connect_socket(host, port);
        requestNumFromServer(server_socket);
        readNumFromServer(server_socket);
        close(server_socket);
    }
 
    void Commons::task(char * host, u_short port)
    {
        executeAdd(host, port);
    }
