/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	shell.h
*/

#include <string>

#include "filesystem.h"

using namespace std;

#ifndef SHELL_H
#define SHELL_H

class Shell : public FileSystem
{
public:
	Shell(string, int, int);
    int dir();
    int add(string);
    int del(string);
    int type(string);
    int copy(string, string);

    // Custom Functions Because I Can
    int append(string);

private:
    void runShell();
};

#endif
