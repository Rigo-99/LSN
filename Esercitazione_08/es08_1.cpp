/**************************************************************** *****************************************************************
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


double energia;
double incertezza;


double get_energia(double mu, double sigma, bool print){


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

	double delta = 5.5;
	
	int n_step = 1e6;
	int n_blocchi = 1e3;
	int L = n_step/n_blocchi;
	
	double blocchi[n_blocchi];
	
	double alpha_cum;
	double x;
	double h;

	ofstream punti;
	if(print)
		punti.open("results/punti.dat");
	
	x = 0;
	h = psi2T(x, mu, sigma);
	
	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_x = rnd.Rannyu(-delta/2,delta/2);
			
			double h_prova = psi2T(x+delta_x, mu, sigma);
			
			double alpha = h_prova/h;

			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO

			
			if (rnd.Rannyu() < alpha){
				x += delta_x;
						
				h = psi2T(x, mu, sigma);
			}
			
			double e_kin = K(x,mu,sigma);
			double e_pot = V(x);
			
			if(print)
				punti << x << endl;

			cumsum +=  e_kin + e_pot;
		}
		
		blocchi[n] = cumsum/double(L);
	}

	if(print)
		punti.close();
	
	cout << "Accettanza media:\t " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	if (print)
		Print_media_sigma_blocchi(blocchi, n_blocchi, "results/energia.dat");
	
	energia = media(blocchi, n_blocchi);
	incertezza = stdev(blocchi, n_blocchi);
	
	return energia;
}















int main (int argc, char *argv[]){

	double energia_media = get_energia(0.8,0.6,false);

	cout << "Energia media:\t " << energia_media << endl;

	ofstream out("results/griglia.dat");

	for (double mu=0.7; mu<=0.9; mu+=0.04){
		for (double sigma=0.5; sigma<=0.7; sigma+=0.02){

			energia_media = get_energia(mu,sigma,false);
			
			cout << "sigma = " << sigma << "\t mu = " << mu << "\t E = " << energia_media << endl;	
			out << energia_media << " " << incertezza << " " << sigma << " " << mu << endl;
		}
	}

	out.close();


	// stampa della migliore stima

	double mu = 0.82 ;
	double sigma = 0.62 ;

	get_energia(mu,sigma,true);

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
