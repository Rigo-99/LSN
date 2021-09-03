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


/************************************************************************************/

// PASSI DISCRETI SU GRIGLIA CUBICA


	int n_cammini = 10000;
	int l = 100;
	int n_blocchi = 100;
	int l_blocchi = n_cammini/n_blocchi;
	
	
	double sum_distanze_CUB[l+1] = {0};
	double ave_distanze_CUB[l+1] = {0};
	double std_distanze_CUB[l+1] = {0};
	
	double blocchi[l+1][l_blocchi];

	for(int i=0; i<n_cammini; i++){

		double pos [3] = {0};

		for(int p=1; p<=l; p++){
			int dir = floor(rnd.Rannyu(0,6));
			if((dir % 2) == 0)
				pos[dir/2]++;
			else
				pos[(dir-1)/2]--;

			sum_distanze_CUB[p] += pow(dist(pos),2);
		}
		
		
		if ((i+1) % l_blocchi == 0){
			int j = ((i+1) / l_blocchi)-1;
			
			for(int p=1; p<=l; p++){
				blocchi[p][j] = sum_distanze_CUB[p] / l_blocchi;
				sum_distanze_CUB[p] = 0;
			}
		}
	}


	for(int p=1; p<=l; p++){
		double sum = 0;	
		for(int j=0; j<n_blocchi; j++){
			sum += blocchi[p][j];
		}
		ave_distanze_CUB[p] = sum/double(n_blocchi);
		
		
		double mean = 0;
		double mean2 = 0;
		for(int j=0; j<n_blocchi; j++){
			mean += blocchi[p][j] / double(n_blocchi) ;
			mean2 += pow(blocchi[p][j],2) / double(n_blocchi) ;
		}
		std_distanze_CUB[p] = sqrt((mean2 - pow(mean,2))/(n_blocchi-1));
		
		
		// AGGIUSTAMENTO DEI VALORI FACENDONE LA RADICE
		
		ave_distanze_CUB[p] = sqrt(ave_distanze_CUB[p]);
		std_distanze_CUB[p] = std_distanze_CUB[p]/(2*ave_distanze_CUB[p]);
	}
	

	Print_valore_incertezza(ave_distanze_CUB, std_distanze_CUB, l+1, "results/2_1.dat");


/**************************************************************************************************/


// PASSI NELLO SPAZIO


	n_cammini = 10000;
	l = 100;
	n_blocchi = 100;
	l_blocchi = n_cammini/n_blocchi;
	
	double sum_distanze_SPA[l+1] = {0};
	double ave_distanze_SPA[l+1] = {0};
	double std_distanze_SPA[l+1] = {0};
	

	for(int i=0; i<n_cammini; i++){

		double pos [3] = {0};

		for(int p=1; p<=l; p++){
			double theta = rnd.Rannyu(-M_PI/2,M_PI/2);
			double phi = rnd.Rannyu(0,2*M_PI);

			pos[0] += cos(theta)*sin(phi);
			pos[1] += cos(theta)*cos(phi);
			pos[2] += sin(theta);

			sum_distanze_SPA[p] += pow(dist(pos),2);
		}
		
		
		if ((i+1) % l_blocchi == 0){
			int j = ((i+1) / l_blocchi)-1;
			
			for(int p=1; p<=l; p++){
				blocchi[p][j] = sum_distanze_SPA[p] / l_blocchi;
				sum_distanze_SPA[p] = 0;
			}
		}
	}


	for(int p=1; p<=l; p++){
		double sum = 0;	
		for(int j=0; j<n_blocchi; j++){
			sum += blocchi[p][j];
		}
		ave_distanze_SPA[p] = sum/double(n_blocchi);
		
		
		double mean = 0;
		double mean2 = 0;
		for(int j=0; j<n_blocchi; j++){
			mean += blocchi[p][j] / double(n_blocchi) ;
			mean2 += pow(blocchi[p][j],2) / double(n_blocchi) ;
		}
		std_distanze_SPA[p] = sqrt((mean2 - pow(mean,2))/(n_blocchi-1));
		
		
		// AGGIUSTAMENTO DEI VALORI FACENDONE LA RADICE
		
		ave_distanze_SPA[p] = sqrt(ave_distanze_SPA[p]);
		std_distanze_SPA[p] = std_distanze_SPA[p]/(2*ave_distanze_SPA[p]);
	}
	

	Print_valore_incertezza(ave_distanze_SPA, std_distanze_SPA, l+1, "results/2_2.dat");




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
