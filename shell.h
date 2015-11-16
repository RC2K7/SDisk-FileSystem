/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	shell.h
*/

#ifndef SHELL_H
#define SHELL_H

class Shell
{
	Shell(string, int, int);
    int dir();
    int add(string);
    int del(string);
    int type(string);
    int copy(string);
};

#endif
