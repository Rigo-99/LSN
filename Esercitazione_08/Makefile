CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : es08_1.exe

es08_1.exe : es08_1.o random.o mylib.o
	$(CC) random.o mylib.o es08_1.o -o es08_1.exe
es08_1.o : es08_1.cpp
	$(CC) -c es08_1.cpp -o es08_1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)

clean :
	rm *.o *.exe seed.out
