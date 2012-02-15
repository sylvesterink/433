#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iterator>

using namespace std;

void getCommand();
void processCommand(string&, string[]);
void execCommand();
void runProcess();

int main(int argc, const char* argv[])
{

  cout << "Myshell" << endl;
  char input[256];
  string inputString = "";
  string command[125];
  
  while(true){
    cin.getline(input, 256);
    if(strcmp(input, "exit") == 0)
      exit(0);
    inputString = input;
    processCommand(inputString, command);
    for(int i = 0; i < 125; i++) {
      cout << command[i] << endl;
    }
  }//end while







  return 0;
}



void getCommand()
{





}


void processCommand(string &rawCommand, string commandList[])
{
  istringstream convertInput(rawCommand);
  string temp = "";
  int counter = 0;
  while( getline(convertInput, commandList[counter], ' ') ){
   counter++;
  }
   //cout << temp << endl;  

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
