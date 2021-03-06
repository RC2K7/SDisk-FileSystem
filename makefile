all: main

build: cleanall main

main: main.o shell.o filesystem.o sdisk.o
	g++ main.o shell.o filesystem.o sdisk.o -o SDisk

main.o: main.cpp shell.o
	g++ shell.o -c main.cpp

shell.o: shell.cpp
	g++ -c shell.cpp

filesystem.o: filesystem.cpp
	g++ -c filesystem.cpp

sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp

clean:
	rm -f SDisk *.o

cleanall:
	rm -f SDisk *.o test1
