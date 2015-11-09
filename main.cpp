/*
*	Ruben Castaneda
*	CSE 461
*	Lab 3
*
*	main.cpp
*
*	Main test block for verifying functionality of SDisk.
*/

#include "filesystem.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	FileSystem *fs = new FileSystem("test1", 256, 128);

	delete fs;
}
