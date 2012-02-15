#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(int argc, const char* argv[])
{

  cout << "Myshell" << endl;
  char inputString[256];
  string command = "";

  while(true){
    cin.getline(inputString, 256);
    if(strcmp(inputString, "exit") == 0)
      exit(0);

  }//end while







  return 0;
}



void getCommand()
{





}


void processCommand()
{



}

void execCommand()
{


}


void runProcess()
{
  pid_t  pid;
  /* fork another process */
  pid = fork();

  if (pid < 0) { /* error occurred */
    cerr << "Fork Failed" << endl;
    exit(-1);
  }
  else if (pid == 0) { /* child process */
    cout << "executing child" << endl;
    execlp("/bin/ls", "ls", NULL);
  }
  else { /* parent process */
      /* parent will wait for the child to complete */
      wait();
      cout << "Child Complete" << endl;
      //exit(0);
  }



}
