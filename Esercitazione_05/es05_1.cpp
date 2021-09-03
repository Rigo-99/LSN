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
	int step_eq = 1e4;
	int n_step = 1e6;
	int n_blocchi = 1000;
	
	if ( argc==4 ) {
		step_eq = atoi(argv[1]);
		n_step = atoi(argv[2]);
		n_blocchi = atoi(argv[3]);
	}
	else{
		std::cerr << "\nSPECIFICARE IN ORDINE:\n- passi di equilibrazione     ["<<step_eq<<"]\n- passi totali                ["<<n_step<<"]\n- numero di blocchi           ["<<n_blocchi<<"]"<< endl;
		cout << endl;
		cout << "Utilizzo valori in parentesi quadre:\n./es05_1.exe " << step_eq << " " << n_step << " " << n_blocchi << "\n\n";
		cout << "(premere un tasto per proseguire)\n";
		cin.get();	// wait for key pressed
	}
	
	
	
	double delta;
	double sigma;
	
	int L = int(n_step/n_blocchi);
	
	double blocchi[n_blocchi];
	
	double alpha_cum;
	
	double x;
	double y;
	double z;
	
	double h;


/****************************/
/* 𝜓_100 con passi uniformi */
/****************************/

	delta = 2.5;
	
	x = 1.5;
	y = 0;
	z = 0;

	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	h = psi100(x,y,z);
	
	// equilibrazione
	
	for(int n=0; n<step_eq; n++){
		double delta_r = rnd.Rannyu(0,delta);
		double delta_theta = rnd.Rannyu(0,M_PI);
		double delta_phi = rnd.Rannyu(0,2*M_PI);

		double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
		double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
		double delta_z = delta_r * cos(delta_theta);
		
		double h_prova = psi100(x+delta_x, y+delta_y, z+delta_z);
		double alpha = h_prova/h;
		
		if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
			x += delta_x;
			y += delta_y;
			z += delta_z;
				
			h = psi100(x,y,z);
		}
	}
	
	
	// valutazione
	
	h = psi100(x,y,z);
	
	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_r = rnd.Rannyu(0,delta);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,2*M_PI);

			double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
			double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
			double delta_z = delta_r * cos(delta_theta);

			double h_prova = psi100(x+delta_x, y+delta_y, z+delta_z);
			
			double alpha = h_prova/h;

			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO

			
			if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
				x += delta_x;
				y += delta_y;
				z += delta_z;
				
				h = psi100(x,y,z);
			}
			
			cumsum += get_r(x,y,z);	
		}
		
		blocchi[n] = cumsum/double(L);
	}
	
	cout << "1s unif  𝛼 = " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	Print_media_sigma_blocchi(blocchi, n_blocchi, "results/1_1.dat");
	
	
	
/****************************/
/* 𝜓_210 con passi uniformi */
/****************************/

	delta = 6.6;
	
	x = 1.5;
	y = 0;
	z = 0;

	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	h = psi210(x,y,z);
	
	// equilibrazione
	
	for(int n=0; n<step_eq; n++){
		double delta_r = rnd.Rannyu(0,delta);
		double delta_theta = rnd.Rannyu(0,M_PI);
		double delta_phi = rnd.Rannyu(0,2*M_PI);

		double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
		double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
		double delta_z = delta_r * cos(delta_theta);
		
		double h_prova = psi210(x+delta_x, y+delta_y, z+delta_z);
		double alpha = h_prova/h;
		
		if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
			x += delta_x;
			y += delta_y;
			z += delta_z;
				
			h = psi210(x,y,z);
		}
	}
	
	
	// valutazione
	
	h = psi210(x,y,z);
	
	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_r = rnd.Rannyu(0,delta);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,2*M_PI);

			double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
			double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
			double delta_z = delta_r * cos(delta_theta);

			double h_prova = psi210(x+delta_x, y+delta_y, z+delta_z);
			
			double alpha = h_prova/h;

			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO

			
			if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
				x += delta_x;
				y += delta_y;
				z += delta_z;
				
				h = psi210(x,y,z);
			}
			
			cumsum += get_r(x,y,z);	
		}
		
		blocchi[n] = cumsum/double(L);
	}
	
	cout << "2p unif  𝛼 = " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	Print_media_sigma_blocchi(blocchi, n_blocchi, "results/1_2.dat");	
	
	
	
/*****************************/
/* 𝜓_100 con passi gaussiani */
/*****************************/

	sigma = 1.75;
	
	x = 1.5;
	y = 0;
	z = 0;
	
	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	h = psi100(x,y,z);
	
	// equilibrazione
	
	for(int n=0; n<step_eq; n++){
			double delta_r = rnd.Gauss(0,sigma);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,M_PI);

		double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
		double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
		double delta_z = delta_r * cos(delta_theta);
		
		double h_prova = psi100(x+delta_x, y+delta_y, z+delta_z);
		double alpha = h_prova/h;
		
		if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
			x += delta_x;
			y += delta_y;
			z += delta_z;
				
			h = psi100(x,y,z);
		}
	}
	
	
	// valutazione
	
	h = psi100(x,y,z);

	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_r = rnd.Gauss(0,sigma);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,M_PI);

			double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
			double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
			double delta_z = delta_r * cos(delta_theta);
		
			double h_prova = psi100(x+delta_x, y+delta_y, z+delta_z);
			
			double alpha = h_prova/h;
			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO
			
			
			if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
				x += delta_x;
				y += delta_y;
				z += delta_z;
				
				h = psi100(x,y,z);
			}
			
			cumsum += get_r(x,y,z);	
		}
		
		blocchi[n] = cumsum/double(L);
	}
	
	cout << "1s gauss 𝛼 = " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	Print_media_sigma_blocchi(blocchi, n_blocchi, "results/2_1.dat");
	
	
	
		
/*****************************/
/* 𝜓_210 con passi gaussiani */
/*****************************/

	sigma = 4.5;
	
	x = 0;
	y = 0;
	z = 5;
	
	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	h = psi210(x,y,z);
	
	// equilibrazione
	
	for(int n=0; n<step_eq; n++){
			double delta_r = rnd.Gauss(0,sigma);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,M_PI);

		double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
		double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
		double delta_z = delta_r * cos(delta_theta);
		
		double h_prova = psi210(x+delta_x, y+delta_y, z+delta_z);
		double alpha = h_prova/h;
		
		if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
			x += delta_x;
			y += delta_y;
			z += delta_z;
				
			h = psi210(x,y,z);
		}
	}
	
	
	// valutazione
	
	h = psi210(x,y,z);
	
	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_r = rnd.Gauss(0,sigma);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,M_PI);

			double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
			double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
			double delta_z = delta_r * cos(delta_theta);
		
			double h_prova = psi210(x+delta_x, y+delta_y, z+delta_z);
			
			double alpha = h_prova/h;
			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO
			
			
			if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
				x += delta_x;
				y += delta_y;
				z += delta_z;
				
				h = psi210(x,y,z);
			}
			
			cumsum += get_r(x,y,z);	
		}
		
		blocchi[n] = cumsum/double(L);
	}
	
	cout << "2p gauss 𝛼 = " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	Print_media_sigma_blocchi(blocchi, n_blocchi, "results/2_2.dat");


		
/**********************************************/
/* 𝜓_210 lontano da origine senza equilibrare */
/**********************************************/

	sigma = 4.5;
	
	x = 200;
	y = 0;
	z = 0;
	
	h = psi210(x,y,z);
	
	alpha_cum = 0; // CALCOLO ALPHA MEDIO
	
	
	for(int n=0; n<n_blocchi; n++){

		double cumsum = 0;
		
		for(int i=0; i<L; i++){

			double delta_r = rnd.Gauss(0,sigma);
			double delta_theta = rnd.Rannyu(0,M_PI);
			double delta_phi = rnd.Rannyu(0,M_PI);

			double delta_x = delta_r * sin(delta_theta) * cos(delta_phi);
			double delta_y = delta_r * sin(delta_theta) * sin(delta_phi);
			double delta_z = delta_r * cos(delta_theta);
		
			double h_prova = psi210(x+delta_x, y+delta_y, z+delta_z);
			
			double alpha = h_prova/h;
			
			if(alpha > 1)				// CALCOLO ALPHA MEDIO
				alpha_cum += 1;			// CALCOLO ALPHA MEDIO
			else						// CALCOLO ALPHA MEDIO
				alpha_cum += alpha;		// CALCOLO ALPHA MEDIO
			
			
			if ((alpha >= 1) or (rnd.Rannyu() < alpha)){
				x += delta_x;
				y += delta_y;
				z += delta_z;
				
				h = psi210(x,y,z);
			}
			
			cumsum += get_r(x,y,z);	
		}
		
		blocchi[n] = cumsum/double(L);
	}
	
	cout << "2p far   𝛼 = " << alpha_cum / double(n_step) << endl; // CALCOLO ALPHA MEDIO
	
	Print_media_sigma_blocchi(blocchi, n_blocchi, "results/3_2.dat");






		
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
