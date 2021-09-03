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


/****************************************************/


	int N[4] = {1,2,10,100};
	int M = 10000;
	
	double SN_exp[4][M];
	double SN_lor[4][M];
	double SN_unif[4][M];
	double cum_sum;

	ofstream out;
	
	out.open("results/2_unif.dat");

	for(int i=0; i<M; i++){							// per 10000 volte
		for(int k=0; k<4; k++){						// per ogni N
			cum_sum = 0;
			for(int j=0; j<N[k]; j++){				// per N volte
				cum_sum += rnd.Rannyu();			// accumula UNIF
			}
			SN_unif[k][i] = cum_sum / N[k];			// fai media
			out << SN_unif[k][i] << " ";
		}
		out << endl;
	}
	out.close();


	out.open("results/2_exp.dat");

	for(int i=0; i<M; i++){							// per 10000 volte
		for(int k=0; k<4; k++){						// per ogni N
			cum_sum = 0;
			for(int j=0; j<N[k]; j++){				// per N volte
				cum_sum += rnd.Exp(1);				// accumula EXP
			}
			SN_exp[k][i] = cum_sum / N[k];			// fai media
			out << SN_exp[k][i] << " ";
		}
		out << endl;
	}
	out.close();
	
	
	out.open("results/2_lor.dat");
	
	for(int i=0; i<M; i++){							// per 10000 volte
		for(int k=0; k<4; k++){						// per ogni N
			cum_sum = 0;
			for(int j=0; j<N[k]; j++){				// per N volte
				cum_sum += rnd.Lorentz(0,1);		// accumula LORENTZ
			}
			SN_lor[k][i] = cum_sum / N[k];			// fai media
			out << SN_lor[k][i] << " ";
		}
		out << endl;
	}



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
