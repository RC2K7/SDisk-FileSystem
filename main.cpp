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
    FileSystem *fsys = new FileSystem("test1", 256, 128);

    // Local Scope Lab 4 and 5 Main (Collapsable)
    {
        fsys->newFile("file1");
        fsys->newFile("file2");

        string bfile1;
        string bfile2;

        for (int i = 1; i <= 1024; i++)
        {
            bfile1 += "1";
        }

        vector<string> blocks = FileSystem::block(bfile1, 128);

        int blocknumber = 0;

        for (int i = 0; i < blocks.size(); i++)
        {
            blocknumber = fsys->addBlock("file1", blocks[i]);
        }

        fsys->delBlock("file1", fsys->getFirstBlock("file1"));

        for (int i = 1; i <= 2048; i++)
        {
            bfile2 += "2";
        }

        blocks = FileSystem::block(bfile2, 128);

        for (int i = 0; i < blocks.size(); i++)
        {
            blocknumber = fsys->addBlock("file2", blocks[i]);
        }

        fsys->delBlock("file2", blocknumber);
    }

    delete fsys;
}
