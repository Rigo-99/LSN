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
#include "genetics.h"
#include "mylib.h"
#include <math.h>

using namespace std;




int main (int argc, char *argv[]){


/*****************************************************************************/
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




	int dimensioni = 32;
	ofstream out ("results/1_1.dat");
	

	Mappa map(&rnd, dimensioni);
	map.Genera_su_cerchio(1);

	Individuo colombo(&rnd, dimensioni);
	colombo.Standard();

	double lunghezza = colombo.Misura_Lunghezza_Percorso(&map);
	int accepted = 0;
	int tried = 0;
	
	for (double r=0; r<50000; r++){
		
		double t = pow(1 - double(r)/50000. , 2) ;
		
		// proponi nuovo
		Individuo amerigo = colombo;
		
		switch (rnd.Randint(1,4)){
			case 1: amerigo.Mutazione_1();
			break;
			case 2: amerigo.Mutazione_2();
			break;
			case 3: amerigo.Mutazione_3();
			break;
			case 4: amerigo.Mutazione_4();
			break;
		}
		
		double lunghezza_proposta = amerigo.Misura_Lunghezza_Percorso(&map);
		
		// calcola probabilità
		
		double p = exp( - (lunghezza_proposta - lunghezza)/ t);
		

		// decidi se accettare e nel caso aggiorna	
		
		tried ++;
		
		if (rnd.Rannyu() < p){
			
			colombo = amerigo;
			lunghezza = lunghezza_proposta;
			accepted ++;
		}
		
		
		// registra informazioni
		
		out << lunghezza << endl;
	}
	
	cout << "accettanza = " << accepted << "/" << tried << " = " << double(accepted)/double(tried) << endl;
	
	map.Stampa("results/map_1.dat");
	colombo.Stampa("results/path_1.dat");
	
	
	
	out.close();
	
	/****************************************************************************/

	out.open("results/1_2.dat");

	map = Mappa("results/map_quadrato.dat");

	colombo.Standard();

	lunghezza = colombo.Misura_Lunghezza_Percorso(&map);
	accepted = 0;
	tried = 0;
	
	for (double r=0; r<500000; r++){
		
		double t = pow(1 - double(r)/500000. , 1) ;
		
		// proponi nuovo
		Individuo amerigo = colombo;
		
		switch (rnd.Randint(1,4)){
			case 1: amerigo.Mutazione_1();
			break;
			case 2: amerigo.Mutazione_2();
			break;
			case 3: amerigo.Mutazione_3();
			break;
			case 4: amerigo.Mutazione_4();
			break;
		}
		
		double lunghezza_proposta = amerigo.Misura_Lunghezza_Percorso(&map);
		
		// calcola probabilità
		
		double p = exp( - (lunghezza_proposta - lunghezza)/ t);
		

		// decidi se accettare e nel caso aggiorna	
		
		tried ++;
		
		if (rnd.Rannyu() < p){
			
			colombo = amerigo;
			lunghezza = lunghezza_proposta;
			accepted ++;
		}
		
		
		// registra informazioni
		
		out << lunghezza << endl;
	}
	
	cout << "accettanza = " << accepted << "/" << tried << " = " << double(accepted)/double(tried) << endl;
	
	map.Stampa("results/map_2.dat");
	colombo.Stampa("results/path_2.dat");
	
	
	out.close();
	
	
	
	
	
	

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
