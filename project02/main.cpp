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
int parseCommand(string&, char**);
bool runLocalProcess(char**);
void runProcess(char**);

const int MAX_PARAMETERS = 125;

int main(int argc, const char* argv[])
{
    cout << "Myshell" << endl;

    string inputString = "";
    char* parameters[MAX_PARAMETERS];
    int numParams = 0;

    bool loop = true;

    while(loop){
        //cout << "> ";
        getline(cin, inputString);
        //cout << endl;

        if( inputString == "exit") {
            loop = false;
        }
        else {
            numParams = parseCommand(inputString, parameters);

            if (!runLocalProcess(parameters)) {
                runProcess(parameters);
            }

            // if exec returns, it failed to execute
            // TODO: exec will need to be called in forked process
            // so that memory is correctly deallocated in main process
        }
    }//end while

    for (int i = 0; i < numParams; i++) {
        if(parameters[i] != NULL) {
            delete[] parameters[i];
        }
    }

    return 0;
}

void getCommand()
{

}

int parseCommand(string &rawCommand, char** commandList)
{
    istringstream convertInput(rawCommand);

    string temp = "";
    // count number of parameters
    int parameterCount = 0;

    while( getline(convertInput, temp, ' ') &&
            (parameterCount < MAX_PARAMETERS - 1) ){

        commandList[parameterCount] = new char[temp.size() + 1];
        strcpy(commandList[parameterCount], temp.c_str());
        parameterCount++;
    }

    commandList[parameterCount] = NULL;

    return parameterCount;
}

bool runLocalProcess(char** commandList)
{

    if ( strcmp(commandList[0], "pushd") == 0 ) {
        return true;
    }
    else if ( strcmp(commandList[0], "popd") == 0 ) {
        return true;
    }
    else if ( strcmp(commandList[0], "dirs") == 0 ) {
        return true;
    }
    else if ( strcmp(commandList[0], "cd") == 0 ) {
        return true;
    }

    return false;
}

void runProcess(char** commandList)
{
    pid_t  pid;
    /* fork another process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        cerr << "Fork Failed" << endl;
        exit(-1);
    }
    else if (pid == 0) { /* child process */
        execvp(commandList[0], commandList);
        cout << "Unknown Command" << endl;
        exit(0);
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait();
        //exit(0);
    }
}
