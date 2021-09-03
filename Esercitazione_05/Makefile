CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : es05_1.exe

es05_1.exe : es05_1.o random.o mylib.o
	$(CC) random.o mylib.o es05_1.o -o es05_1.exe
es05_1.o : es05_1.cpp
	$(CC) -c es05_1.cpp -o es05_1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)

clean :
	rm *.o main.exe seed.out
