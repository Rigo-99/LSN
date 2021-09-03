#include <iostream>
#include <cstdlib>
#include "bar.h"

using namespace std;

ProgressBar :: ProgressBar(int massimo, int larghezza){
	max = massimo;
	width = larghezza;
	actual = 0;
	a_pos = -1;
	a_per = -1;
}

ProgressBar :: ~ProgressBar(){}

void ProgressBar :: Punto(){
	actual ++;
	Mostra();
}

void ProgressBar :: Mostra() {
	if (actual <= max) {
		int pos = int(width * actual/double(max));
		int per = int(actual/double(max) * 100);

		if ((pos != a_pos) || (per != a_per)){

			std::cout << "╠";
			for (int i = 0; i < width; ++i) {
				if (i < pos) std::cout << "═";
				else if (i == pos) std::cout << "▶";
				else std::cout << " ";
			}
			std::cout << "╣ " << per << " %\r";
			std::cout.flush();
			
			a_per = per;
			a_pos = pos;
		}
	}
	if (actual == max){
		std::cout << endl << endl;
	}
}

void ProgressBar :: Reset() {
	actual = 0;
	a_per = -1;
	a_pos = -1;
}
