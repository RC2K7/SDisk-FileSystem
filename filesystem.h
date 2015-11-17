/*
*	Ruben Castaneda
*	CSE 461
*	Lab 3
*
*	filesystem.h
*/

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "sdisk.h"

#include <string>
#include <vector>

using namespace std;

class FileSystem : public SDisk
{
	public:
		FileSystem(string, int, int);
		int fsClose();
		int fsSynch();
		int newFile(string);
		int rmFile(string);
		int getFirstBlock(string);
		int addBlock(string, string);
		int delBlock(string, int);
		int readBlock(string, int, string&);
		int writeBlock(string, int, string);
		int nextBlock(string, int);
        vector<string> ls();

        static vector<string> block(string, int);
	private:
		int initRoot();
		int initFat();

		// Configurable Variables
		static const char delimiter = ' ';

		int rootSize;
		int fatSize;
		vector<string> rootFileName;
		vector<int> rootFirstBlock;
		vector<int> fat;
};

#endif
