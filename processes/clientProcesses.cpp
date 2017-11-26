#include "../include/Commons.h"
#include <sys/wait.h>

using namespace std;

int main (int argc, char *argv[]) {
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " host port count type\n";
    exit(-1);
  }

  Commons c;
  int count = atoi(argv[3]);
  pid_t pid;
  int i;
  char *host = argv[1];
  u_short port = atoi(argv[2]);
  char *reqtype = argv[4];

  // const clock_t begin_time = clock();

  // cout << "START: Parent process PID = " << getpid() << endl;

  for (i = 1; i <= count; i++) {
    switch ( pid = fork() ) {
      case -1:
        cout << "Error in fork";

      case 0:
        // cout << "Child " << i <<" PID = " << getpid() << endl;
        c.task(host, port, reqtype, count);
        // cout << "Elapsed User Time in seconds for PID " << getpid() << "=" << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
        return 0;

      default:
        continue;
    }
  }

  // cout << "Waiting" << endl;
  // Need to wait for all
  for(i=0; i<count; i++){
    wait(0);
    // cout << "Got " << i+1 << " done" << endl;
  }

  // cout << "Total Elapsed User Time in seconds: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
  return 0;
}
