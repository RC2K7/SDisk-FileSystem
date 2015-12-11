/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	shell.cpp
*/

#include "shell.h"

#include <iostream>
#include <vector>

vector<string> splitString(string buffer);

// Main Constructor
Shell::Shell(string diskName, int numberOfBlocks, int blockSize, string indexFile,
    string flatFile) : Table(diskName, numberOfBlocks, blockSize, indexFile, flatFile)
{
    // Just Some Interesting Styling
    cout << "Interactive DOS Shell Version 0.1" << endl;
    cout << "Copyright 2016 by Ruben Castaneda" << endl;
    cout << "=================================" << endl;
    this->runShell();
}

// Calls LS and Ouptuts All Filenames
int Shell::dir(){
    vector<string> tmp = this->ls();

    for (int i = 0; i < tmp.size(); i++)
        cout << tmp[i] << " ";
    cout << endl;

    return 1;
}

// Add File To FileSystem
int Shell::add(string fileName)
{
    if (this->newFile(fileName)) {
        cout << "Would You Like To Add Data (y/n): ";
        string buffer;
        getline(cin, buffer);
        if (buffer == "y" || buffer == "Y")
            this->append(fileName);
    };
    return 1;
}

// Delete File From FileSystem
int Shell::del(string fileName)
{
    int curBlock = this->getFirstBlock(fileName);

    // Return If File Does Not Exist
    if (curBlock == -1) {
        cout << "Cannot Find File To Remove" << endl;
        return 0;
    }

    // Remove All Blocks From File
    while ((curBlock = this->getFirstBlock(fileName)) > 0)
        this->delBlock(fileName, curBlock);

    // Remove File From Root
    this->rmFile(fileName);

    return 1;
}

// Lists The Contents Of A File (Similiar To 'cat' On Linux)
int Shell::type(string fileName)
{
    string fileBuffer = "";
    string blockBuffer = "";

    for ( int curBlock = getFirstBlock(fileName); curBlock != 0; curBlock = 
        this->nextBlock(fileName, curBlock)) {
        this->readBlock(fileName, curBlock, blockBuffer);
        fileBuffer += blockBuffer;
    }

    //fileBuffer = fileBuffer.substr(0, fileBuffer.find_first_of('#'));

    cout << fileBuffer << endl;

    return 1;
}

// Copies One File To Another File
int Shell::copy(string src, string dest)
{
    if (this->getFirstBlock(src) == -1) {
        cout << "Could Not Find Source File!" << endl;
        return 0;
    } else if (this->getFirstBlock(dest) >= 0) {
        cout << "Destination File Already Exists!" << endl;
        return 0;
    }

    if (this->newFile(dest) == 0) {
        cout << "Could Not Create File" << endl;
        return 0;
    }

    string buffer = "";
    for (int curBlock = this->getFirstBlock(src); curBlock != 0; curBlock =
        this->nextBlock(src, curBlock)) {
        this->readBlock(src, curBlock, buffer);
        this->addBlock(dest, buffer);
    }

    return 1;
}

// Allows The Addition Of Data To A File
int Shell::append(string fileName)
{
    if (getFirstBlock(fileName) == -1) {
        cout << "Could Not Find File" << endl;
        return 0;
    }

    int lastBlock;
    for (lastBlock = this->getFirstBlock(fileName); lastBlock != 0 &&
        this->nextBlock(fileName, lastBlock) != 0; lastBlock = nextBlock(
        fileName, lastBlock)) ;

    string totalBuffer;
    if (lastBlock != 0) {
        this->readBlock(fileName, lastBlock, totalBuffer);
        this->delBlock(fileName, lastBlock);
        totalBuffer = totalBuffer.substr(0, totalBuffer.find_first_of('#'));
    }

    string buffer;
    cout << "Enter Data:" << endl;
    getline(cin, buffer);
    totalBuffer += buffer;

    vector<string> blocks = block(totalBuffer, this->getBlockSize());

    for (int i = 0; i < blocks.size(); i++)
        this->addBlock(fileName, blocks[i]);

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
        } else if (args[0] == "app") {
            if (args.size() < 2) {
                cout << "Inoccrent Number of Arguments" << endl;
                continue;
            }
            this->append(args[1]);
        } else if (args[0] == "table") {
            if (args.size() < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                continue;
            }
            if (args[1] == "input") {
                this->buildTable(args[2]);
            } else if (args[1] == "search") {
                this->search(args[2]);
            } else {
                cout << "Unknown Table Command" << endl;
            }
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
