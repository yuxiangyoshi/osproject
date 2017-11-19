#include "Timer.h"
#include "Commons.h"

using namespace std;

int main () {
  Commons c;
  pid_t pid;
  int i;

  Timer time;
  double eTime;
  time.start();   

  cout << "START: Parent process PID = " << getpid() << endl;

  for (i = 1; i <= c.COUNT; i++)
    switch ( pid = fork() ) {
      case -1:
        cout << "Error in fork";

      case 0:
        cout << "Child " <<i <<" PID = " << getpid() << endl;
        c.task("localhost", 8888);
        time.elapsedUserTime(eTime);
        cout << "Child " <<i <<" Elapsed User Time: " << eTime << endl;
        return 0;

      default:
        cout << "Parent Process Elapsed User Time: " << eTime << endl;
    }  

  return 0;
}
