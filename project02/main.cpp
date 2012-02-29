/**
 * @file main.cpp
 * @brief A simple command line shell implementation.
 *        Implements cd, pushd, popd, and dirs internally.
 *        All other commands are passed to the OS.
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-02-29
 * @course CS433
 * @assignment 2
 * @compilation make
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <cstring>
#include <cstdlib>

// These need to be explicitely stated to call the correct functions,
// most notably, wait(), or waitpid()
#include <errno.h>
#include <wait.h>

using namespace std;

// Function Declarations
int parseCommand(string&, char**);
bool runLocalProcess(char**, vector<string>&);
void cmdPushd(char*, vector<string>&);
void cmdPopd(vector<string>&);
void cmdDirs(vector<string>&);
bool cmdCd(const char*);
void runProcess(char**);

// Constant Declarations
const int MAX_PARAMETERS = 125;

/**
 * @brief Main function. Gets input, parses input, and runs the command
 * @param argc Number of parameters passed
 * @param argv[] Program parameters
 * @return Success or failure of program
 */
int main(int argc, const char* argv[])
{
    // Variables to hold the raw and parsed input
    string inputString = "";
    char* parameters[MAX_PARAMETERS];
    // Number of allocated parameters, used for deletion
    int numParams = 0;

    // To hold the directory location when stored by pushd
    vector<string> directoryStack;

    cout << "Myshell" << endl;

    // Keep looping through the program until exit is called
    bool loop = true;
    while(loop){
        // Get input
        cout << endl;
        cout << "> ";
        getline(cin, inputString);

        if( inputString == "exit") {
            loop = false;
        }
        // Make sure the input is valid
        else if (!inputString.empty())
        {
            // Parse the input string and divide it into parameters
            numParams = parseCommand(inputString, parameters);

            // If the command is not one that can't be run locally,
            // execute a nonlocal process
            if (!runLocalProcess(parameters, directoryStack)) {
                runProcess(parameters);
            }

            // Once complete, deallocate the memory allocated for
            // the parameter strings
            for (int i = 0; i < numParams; i++) {
                if(parameters[i] != NULL) {
                    delete[] parameters[i];
                }
            }
        }
    }//end while

    return 0;
}

/**
 * @brief Tokenizes the raw input and stores it into the command list
 * @param rawCommand The raw, untokenized input
 * @param commandList An array of character strings, each containing a token
 * @return The number of tokens in the list
 */
int parseCommand(string &rawCommand, char** commandList)
{
    // Using the C++ tokenizer
    istringstream convertInput(rawCommand);

    // Holding value for each token
    string temp = "";
    // count number of parameters
    int parameterCount = 0;

    // While there's another token, and we don't go beyond the max list size
    // Allocate the memory required and add it to the token array.
    while( getline(convertInput, temp, ' ') &&
            (parameterCount < MAX_PARAMETERS - 1) ){

        // This is deallocated in main.  Not ideal, but manageable for now
        commandList[parameterCount] = new char[temp.size() + 1];
        strcpy(commandList[parameterCount], temp.c_str());
        // Count the number of tokens
        parameterCount++;
    }

    // Token count is 1 greater than number of tokens
    // The execute function requires a NULL value for the last item
    commandList[parameterCount] = NULL;

    return parameterCount;
}

//TODO: add if statement to test if commandlist[1] is null
/**
 * @brief Checks if the command is a locally implemented and call it if so
 * @param commandList The command (location 0) and its following parameters
 * @param directoryStack The list of paths, used by pushd, popd, dirs
 * @return Whether a local process was executed
 */
bool runLocalProcess(char** commandList, vector<string>& directoryStack)
{
    // If the command is local, call it, otherwise return false
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

/**
 * @brief Executes the pushd command.  Changes to the required directory
 *        and pushes the location of the old directory to the stack.
 * @param directory The directory to change to
 * @param directoryStack The stack to add the previous directory to
 */
void cmdPushd(char* directory, vector<string>& directoryStack)
{
    // The starting size of the string to allocate.
    size_t strSize = 100;
    string strCurrDirectory = "";

    // Loop until we are able to store the current path, or if the path size
    // limit is reached.
    bool loop = true;
    while (loop) {
        // Allocate the string to store the path
        char* currentDirectory = (char *) malloc (strSize);

        // Get the current path via system call.  If we were able to
        // acquire the path, cd to the required directory, and push the
        // old directory to the stack
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

/**
 * @brief Change to the directory stored at the top of the directory stack
 * @param directoryStack The stack containing all previously stored directories
 */
void cmdPopd(vector<string>& directoryStack)
{
    // Make sure stack isn't empty
    if (directoryStack.empty()) {
        cout << "Stack is empty" << endl;
    }
    else {
        // Remove the last item from the stack, call CD
        string directory = directoryStack.back();
        directoryStack.pop_back();
        cmdCd(directory.c_str());
    }
}

/**
 * @brief List all the directories stored on the stack
 * @param directoryStack The stack storing the directories
 */
void cmdDirs(vector<string>& directoryStack)
{
    for (unsigned int i = 0; i < directoryStack.size(); i++) {
        cout << directoryStack[i] << endl;
    }
}

/**
 * @brief Change current directory to the directory specified
 * @param directory Directory to change to
 * @return Whether directory change was successful
 */
bool cmdCd(const char* directory)
{
    // chdir checks if directory being changed to is valid
    if ( chdir(directory) != 0) {
        cout << "Unable to change directory" << endl;
        return false;
    }

    return true;
}

/**
 * @brief Run a nonlocal process by forking this process and calling exec
 * @param commandList The command to execute and its required parameters
 */
void runProcess(char** commandList)
{
    // id of the child process
    pid_t  pid;
    // fork another process
    pid = fork();

    // error occurred when forking
    if (pid < 0) {
        cerr << "Fork Failed" << endl;
        exit(-1);
    }
    // child process executes this code
    else if (pid == 0) {
        // Execute the nonlocal process with associated parameters
        execvp(commandList[0], commandList);
        // If this part of code is reached, the command did not exist
        // Otherwise the child process would have terminated after exec
        // Give an error and exit the child.
        cout << "Unknown Command" << endl;
        exit(0);
    }
    // parent process executes this code
    else {
        // parent will wait for the child to complete
        waitpid(pid, 0,0);
    }
}
