#include "table.h"
#include "util.h"

#include <iostream>
#include <iomanip>
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
	this->indexSearch(value);
	return 1;
}
	
int Table::indexSearch(string value)
{
	cout << "+" << right << setfill('-') << setw(139) << "+" << left << endl;
	cout << "|" << setfill(' ') << setw(5) << "Date" << "|"
		<< setw(5) << "End" << "|"
		<< setw(8) << "Type" << "|"
		<< setw(15) << "Place" << "|"
		<< setw(7) << "Ref" << "|"
		<< setw(93) << "Description" << "|" << endl
		<< "+" << right << setfill('-') << setw(139) << "+" << left << endl;

	for (int curBlock = this->getFirstBlock(this->flatFile); curBlock != 0; 
		curBlock = this->nextBlock(this->flatFile, curBlock)) {
		string buffer;
		this->readBlock(this->flatFile, curBlock, buffer);
		string date = buffer.substr(0, buffer.find_first_of(" *"));
		buffer = buffer.substr(0, buffer.find_first_of('#'));
		if (value == date) {
			vector<string> split = Util::splitString(buffer, '*');
			cout << "|" << setfill(' ') << setw(5) << split[0] << " "
				<< setw(5) << split[1] << " "
				<< setw(8) << split[2] << " "
				<< setw(15) << split[3] << " "
				<< setw(7) << split[4] << " "
				<< setw(93) << split[5] << "|" << endl;
		}
	}

	cout << "+" << right << setfill('-') << setw(139) << "+" << left << endl;
	return 1;
}