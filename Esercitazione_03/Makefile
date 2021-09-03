CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : es03_1.exe

es03_1.exe : es03_1.o random.o mylib.o
	$(CC) random.o mylib.o es03_1.o -o es03_1.exe
es03_1.o : es03_1.cpp
	$(CC) -c es03_1.cpp -o es03_1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)

clean :
	rm *.o *.exe seed.out
