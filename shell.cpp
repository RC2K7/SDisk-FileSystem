#include "shell.h"

#include <iostream>
#include <vector>

vector<string> splitString(string buffer);

// Main Constructor
Shell::Shell(string diskName, int numberOfBlocks, int blockSize) : FileSystem(diskName, numberOfBlocks, blockSize)
{
    // Just Some Interesting Styling
    cout << "Interactive DOS Shell Version 0.1" << endl;
    cout << "Copyright 2016 by Ruben Castaneda" << endl;
    cout << "=================================" << endl;
    this->runShell();
}

// Calls LS and Ouptuts All Filenames
int Shell::dir(){
    return 1;
}

// Add File To FileSystem
int Shell::add(string fileName)
{
    return 1;
}

// Delete File From FileSystem
int Shell::del(string fileName)
{
    return 1;
}

// Lists The Contents Of A File (Similiar To 'cat' On Linux)
int Shell::type(string fileName)
{
    return 1;
}

// Copies One File To Another File
int Shell::copy(string src, string dest)
{
    return 1;
}

// Loops The Interactive Shell
void Shell::runShell()
{
    string buffer = "";
    while (1) {
        cout << ">> ";
        getline(cin, buffer);

        vector<string> args = splitString(buffer);

        if (args.size() == 0) {
            cout << "No Command Found" << endl;
            continue;
        }

        // arg[0] Is Our Command, Following Handles All Possible Commands
        if (args[0] == "quit" || args[0] == "q") {
            break;
        } else if (args[0] == "dir") {
            this->dir();
        } else if (args[0] == "add") {
            if (args.size() < 2) { // Handle Incorrect Number Of Arguments
                cout << "Incorrect Number of Arguments" << endl;
                continue;
            }
            this->add(args[1]);
        } else if (args[0] == "del") {
            if (args.size() < 2) { // Handle Incorrect Number Of Arguments
                cout << "Incorrect Number of Arguments" << endl;
                continue;
            }
            this->del(args[1]);
        } else if (args[0] == "type") {
            if (args.size() < 2) { // Handle Incorrect Number Of Arguments
                cout << "Incorrect Number of Arguments" << endl;
                continue;
            }
            this->type(args[1]);
        } else if (args[0] == "copy") {
            if (args.size() < 3) { // Handle Incorrect Number Of Arguments
                cout << "Incorrect Number of Arguments" << endl;
                continue;
            }
            this->copy(args[1], args[2]);
        } else {
            cout << "Unknown Command" << endl;
        }
    }
}

// Splits A String Into A Vector (Splits On Spaces)
vector<string> splitString(string buffer)
{
    vector<string> split;

    size_t begin, end;
    begin = buffer.find_first_not_of(' ');
    end = buffer.find_first_of(' ', begin);

    while (begin != end) {
        split.push_back(buffer.substr(begin, end - begin));
        begin = buffer.find_first_not_of(' ', end);
        end = buffer.find_first_of(' ', begin);
    }

    return split;
}
