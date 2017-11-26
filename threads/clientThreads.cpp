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
  char * reqtype;
  int count;
};

void *thread_work(void *arg)
{
  Commons c;
  Thread_data data = *(Thread_data*)arg;

  c.task(data.host, data.port, data.reqtype, data.count);
  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " host port count type\n";
    exit(-1);
  }

  int count = atoi(argv[3]);
  Thread_data thread_args[count];
  char *host = argv[1];
  u_short port = atoi(argv[2]);
  char *reqtype = argv[4];

	// Start Timer
  // const clock_t begin_time = clock();

	// Create Thread and do process
  for (int i = 0; i < count; ++i) {
    Thread_data & t = thread_args[i];
    t.id = i;
    t.host = host;
    t.port = port;
    t.reqtype = reqtype;
    t.count = count;
    pthread_create(&t.thread_id, NULL, thread_work, &t);
  }

	// Wait for each thread to finish
  for (int i=0; i < count; i++) {
    pthread_join(thread_args[i].thread_id, NULL);
    // cout << "Complete thread: " << i << endl;
  }

	// Stop timer and output elapsed time
  // cout << "Total Elapsed User Time in seconds: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

  pthread_exit(0);
}
