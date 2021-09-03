CC = g++
CCM = mpicxx
CFLAGS = -Wall -O3 --std=c++11

all : es10_2.exe

es10_2.exe : es10_2.o random.o mylib.o genetics.o
	$(CCM) random.o mylib.o genetics.o es10_2.o -o es10_2.exe
es10_2.o : es10_2.cpp
	$(CCM) -c es10_2.cpp -o es10_2.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
mylib.o : mylib.cpp mylib.h
	$(CC) -c mylib.cpp -o mylib.o $(CFLAGS)
genetics.o : genetics.cpp genetics.h random.h
	$(CC) -c genetics.cpp -o genetics.o $(CFLAGS)

clean :
	rm *.o main.exe seed.out
