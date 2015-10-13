/*
*	Ruben Castaneda
*	CSE 461
*	Lab 2
*	
*	Main test block for verifying functionality of SDisk.
*/

#include "filesystem.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	FileSystem *fs = new FileSystem();
	
	delete fs;
}