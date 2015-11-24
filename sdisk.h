/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	sdisk.h
*/

#ifndef SDISK_H
#define SDISK_H
#include <string>

using namespace std;

class SDisk
{
	public:
		SDisk(string, int, int);
		int getBlock(int, string&);
		int putBlock(int, string);
		int getNumberOfBlocks();
		int getBlockSize();
		int getStatusCode();
		bool good();
	private:
		string diskName;
		int numberOfBlocks;
		int blockSize;
		int statusCode;
};
#endif
