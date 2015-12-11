/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	shell.h
*/

#ifndef SHELL_H
#define SHELL_H

#include "table.h"

#include <string>

using namespace std;

class Shell : public Table
{
public:
	Shell(string, int, int, string, string);
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
