/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/



#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "mylib.h"
#include <math.h>

using namespace std;
 
int main (int argc, char *argv[]){

	Random rnd;
	int seed[4];
	int p1, p2;
	ifstream Primes("Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("seed.in");
	string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				rnd.SetRandom(seed,p1,p2);
			}
		}
		input.close();
	} else cerr << "PROBLEM: Unable to open seed.in" << endl;


/*****************************************************************************/
	
	
	int n_punti = 100000;
	int N = 200;
	int L = int(n_punti/N);
	double x_min = 0;
	double x_max = 1;
	double block[N];
	
	for (int i=0; i<N; i++){
		double ave = 0;
		for (int j=0; j<L; j++){
			ave += f2_1(rnd.Rannyu(x_min,x_max))/L;
		}
		block[i] = ave;
	}
	
	Print_media_sigma_blocchi(block, N, "results/1_1.dat");
	
	
	
	
	
	
	
	
	
	
	n_punti = 100000;
	N = 200;
	L = int(n_punti/N);
	block[N]={};
	
	for (int i=0; i<N; i++){
		double ave = 0;
		for (int j=0; j<L; j++){
		
			double x = inversa(rnd.Rannyu(0,1));
			ave += (M_PI/4) * (f2_1(x)/g2_2(x)) / L;

		}
		block[i] = ave;
	}
	
	Print_media_sigma_blocchi(block, N, "results/1_2.dat");
	
	
	
	
	


	return 0;
}




/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
