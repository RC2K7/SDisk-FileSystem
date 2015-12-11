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
	int buildTable(string);
	int search(string value);
private:
	string flatFile;
	string indexFile;
	
	int indexSearch(string);
};

#endif