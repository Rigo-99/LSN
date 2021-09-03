CC = g++
CFLAGS = -Wall -O3 --std=c++11

all: es07_1.exe es07_2.exe

es07_1.exe : es07_1.o random.o mylib.o
	$(CC) random.o mylib.o es07_1.o -o es07_1.exe
es07_1.o : es07_1.cpp
	$(CC) -c es07_1.cpp -o es07_1.o $(CFLAGS)

es07_2.exe : es07_2.o random.o mylib.o
	$(CC) random.o mylib.o es07_2.o -o es07_2.exe
es07_2.o : es07_2.cpp MolDyn_NVE.h
	$(CC) -c es07_2.cpp -o es07_2.o $(CFLAGS)


random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)


clean :
	rm *.o *.exe
