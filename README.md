CSE 461 (Fall 2015) - SDisk, FileSystem
=

What is SDisk?
-
SDisk is a virtual representation of a physical hard disk.  This is simply being emulated within a flat file.  Each SDisk will have two essential parameters, Block Numbers and Block Size.  These two numbers are used to calculate the full size of the virtual disk (SDisk).  This implementation will allow data to be written to "Blocks" of memory within the disk.

What is FileSystem?
-
FileSystem is a simple Disk Operating System (DOS) written to inherit the SDisk and adding useful features and functions that are common is storage system.  This is the ability to read and write files to the disk.  The two main features in the FileSystem include the Root and FAT tables.

- Root Table
	- This stores the data for each file located on the FileSystem.  This data includes the File Name and the starting Block Number which would represent a black of data that can be accessed from the SDisk.
- FAT Table
	- This keeps track of all blocks within the FileSystem and therefore available within the SDisk.  It allows for a quick and convenient way to locate if a Free Block (one that is not in use) is available.  This also links multiple blocks together through a Vector of Integer style method allowing one to looked Block Number "x" and see which Block number"y" succeeds it.
