#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "sdisk.h"

#include <string>
#include <vector>

using namespace std;

class FileSystem : public SDisk
{
	public:
		FileSystem();
		int fsClose();
		int fsSynch();
		int newFile(string);
		int rmFile(string);
		int getFirstBlock(string);
		int addBlock(string);
		int delBlock(string);
		int readBlock(string, int, string&);
		int writeBlock(string, int, string);
		int nextBlock(string, int);
	private:
		int rootSize;
		int fatSize;
		vector<string> rootFileName;
		vector<int> rootFirstBlock;
		vector<int> fat;
};

#endif