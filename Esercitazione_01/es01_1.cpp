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





	int N = 100;
	int M = 100000;
	int L = int(M/N);

	double block[N];

	for(int i=0; i<N; i++){
		double sum = 0;
		for(int j=0; j<L; j++){
			sum += rnd.Rannyu();		
		}
		block[i] = sum / double(L) ;
	}

	Print_media_sigma_blocchi(block,N,"results/1_1.dat");



	for(int i=0; i<N; i++){
		double sum_err = 0;
		for(int j=0; j<L; j++){
			sum_err += pow(rnd.Rannyu()-0.5, 2);
		}
		block[i] = (sum_err) / double(L) ;
	}

	Print_media_sigma_blocchi(block,N,"results/1_2.dat");
	







	M = 100;
	L = 10000;
	int n_volte = 100;
	double chi[n_volte];
	int bin[M];
	
	for (int k=1; k<M; k++)							// azzera bin
		bin[k] = 0;
	
	for (int i=0; i<n_volte; i++){

		for (int j=0; j<L; j++){
			bin[int(floor(rnd.Rannyu()*M))]++;		// conta nei bin
		}

		double cum_sum = 0;		
		for (int k=1; k<M; k++){
			cum_sum += pow(bin[k]-L/M,2);			// fai numeratore chi²
			bin[k] = 0;								// azzera bin
		}
		
		chi[i] = M*cum_sum/L;						// calcola chi quadro
	}
	
	Print(chi, n_volte, "results/1_3.dat");



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
