all: main

build: cleanall main

main: main.o shell.o table.o filesystem.o sdisk.o util.o
	g++ main.o shell.o table.o filesystem.o sdisk.o util.o -o SDisk

main.o: main.cpp shell.o
	g++ shell.o -c main.cpp

shell.o: shell.cpp
	g++ -c shell.cpp

table.o: table.cpp
	g++ -c table.cpp

filesystem.o: filesystem.cpp
	g++ -c filesystem.cpp

sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp

util.o: util.cpp
	g++ -c util.cpp

clean:
	rm -f SDisk *.o

cleanall:
	rm -f SDisk *.o test1
