/*
*	Ruben Castaneda
*	CSE 461
*	Lab 2
*/
#include "sdisk.h"

#include <fstream>

SDisk::SDisk(string diskName, int numberOfBlocks, int blockSize)
{
	this->diskName = diskName;
	this->numberOfBlocks = numberOfBlocks;
	this->blockSize = blockSize;
	
	fstream fStream;
	
	fStream.open(this->diskName.c_str(), ios::in);
	if (fStream.fail()) {
		fStream.open(this->diskName.c_str(), ios::out);
		if (fStream.fail()) {
			this->statusCode = -1;
		} else {
			for (int x = 0; x < this->numberOfBlocks * this->blockSize; x++)
				fStream.put('#');
			this->statusCode = 1;
		}
	}
	fStream.close();
}

int SDisk::getBlock(int blockNumber, string& dataOut)
{
	fstream sFile(this->diskName.c_str(), ios::in);
	
	if (sFile.fail())
		return 0;
	
	sFile.seekg(blockNumber * this->blockSize);
	dataOut = "";
	
	for (int x = 0; x < this->blockSize; x++)
		dataOut += sFile.get();
		
	sFile.close();
	
	return 1;
}

int SDisk::putBlock(int blockNumber, string dataIn)
{
	fstream sFile(this->diskName.c_str(), ios::in | ios::out);
	
	if (sFile.fail())
		return 0;
	
	sFile.seekg(blockNumber * this->blockSize);
	
	for (int x = 0; x < dataIn.length() && x < this->blockSize; x++)
		sFile.put(dataIn[x]);
		
	sFile.close();
	
	return 1;
}

int SDisk::getNumberOfBlocks()
{
	return this->numberOfBlocks;
}

int SDisk::getBlockSize()
{
	return this->blockSize;
}

bool SDisk::good()
{
	return (this->statusCode >= 0);
}