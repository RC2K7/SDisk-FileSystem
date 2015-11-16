#include "shell.h"

Shell::Shell(string diskName, int numberOfBlocks, int blockSize) : FileSystem(diskName, numberOfBlocks, blockSize)
{
    this->runShell();
}

int Shell::dir(){
    return 1;
}

int Shell::add(string fileName)
{
    return 1;
}

int Shell::del(string fileName)
{
    return 1;
}

int Shell::type(string fileName)
{
    return 1;
}

int Shell::copy(string fileName)
{
    return 1;
}

void Shell::runShell()
{

}
