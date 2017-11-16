#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Timer.h"

using namespace std;
#define N_PROCESS 10

void *executeAdd(int num){
    cout << "Number:" << num << endl;
}
void *process_work(int num)
{
    executeAdd(num);
}

int main (){
 pid_t pid;
 int i;
 Timer time;
 double eTime;
 time.start();   
 cout << "START: Parent process PID = " << getpid() << endl;

 for (i = 1; i <= N_PROCESS; i++)
  switch ( pid = fork() ) {
  case -1:
    cout << "Error in fork";

  case 0:
    cout << "Child " <<i <<" PID = " << getpid() << endl;
    process_work(i*10000);
    time.elapsedUserTime(eTime);
    cout << "Child " <<i <<" Elapsed User Time: " << eTime << endl;
    return 0;

  default:
  cout << "Parent Process Elapsed User Time: " << eTime << endl;
 }  
 return 0;
 }