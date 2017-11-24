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
#include "../include/Timer.h"
#include "../include/Commons.h"

using namespace std;

#define N_THREADS 1000

struct Thread_data
{
  int id;
  pthread_t thread_id;
  char * host;
  u_short port;
};

void *thread_work(void *arg)
{
  Commons c;
  Thread_data data = *(Thread_data*)arg;

  c.task(data.host, data.port);
  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " host port count\n";
    exit(-1);
  }

  Commons c;
  int count = atoi(argv[3]);
  Thread_data thread_args[count];
  char *host = argv[1];
  u_short port = atoi(argv[2]);

	//Start Timer
	Timer time;
	double eTime;
	time.start();

	//Create Thread and do process
  for (int i = 0; i < count; ++i) {
    Thread_data & t = thread_args[i];
    t.id = i;
    t.host = host;
    t.port = port;
    pthread_create(&t.thread_id, NULL, thread_work, &t);
  }
    
	//Wait for each thread to finish
  for (int i=0; i < count; i++) {
    pthread_join(thread_args[i].thread_id, NULL);
    cout << "Complete thread: " << i << endl;
  }

	//Stop timer and output elapsed time
	time.elapsedUserTime(eTime);
	cout << "Elapsed User Time: " << eTime << endl;

  pthread_exit(0);
}
