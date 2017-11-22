#include "../include/Timer.h"
#include "../include/Commons.h"

using namespace std;

int main () {
  char serverAddress[] = "localhost";

  Commons c;
  pid_t pid;
  int i;

  Timer time;
  double eTime;
  time.start();   

  cout << "START: Parent process PID = " << getpid() << endl;

  for (i = 1; i <= COUNT; i++)
    switch ( pid = fork() ) {
      case -1:
        cout << "Error in fork";

      case 0:
        cout << "Child " <<i <<" PID = " << getpid() << endl;
        c.task(serverAddress, 8888);
        time.elapsedUserTime(eTime);
        return 0;

      default:
        continue;
    }  
    cout << "Total Elapsed User Time: " << eTime << endl;
}
