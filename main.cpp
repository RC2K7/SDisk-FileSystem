/*
*	Ruben Castaneda
*	CSE 461
*	Lab 6
*
*	main.cpp
*
*	Main test block for verifying functionality of SDisk.
*/

#include "shell.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Shell *shell = new Shell("test1", 256, 128, "index", "flat");

    delete shell;
}
