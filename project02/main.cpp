#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iterator>

using namespace std;

void getCommand();
int processCommand(string&, char**);
void execCommand();
void runProcess();

const int MAX_PARAMETERS = 125;

int main(int argc, const char* argv[])
{
    cout << "Myshell" << endl;

    string inputString = "";
    char* parameters[MAX_PARAMETERS];
    int numParams = 0;

    bool loop = true;

    while(loop){
        getline(cin, inputString);
        if( inputString == "exit") {
            loop = false;
        }
        else {
            numParams = processCommand(inputString, parameters);

            //for (int i = 0; i < 6; i++) {
                //cout << parameters[i] << endl;
            //}
            execvp(parameters[0], parameters);
        }
    }//end while

    //if(command != NULL) {
        //for (int i = 0; i < numParams; i++) {
            //delete[] command[i];
        //}
        //delete[] command;
    //}

    return 0;
}



void getCommand()
{





}


int processCommand(string &rawCommand, char** commandList)
{
    istringstream convertInput(rawCommand);

    string temp = "";
    // count number of parameters
    int parameterCount = 0;

    while( getline(convertInput, temp, ' ') &&
            (parameterCount < MAX_PARAMETERS - 1) ){

        commandList[parameterCount] = new char[temp.size()];
        strcpy(commandList[parameterCount], temp.c_str());
        parameterCount++;
    }

    commandList[parameterCount] = NULL;

    return parameterCount;
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
