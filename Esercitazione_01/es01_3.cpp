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


/****************************************************/


	double L = 1;
	double d = 1.8;
	
	int n_blocchi = 1000;
	int n_tiri = 10000;
	double Pi[n_blocchi];


	for(int i=0; i<n_blocchi; i++){		
		int n_hit = 0;			
		for(int j=0; j<n_tiri; j++){
			double dist = rnd.Rannyu(0,0.5*d);
			double x = rnd.Rannyu(0,1);					
			double y = rnd.Rannyu(0,1);					// punti unif. su un quadrato
			while ((pow(x,2)+pow(y,2)) > 1){			// ma prendo solo dentro cerchio
				x = rnd.Rannyu(0,1);					//    per avere angolo unif.
				y = rnd.Rannyu(0,1);
			}
			if (dist < ((L/2)*(1/sqrt(1+pow(y/x,2))))){
				n_hit++;
			}
		}
		Pi[i] = 2*(L/d)*(double(n_tiri)/double(n_hit));		
	}
	
	
	Print_media_sigma_blocchi(Pi, n_blocchi, "results/3_1.dat");

	return 0;
}
