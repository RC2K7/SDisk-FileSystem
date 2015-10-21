all: main

build: cleanall main

main: main.o sdisk.o filesystem.o
	g++ main.o sdisk.o filesystem.o -o SDisk

main.o: main.cpp sdisk.o
	g++ sdisk.o -c main.cpp

sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp

filesystem.o: filesystem.cpp
	g++ -c filesystem.cpp

clean:
	rm -f SDisk *.o

cleanall:
	rm -f SDisk *.o test1