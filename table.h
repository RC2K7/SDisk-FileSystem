/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	shell.h
*/

#ifndef TABLE_H
#define TABLE_H

#include "Filesystem.h"

class Table : public FileSystem {
public:
	Table(string, int, int, string, string);
	int Build_Table(string);
	int Search(string value);
private:
	string flatFile;
	string indexFile;
	
	int IndexSearch(string);
};

#endif