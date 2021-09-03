CC = g++
CFLAGS = -Wall -O3 --std=c++11

es_6.exe : es_6.o random.o bar.o
	$(CC) random.o bar.o es_6.o -o es_6.exe
es_6.o : es_6.cpp
	$(CC) -c es_6.cpp -o es_6.o $(CFLAGS)

Monte_Carlo_ISING_1D.exe : Monte_Carlo_ISING_1D.o random.o
	$(CC) random.o bar.o Monte_Carlo_ISING_1D.o -o Monte_Carlo_ISING_1D.exe
Monte_Carlo_ISING_1D.o : Monte_Carlo_ISING_1D.cpp
	$(CC) -c Monte_Carlo_ISING_1D.cpp -o Monte_Carlo_ISING_1D.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
bar.o : bar.cpp bar.h
	$(CC) -c bar.cpp -o bar.o $(CFLAGS)

clean :
	rm *.o
	rm*.exe
