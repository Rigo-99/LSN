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
#include <algorithm>
#include <fstream>
#include <string>
#include "random.h"
#include "genetics.h"
#include "mylib.h"
#include "mpi.h"
#include <math.h>

using namespace std;




int main (int argc, char *argv[]){

	int size,rank;

	MPI_Init(&argc, &argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(size != 4){
		std::cerr << "Attento! usa 4 processori!" << endl;
		return -1;
	}
	
/**************************/

	int n_individui = 400;
	int n_generazioni = 1000;
	int n_gen_olympic = 80;
	double elitarieta = 1.5;
	double mutabilita = 0.15;

/*	if ( argc!=6 ) {
		std::cerr << "\nSPECIFICARE in ordine:\n- numero individui   [400]\n- numero generazioni [1000]\n- gen per olimpiade  [100]\n- elitarietà         [1.5]\n- mutabilità         [0.15]" << endl;
		cout << endl;
		cout << "Utilizzo valori in parentesi quadre:\n./es10_2.exe 400 1000 100 1.5 0.15\n\n" << endl;
	}
	else{
		n_individui = atoi(argv[1]);
		n_generazioni = atoi(argv[2]);
		n_gen_olympic = atoi(argv[3]);
		elitarieta = atof(argv[4]);
		mutabilita = atof(argv[5]);
	}
											==========> magari non funziona perché argv è usato da MPI_Init()... per cambiare valori ricompilare.
*/

	int dimensioni = 32;
	int n_riproduzioni = int(n_individui/4);

	ofstream out ("results/best_"+to_string(rank)+".dat");

	Random rnd(rank);

	Mappa map("map.dat");

	Popolazione pop(&rnd, &map, n_individui, dimensioni, elitarieta, mutabilita);
	
	pop.Popolazione_Random();
	pop.Statistica();
	out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
	
	for (int i=0; i<int(n_generazioni/n_gen_olympic); i++){
		for (int j=0; j<n_gen_olympic; j++){
			
			pop.Nuova_Generazione(n_riproduzioni);
			pop.Statistica();

			out << pop.best << "\t\t" << pop.media  << "\t\t" << pop.stdev << endl;
		}
		
		// QUA CI SONO LE OLIMPIADI, CIOÈ SCAMBIO FRA TUTTA LA POPOLAZIONE MONDIALE
		// tutti fanno Broadcast dei propri
		
		int zer[n_individui][dimensioni];
		int uno[n_individui][dimensioni];
		int due[n_individui][dimensioni];
		int tre[n_individui][dimensioni];
		

		for (int k=0; k<n_individui; k++){
			for(int l=0; l<dimensioni; l++){
				zer[k][l] = pop.popolo[k].DNA[l];
                                uno[k][l] = pop.popolo[k].DNA[l];
                                due[k][l] = pop.popolo[k].DNA[l];
                                tre[k][l] = pop.popolo[k].DNA[l];
			}
		}
		MPI_Bcast(zer, dimensioni*n_individui, MPI_INTEGER, 0 , MPI_COMM_WORLD);
		MPI_Bcast(uno, dimensioni*n_individui, MPI_INTEGER, 1 , MPI_COMM_WORLD);
		MPI_Bcast(due, dimensioni*n_individui, MPI_INTEGER, 2 , MPI_COMM_WORLD);
		MPI_Bcast(tre, dimensioni*n_individui, MPI_INTEGER, 3 , MPI_COMM_WORLD);


		int tutti[4][n_individui][dimensioni];


		for (int k=0; k<n_individui; k++){
                        for(int l=0; l<dimensioni; l++){
                                tutti[0][k][l] = zer[k][l];
                                tutti[1][k][l] = uno[k][l];
                                tutti[2][k][l] = due[k][l];
                                tutti[3][k][l] = tre[k][l];
                        }
		}
		// ognuno riarrangia e prende i suoi nuovi

		pop.Svuota_Popolazione();

		for (int k=0; k<n_individui; k++){
			vector<int> DNA_vec;
			DNA_vec.empty();
			int a = (k+rank)%4;
			for(int l=0; l<dimensioni; l++){
				DNA_vec.push_back(tutti[a][k][l]);
			}
			Individuo nuovo(&rnd,dimensioni,DNA_vec);
			nuovo.Aggiorna(&map);
			pop.Aggiungi_Individuo(nuovo);
		}
	}
	
	out.close();

	cout << "lunghezza minima sulla circonferenza: " << pop.best << endl;
	
	
	//map.Stampa("results/map_1.dat");
	pop.popolo[0].Stampa("results/path_"+to_string(rank)+".dat");

	
/**************************/
	
	MPI_Finalize();
	

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
