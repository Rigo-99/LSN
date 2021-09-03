CC = g++
CFLAGS = -Wall -O3 --std=c++11

all : es10_1.exe

es10_1.exe : es10_1.o random.o mylib.o genetics.o
	$(CC) random.o mylib.o genetics.o es10_1.o -o es10_1.exe
es10_1.o : es10_1.cpp
	$(CC) -c es10_1.cpp -o es10_1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)
genetics.o : genetics.cpp genetics.h random.h
	$(CC) -c genetics.cpp -o genetics.o $(CFLAGS)

clean :
	rm *.o *.exe seed.out
