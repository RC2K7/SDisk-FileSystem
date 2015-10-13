#include "filesystem.h"

FileSystem::FileSystem() : SDisk("test1", 16, 32)
{

}

int FileSystem::fsClose()
{
	return 1;
}

int FileSystem::fsSynch()
{
	return 1;
}


int FileSystem::newFile(string)
{
	return 1;
}


int FileSystem::rmFile(string)
{
	return 1;
}

int FileSystem::getFirstBlock(string)
{
	return 1;
}


int FileSystem::addBlock(string)
{
	return 1;
}


int FileSystem::delBlock(string)
{
	return 1;
}

int FileSystem::readBlock(string, int, string&)
{
	return 1;
}

int FileSystem::writeBlock(string, int, string)
{
	return 1;
}

int FileSystem::nextBlock(string, int)
{
	return 1;
}