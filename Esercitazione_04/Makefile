CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : es04_1.exe

es04_1.exe : es04_1.o mylib.o
	$(CC) es04_1.o mylib.o -o es04_1.exe

es04_1.o : es04_1.cpp
	$(CC) -c es04_1.cpp -o es04_1.o $(CFLAGS)

mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)

clean :
	rm *.o *.exe
