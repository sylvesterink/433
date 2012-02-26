#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <cstring>
#include <cstdlib>
#include <errno.h>

using namespace std;

int parseCommand(string&, char**);
bool runLocalProcess(char**, vector<string>&);
void cmdPushd(char*, vector<string>&);
void cmdPopd(vector<string>&);
void cmdDirs(vector<string>&);
bool cmdCd(const char*);

void runProcess(char**);

const int MAX_PARAMETERS = 125;

int main(int argc, const char* argv[])
{
    cout << "Myshell" << endl;

    string inputString = "";
    char* parameters[MAX_PARAMETERS];

    //Validate array
    for(int i = 0; i < MAX_PARAMETERS; i++) {
      parameters[i] = NULL;
    }

    //int numParams = 0; no longer needed

    vector<string> directoryStack;

    bool loop = true;

    string temp = "";

    while(loop){
        //cout << "> ";
        getline(cin, inputString);
        //cout << endl;
	if(inputString == "") { //Only new line was entered
	  continue; //I still think this is better than another nested else if
	}
        if( inputString == "exit") {
            loop = false;
        }
        else {
            parseCommand(inputString, parameters);
	    if (!runLocalProcess(parameters, directoryStack)) {
	      runProcess(parameters);
	    }
            // if exec returns, it failed to execute
            // TODO: exec will need to be called in forked process
            // so that memory is correctly deallocated in main process
        }
    }//end while

    
    for (int i = 0; i < MAX_PARAMETERS; i++) {
        if(parameters[i] != NULL) {
            delete[] parameters[i];
        }
    }

    return 0;
}

int parseCommand(string &rawCommand, char** commandList)
{
    istringstream convertInput(rawCommand);

    string temp = "";
    // count number of parameters
    int parameterCount = 0;

    while( getline(convertInput, temp, ' ') &&
            (parameterCount < MAX_PARAMETERS - 1) ){
      //      cout << temp << endl;
        commandList[parameterCount] = new char[temp.size() + 1];
        strcpy(commandList[parameterCount], temp.c_str());
        parameterCount++;
    }

    commandList[parameterCount] = NULL;

    return parameterCount;
}

//TODO: add if statement to test if commandlist[1] is null
bool runLocalProcess(char** commandList, vector<string>& directoryStack)
{
    if ( strcmp(commandList[0], "pushd") == 0 ) {
        cmdPushd(commandList[1], directoryStack);
        return true;
    }
    else if ( strcmp(commandList[0], "popd") == 0 ) {
        cmdPopd(directoryStack);
        return true;
    }
    else if ( strcmp(commandList[0], "dirs") == 0 ) {
        cmdDirs(directoryStack);
        return true;
    }
    else if ( strcmp(commandList[0], "cd") == 0 ) {
        cmdCd(commandList[1]);
        return true;
    }

    return false;
}

void cmdPushd(char* directory, vector<string>& directoryStack)
{
    size_t strSize = 100;
    string strCurrDirectory = "";
    bool loop = true;

    while (loop) {
        char* currentDirectory = (char *) malloc (strSize);

        if (getcwd(currentDirectory, strSize) == currentDirectory) {
            strCurrDirectory = currentDirectory;

            if (cmdCd(directory) == true) {
                directoryStack.push_back(strCurrDirectory);
            }
        }

        free( currentDirectory );
        loop = false;

        // If path was too large to fit in allocated string using getcwd
        // and size to allocate isn't too big, increase allocation size
        if ((errno == ERANGE) && (strSize < 1000)) {
            strSize *= 2;
            loop = true;
        }
    }
}

void cmdPopd(vector<string>& directoryStack)
{
    if (directoryStack.empty()) {
        cout << "Stack is empty" << endl;
    }
    else {
        string directory = directoryStack.back();
        directoryStack.pop_back();
        cmdCd(directory.c_str());
    }
}

void cmdDirs(vector<string>& directoryStack)
{
    for (unsigned int i = 0; i < directoryStack.size(); i++) {
        cout << directoryStack[i] << endl;
    }
}

bool cmdCd(const char* directory)
{
    //TODO: make sure argument is valid
    //      may not need to, as chdir already checks
    if ( chdir(directory) != 0) {
        cout << "Unable to change directory" << endl;
        return false;
    }

    return true;
}

void runProcess(char** commandList)
{
    pid_t  pid;
    // fork another process
    pid = fork();

    if (pid < 0) { // error occurred
        cerr << "Fork Failed" << endl;
        exit(-1);
    }
    else if (pid == 0) { // child process
        execvp(commandList[0], commandList);
        cout << "Unknown Command" << endl;
        exit(0);
    }
    else { // parent process
        // parent will wait for the child to complete
        wait();
    }
}
