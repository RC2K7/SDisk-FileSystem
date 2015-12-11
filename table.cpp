#include "table.h"

#include <iostream>
#include <fstream>

Table::Table(string diskName, int blockNumbers, int blockSize, string indexFile,
	string flatFile) : FileSystem(diskName, blockNumbers, blockSize)
{
	this->flatFile = flatFile;
	this->indexFile = indexFile;

	if (this->getFirstBlock(this->flatFile) == -1)
		this->newFile(flatFile);
	if (this->getFirstBlock(this->indexFile) == -1)
		this->newFile(indexFile);
}

int Table::buildTable(string inputFile)
{
	ifstream inFile(inputFile);

	if (inFile.bad()) {
		cout << "Could Not Open File" << endl;
		return 0;
	}

	string buffer;
	
	while (getline(inFile, buffer)) {
		vector<string> blocks = block(buffer, this->getBlockSize());
		this->addBlock(this->flatFile, blocks[0]);
	}

	inFile.close();
	return 1;
}

int Table::search(string value)
{
	return 1;
}
	
int Table::indexSearch(string value)
{
	return 1;
}