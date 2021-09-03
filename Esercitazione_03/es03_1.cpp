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


/**********************************************************************************/

	double S = 100;
	double T = 1;
	double K = 100;
	double r = 0.1;
	double sigma = 0.25;

	int M = 1e5;
	int n_blocchi = 100;
	int l = M/n_blocchi;
	
	
	double put_dir[n_blocchi];
	double put_dis[n_blocchi];
	double call_dir[n_blocchi];
	double call_dis[n_blocchi];
	
	
	for(int i=0; i<n_blocchi; i++){
		double call_cum = 0;
		double put_cum = 0;
		for(int j=0; j<l; j++){
			
			double Z = rnd.Gauss(0,T);
			
			double S_fin = S*exp((r-0.5*sigma*sigma)*T + sigma*Z);			
			
			double call = exp(-r*T) * max(0., S_fin-K);
			call_cum += call;
			
			double put = exp(-r*T) * max(0., K-S_fin);
			put_cum += put;
		}
		
		call_dir[i] = call_cum/double(l);
		put_dir[i] = put_cum/double(l);

	}
	
	
	int n_step = 100;
	double step = T/double(n_step);
	
	
	for(int i=0; i<n_blocchi; i++){
		double call_cum = 0;
		double put_cum = 0;
		for(int j=0; j<l; j++){
			double S_par = S;
			for(double t=0; t<T; t+=step){
				double Z = rnd.Gauss(0,1);
				S_par = S_par*exp((r-0.5*sigma*sigma)*step + sigma*Z*sqrt(step));
			}
			double S_fin = S_par;
			
			double call = exp(-r*T) * max(0., S_fin-K);
			call_cum += call;
			
			double put = exp(-r*T) * max(0., K-S_fin);
			put_cum += put;
		}
		
		call_dis[i] = call_cum/double(l);
		put_dis[i] = put_cum/double(l);

	}
	
	
	Print_media_sigma_blocchi(call_dir, n_blocchi, "results/1_1_1.dat");
	Print_media_sigma_blocchi(put_dir, n_blocchi, "results/1_1_2.dat");
	Print_media_sigma_blocchi(call_dis, n_blocchi, "results/1_2_1.dat");
	Print_media_sigma_blocchi(put_dis, n_blocchi, "results/1_2_2.dat");

	


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
