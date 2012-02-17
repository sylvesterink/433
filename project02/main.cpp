#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iterator>

using namespace std;

void getCommand();
void processCommand(string&, char**);
void execCommand();
void runProcess();

const int MAX_PARAMETERS = 125;
const int MAX_LINE_SIZE = 256;

int main(int argc, const char* argv[])
{

  cout << "Myshell" << endl;
  char input[MAX_LINE_SIZE];
  string inputString = "";
  char** command = NULL;
  for(int j = 0; j < MAX_PARAMETERS; j++){
    command[j] = "";
  }
  
  while(true){
    cin.getline(input, 256);
    if(strcmp(input, "exit") == 0)
      exit(0);
    inputString = input;
    processCommand(inputString, command);

    //execv("/bin/ls", command);
    //for(int i = 0; i < 125; i++) {
    //  cout << command[i] << endl;
    // }
    cout << command[0] << endl;
  }//end while





  if(commandList != NULL)
    delete *commandList;

  return 0;
}



void getCommand()
{





}


void processCommand(string &rawCommand, char** commandList)
{
  istringstream convertInput(rawCommand);
  vector<string> commandVector;
  string temp = "";
  //int counter = 0;
  while( getline(convertInput, temp, ' ') ){
    commandVector.add(temp);
  }
  *commandList = new char[commandVector.size() + 1]; 
  for(int i = 0; i < commandVector.size() + 1; i++) {
    commandList[i] = commandVector[i].c_str();
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
