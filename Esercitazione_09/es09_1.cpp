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

	int numero_individui = 400;
	int n_generazioni = 1000;
	double elitarieta = 1.5;
	double mutabilita = 0.15;

	if ( argc!=5 ) {
		std::cerr << "\nSPECIFICARE in ordine:\n- numero individui   [400]\n- numero generazioni [1000]\n- elitarietà         [1.5]\n- mutabilità         [0.15]" << endl;
		cout << endl;
		cout << "Utilizzo valori in parentesi quadre:\n./es09_1.exe 400 1000 1.5 0.15\n\n" << endl;
	}
	else{
		numero_individui = atoi(argv[1]);
		n_generazioni = atoi(argv[2]);
		elitarieta = atof(argv[3]);
		mutabilita = atof(argv[4]);
	}


	int dimensioni = 32;
	int n_riproduzioni = int(numero_individui/4);

	ofstream out ("results/1_1.dat");

	

	Random rnd;


	Mappa map(&rnd, dimensioni);
	map.Genera_su_cerchio(1);

	Popolazione pop(&rnd, &map, numero_individui, dimensioni, elitarieta, mutabilita);
	
	pop.Popolazione_Random();
	pop.Statistica();
	out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
	
	for (int i=0; i<n_generazioni; i++){
		pop.Nuova_Generazione(n_riproduzioni);
		pop.Statistica();

		out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
	}
	
	out.close();

	cout << "lunghezza minima sulla circonferenza: " << pop.best << endl;
	
	
	map.Stampa("results/map_1.dat");
	pop.popolo[0].Stampa("results/path_1.dat");
	
	
	
	
	
	
	out.open("results/1_2.dat");
	
	//map.Genera_in_quadrato(1);
	map = Mappa("results/map_quadrato.dat");


	pop = Popolazione(&rnd, &map, numero_individui, dimensioni, elitarieta, mutabilita);
	
	pop.Popolazione_Random();
	pop.Statistica();
	out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
	
	for (int i=0; i<n_generazioni; i++){
		pop.Nuova_Generazione(n_riproduzioni);
		pop.Statistica();

		out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
	}
	
	out.close();

	cout << "lunghezza minima nel quadrato: " << pop.best << endl;
	
	
	map.Stampa("results/map_2.dat");
	pop.popolo[0].Stampa("results/path_2.dat");
	
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
