/*
*	Ruben Castaneda
*	CSE 461
*	Lab 3
*
*	filesystem.cpp
*/

#include "filesystem.h"

#include <iomanip>
#include <sstream>

FileSystem::FileSystem() : SDisk("test1", 16, 32)
{
	if (this->getStatusCode() <= 0)
		return;
	
	this->rootSize = this->getBlockSize() / 12;
	int byteReq = this->getNumberOfBlocks() * 6;
	this->fatSize = (byteReq / this->getBlockSize()) + (byteReq %
		this->getBlockSize() > 0);
		
	this->initRoot();
	this->initFat();
	
	this->fsSynch();
}

// Why Do We Need This??
int FileSystem::fsClose()
{
	return 1;
}

// Writes FileSystem (Root/FAT) to SDisk
int FileSystem::fsSynch()
{
	stringstream ssBuffer;
	
	//Write Root To SDisk
	for (int i = 0; i < this->rootSize; i++)
		ssBuffer << this->rootFileName[i] << this->delimiter << setw(5) <<
			setfill('0') << this->rootFirstBlock[i] << this->delimiter;
	vector<string> vecRoot = block(ssBuffer.str(), this->getBlockSize());
	this->putBlock(0, vecRoot[0]);
	
	ssBuffer.str("");
	
	//Write fat To SDisk
	for (int i = 0; i < this->fat.size(); i++)
		ssBuffer << setw(5) << setfill('0') << fat[i] << this->delimiter;
	vector<string> vecFAT = block(ssBuffer.str(), this->getBlockSize());
	for (int i = 0; i < vecFAT.size(); i++)
		this->putBlock((1 + i), vecFAT[i]);
	
	return 1;
}

// Creates New File in Root
int FileSystem::newFile(string fileName)
{
	// Handles FileNames Greater Than 5 Chars
	if (fileName.legth() > 5)
		fileName = fileName.substr(0, 5);

	// Returns If File Exists
	if (this->getFirstBlock(fileName) != -1)
		return 0;

	for (int i = 0; i < this->rootFileName.size(); i++)
		if (this->rootFileName[i] == ".....") {
			this->rootFileName[i] = fileName;
			this->rootFirstBlock = 0;
			return this->fsSynch();
		}

	return 0;
}

// Removes Empty File From Root
int FileSystem::rmFile(string fileName)
{
	// Handles FileNames Greater Than 5 Chars
	if (fileName.length() > 5)
		fileName = fileName.substr(0, 5);

	int tmpFB = this->getFirstBlock(fileName);

	// Return 0 File Does Not Exist or File Contains Blocks
	if (tmpFB != 0)
		return 0;

	for (int i = 0; i < this->rootFileName.size(); i++)
		if (this->rootFileName[i] == fileName)
			this->rootFileName[i] = ".....";

	return this->fsSynch();
}

// Returns The First Block In A File
int FileSystem::getFirstBlock(string fileName)
{
	// Handles FileNames Greater Than 5 Chars
	if (fileName.length() > 5)
		fileName = fileName.substr(0, 5);

	for (int i = 0; i < this->rootFileName.size(); i++)
		if (this->fileName[i] == fileName)
			return this->rootFirstBlock[i];

	return -1;
}

// Reserve A Block For A File
int FileSystem::addBlock(string fileName)
{
	return 1;
}

// Remove Last Block From A File
int FileSystem::delBlock(string fileName)
{
	return 1;
}

// Retrieve Block From File
int FileSystem::readBlock(string fileName, int block, string& buffer)
{
	return 1;
}

// Write Buffer To Block Within File
int FileSystem::writeBlock(string fileName, int block, string buffer)
{
	return 1;
}

// Get Following Block 
int FileSystem::nextBlock(string fileName, int block)
{
	return 1;
}

int FileSystem::initRoot()
{
	stringstream ssBuffer;
	
	if (this->getStatusCode() == 1) {
		for (int i = 0; i < this->rootSize; i++)
			ssBuffer << "....." << this->delimiter << "00000" << this->delimiter;
	} else {
		string temp;
		this->getBlock(0, temp);
		ssBuffer << temp;
	}
	
	vector<string>vecRoot = block(ssBuffer.str(), this->getBlockSize());
	ssBuffer.str(vecRoot[0]);
	
	{
		int i;
		string entry;
		for (i = 0; i  < (this->rootSize * 2) && getline(ssBuffer, entry,
			this->delimiter); i++)
		{
			if (i % 2 == 0)
				this->rootFileName.push_back(entry);
			else
				this->rootFirstBlock.push_back(std::stoi(entry, nullptr, 10));
		}
	}
	
	return 1;
}

int FileSystem::initFat()
{
	stringstream ssBuffer;
	int dataStart = 1 + this->fatSize;
	
	if (this->getStatusCode() == 1) {
		ssBuffer << setw(5) << setfill('0') << dataStart << this->delimiter;
		for (int i = 1; i < dataStart; i++)
			ssBuffer << "00000" << this->delimiter;
		for (int i = dataStart; i < (this->getNumberOfBlocks() - 1); i++)
			ssBuffer << setw(5) << setfill('0') << (i + 1) << this->delimiter;
		ssBuffer << "00000" << this->delimiter;
	} else {
		string temp;
		for (int i = 1; i < dataStart; i++) {
			this->getBlock(i, temp);
			ssBuffer << temp;
		}
	}
	
	vector<string> vecFAT = block(ssBuffer.str(), this->getBlockSize());
	ssBuffer.str("");
	for (int i = 0; i < vecFAT.size(); i++)
		ssBuffer << vecFAT[i];
	
	{
		int i;
		string entry;
		for (i = 0; i < this->getNumberOfBlocks() && getline(ssBuffer, entry,
			this->delimiter); i++)
		{
			this->fat.push_back(std::stoi(entry, nullptr, 10));
		}
	}
	
	return 1;
}

static vector<string> block(string buffer, int b)
{
	vector<string> blocks;
	int numberofblocks = 0;

	if (buffer.length() % b == 0) 
	{ 
		numberofblocks = buffer.length()/b;
	} else {
		numberofblocks = buffer.length()/b +1;
	}
	
	string tempblock;
	for (int i=0; i<numberofblocks; i++)
	{
		tempblock = buffer.substr(b*i,b);
		blocks.push_back(tempblock);
	}
	
	int lastblock = blocks.size()-1;
	
	for (int i=blocks[lastblock].length(); i<b; i++)
	{
		blocks[lastblock] += "#";
	}
	
	return blocks;
}