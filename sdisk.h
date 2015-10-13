/*
*	Ruben Castaneda
*	CSE 461
*	Lab 2
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
		bool good();
	private:
		string diskName;
		int numberOfBlocks;
		int blockSize;
		int statusCode;
};
#endif