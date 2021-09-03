/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>		// srand, rand: to generate random number
#include <iostream>		// cin, cout: Standard Input/Output Streams Library
#include <fstream>		// Stream class to both read and write from/to files.
#include <cmath>		// rint, pow
#include "MolDyn_NVE.h"
#include "mylib.h"

using namespace std;

int main (int argc, char *argv[]){
	
	int numero_riscalature = 5;
	int step_per_block = 50;
	int step_per_riscalatura = 100;
	bool restart = false;

	if ( argc==5 ) {
		numero_riscalature = atoi(argv[1]);
		step_per_riscalatura = atoi(argv[2]);
		restart = (atoi(argv[3]) == 1);
		step_per_block = atoi(argv[4]);
	}
	else{
		std::cerr << "\nSPECIFICARE in ordine:\n- numero riscalature        ["<<numero_riscalature<<"]\n- step per riscalatura      ["<<step_per_riscalatura<<"]\n- restart (0=no, 1=sì)      [0]\n- lunghezza blocchi         ["<< step_per_block <<"]" << endl;
		cout << endl;
		cout << "Utilizzo valori in parentesi quadre:\n./es07_2.exe " << numero_riscalature << " " << step_per_riscalatura << " " << 0 << " " << step_per_block << "\n\n";
		cout << "(premere un tasto per proseguire)\n";
		cin.get();	// wait for key pressed
		
	}

	int step_per_mesure = 10;
	
	Input(restart);			 		//Inizialization
	int nconf = 1;
	
	cout << "Number of time-steps: 0" << endl;
	
	for(int istep=0; istep < nstep; ++istep){
		Move();		   				//Move particles with Verlet algorithm

		if((istep % step_per_riscalatura == 0) and (istep / step_per_riscalatura < numero_riscalature)){
			Rescale();
		}
		if((istep+1) % iprint == 0)
			cout << "Number of time-steps: " << istep+1 << endl;
		
		if(istep % step_per_mesure == 0){
			bool in_blocchi;
			if (step_per_block == 0)
				in_blocchi = false;
			else
				in_blocchi = (istep % step_per_block == 0);
			
			Measure(in_blocchi);	//Properties measurement
			
			//ConfXYZ(nconf);		//Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
			//nconf += 1;
		}
	}
	ConfFinal();		 			//Write final configuration to restart
	
	if (step_per_block != 0)
		Salva_Blocchi();




	return 0;
}



void Input(bool restart){ //Prepare all stuff for the simulation
	ifstream ReadInput,ReadConf;
	//double ep, ek, pr, et, vir;

	cout << "Classic Lennard-Jones fluid" << endl;
	cout << "Molecular dynamics simulation in NVE ensemble" << endl << endl;
	cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
	cout << "The program uses Lennard-Jones units" << endl;

	seed = 1;	//Set seed for random numbers
	srand(seed); //Initialize random number generator

	ReadInput.open("input_2.dat"); //Read input

	ReadInput >> temp;

	ReadInput >> npart;
	cout << "Number of particles = " << npart << endl;

	ReadInput >> rho;
	cout << "Density of particles = " << rho << endl;
	vol = (double)npart/rho;
	cout << "Volume of the simulation box = " << vol << endl;
	box = pow(vol,1.0/3.0);
	cout << "Edge of the simulation box = " << box << endl;

	ReadInput >> rcut;
	ReadInput >> delta;
	ReadInput >> nstep;
	ReadInput >> iprint;
	
	vtail = (8.0*M_PI*rho)/(9.0*pow(rcut,9)) - (8.0*M_PI*rho)/(3.0*pow(rcut,3));
	
	cout << "The program integrates Newton equations with the Verlet method " << endl;
	cout << "Time step = " << delta << endl;
	cout << "Number of steps = " << nstep << endl << endl;
	ReadInput.close();

	//Prepare array for measurements
	iv = 0;			//Potential energy
	ik = 1;			//Kinetic energy
	ie = 2;			//Total energy
	it = 3;			//Temperature
	n_props = 4;	//Number of observables

	igofr = 4;
	nbins = 100;
	n_props = n_props + nbins;
	bin_size = (box/2.0)/(double)nbins;
	
	if(restart){
	
		//Read initial configuration
		cout << "Read initial configuration from file config.final "<< endl;
		ReadConf.open("config.final");
		for (int i=0; i<npart; ++i){
			ReadConf >> x[i] >> y[i] >> z[i];
			x[i] = x[i] * box;
			y[i] = y[i] * box;
			z[i] = z[i] * box;
		}
		ReadConf.close();
	
		//Read initial-1 configuration
		cout << "Read initial configuration from file config.final-1 " << endl << endl;
		ReadConf.open("config.final-1");
		for (int i=0; i<npart; ++i){
			ReadConf >> xold[i] >> yold[i] >> zold[i];
			xold[i] = xold[i] * box;
			yold[i] = yold[i] * box;
			zold[i] = zold[i] * box;
		}
		ReadConf.close();
		
	}
	else{
	
		//Read initial configuration
		cout << "Read initial configuration from file config.0 " << endl << endl;
		ReadConf.open("config.0");
		for (int i=0; i<npart; ++i){
			ReadConf >> x[i] >> y[i] >> z[i];
			x[i] = x[i] * box;
			y[i] = y[i] * box;
			z[i] = z[i] * box;
		}
		ReadConf.close();

		//Prepare initial velocities
		cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
		double sumv[3] = {0.0, 0.0, 0.0};
		for (int i=0; i<npart; ++i){
			vx[i] = rand()/double(RAND_MAX) - 0.5;
			vy[i] = rand()/double(RAND_MAX) - 0.5;
			vz[i] = rand()/double(RAND_MAX) - 0.5;

			sumv[0] += vx[i];
			sumv[1] += vy[i];
			sumv[2] += vz[i];
		}
		for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
		double sumv2 = 0.0, fs;
		for (int i=0; i<npart; ++i){	// le velocità devono avere media nulla
			vx[i] = vx[i] - sumv[0];
			vy[i] = vy[i] - sumv[1];
			vz[i] = vz[i] - sumv[2];

			sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
		}
		sumv2 /= (double)npart;

		fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor
		for (int i=0; i<npart; ++i){
			vx[i] *= fs;
			vy[i] *= fs;
			vz[i] *= fs;

			xold[i] = Pbc(x[i] - vx[i] * delta);
			yold[i] = Pbc(y[i] - vy[i] * delta);
			zold[i] = Pbc(z[i] - vz[i] * delta);
		}
	}
	return;
}





void Rescale(){ //Rescaling velocities to set temperature equal to temp
	cout << "sto riscalando... ";
	
	double old_T = 0;
	
	if (i_scaling == 0){
		
		double old_cin = 0;
		for (int i=0; i<npart; ++i)
			old_cin += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
		old_T = (2.0 / 3.0) * old_cin / (double)npart;
	}
	else{
		old_T = media_temp_scaling;
		i_scaling = 0;
	}
	
	double fs = sqrt(temp/old_T);			// fs = velocity scale factor
	for (int i=0; i<npart; ++i){
		vx[i] *= fs;
		vy[i] *= fs;
		vz[i] *= fs;

		xold[i] = Pbc(x[i] - vx[i] * delta);
		yold[i] = Pbc(y[i] - vy[i] * delta);
		zold[i] = Pbc(z[i] - vz[i] * delta);
	}
	
	cout << "ok!" << endl;
	return;
}




void Move(void){ //Move particles with Verlet algorithm
	double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

	for(int i=0; i<npart; ++i){ //Force acting on particle i
		fx[i] = Force(i,0);
		fy[i] = Force(i,1);
		fz[i] = Force(i,2);
	}

	for(int i=0; i<npart; ++i){ //Verlet integration scheme

		xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
		ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
		znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

		vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
		vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
		vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

		xold[i] = x[i];
		yold[i] = y[i];
		zold[i] = z[i];

		x[i] = xnew;
		y[i] = ynew;
		z[i] = znew;
	}
	return;
}



double Force(int ip, int idir){ // Compute forces as -Grad_ip V(r)
	double f=0.0;
	double dvec[3], dr;

	for (int i=0; i<npart; ++i){
		if(i != ip){
			dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
			dvec[1] = Pbc( y[ip] - y[i] );
			dvec[2] = Pbc( z[ip] - z[i] );

			dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
			dr = sqrt(dr);

			if(dr < rcut){
				f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
			}
		}
	}
	return f;
}



void Measure(bool in_blocchi){		//Properties measurement

	double v, t, g, vij;
	double dx, dy, dz, dr;
	
	v = 0.0;						//reset observables
	t = 0.0;
	g = 0.0;

	for (int i=0; i<nbins; i++)		// reset histogram of g(r)
		stima_g[i] = 0;


	//cycle over pairs of particles
	
	for (int i=0; i<npart-1; i++){
		for (int j=i+1; j<npart; j++){

			dx = Pbc( xold[i] - xold[j] ); // here I use old configurations [old = r(t)]
			dy = Pbc( yold[i] - yold[j] ); // to be compatible with EKin which uses v(t)
			dz = Pbc( zold[i] - zold[j] ); // => EPot should be computed with r(t)

			
			dr = dx*dx + dy*dy + dz*dz;
			dr = sqrt(dr);

			if(dr < 0.5*box){
				// update histogram of g(r)
				int ind_dist = int(dr/bin_size);
				
				stima_g[ind_dist] += 2.;
			}
			
			if(dr < rcut){
				vij = 4.0/pow(dr,12) - 4.0/pow(dr,6); //Potential energy
				v += vij;
			}
		}
	}
									//Kinetic energy
	for (int i=0; i<npart; ++i)
		t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
	
	stima_pot = v/(double)npart + vtail;			//Potential energy per particle
	stima_kin = t/(double)npart;					//Kinetic energy per particle
	stima_temp = (2.0 / 3.0) * t/(double)npart;		//Temperature
	stima_etot = (t+v)/(double)npart;				//Total energy per particle


	media_pot += stima_pot;
	media_kin += stima_kin;
	media_etot += stima_etot;
	media_temp += stima_temp;

	for (int i=0; i<nbins; i++){
	
		double den = rho*npart*(4./3.)*M_PI*(pow((i+1.5)*bin_size,3.)-pow((i+0.5)*bin_size,3.));
		
		media_g[i] += stima_g[i] / den;
	}

	len_block ++;



	media_temp_scaling = ((media_temp_scaling * i_scaling) + stima_temp)/(i_scaling+1.);
	i_scaling ++;



	if (in_blocchi){
		
		blocchi[iv][i_block] = media_pot / double(len_block);
		blocchi[ik][i_block] = media_kin / double(len_block);
		blocchi[ie][i_block] = media_etot / double(len_block);
		blocchi[it][i_block] = media_temp / double(len_block);
		
		ofstream Gofr;
		Gofr.open("results/output_gofr.dat",ios::app);
		
		for (int i=0; i<nbins; i++){
			blocchi[igofr+i][i_block] = media_g[i] / double(len_block);
			Gofr << media_g[i] / double(len_block) << " \t";
		}
		Gofr << endl;
		Gofr.close();
		
		i_block ++;
		
		media_pot = 0;
		media_kin = 0;
		media_etot = 0;
		media_temp = 0;
		
		for (int i=0; i<nbins; i++){
	        media_g[i] = 0;
        }
		
		len_block = 0;
	}
	return;
}



void ConfFinal(void){				//Write final configurations
	ofstream WriteConf;

	cout << endl << "Print final configuration to file config.final" << endl;
	WriteConf.open("config.final");

	for (int i=0; i<npart; ++i){
		WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
	}
	WriteConf.close();

	cout << "Print final-1 configuration to file config.final-1 " << endl << endl;
	WriteConf.open("config.final-1");

	for (int i=0; i<npart; ++i){
		WriteConf << xold[i]/box << "   " <<  yold[i]/box << "   " << zold[i]/box << endl;
	}
	WriteConf.close();

	return;
}



void Salva_Blocchi(void){
	
	const char* nomi_files[] = {"results/output_epot_blocchi.dat","results/output_ekin_blocchi.dat","results/output_etot_blocchi.dat","results/output_temp_blocchi.dat"};
	
	Print_media_sigma_blocchi_multi(blocchi, i_block, n_props-nbins, nomi_files);
	
	
	// Write final average g(r) with std
	
	ofstream Gave("results/output_gave.dat");
	for (int i=0; i<nbins; i++){
		double mean = 0;
		double mean2 = 0;
		for(int j=0; j<i_block; j++){
			mean += blocchi[igofr+i][j] / double(i_block) ;
			mean2 += pow(blocchi[igofr+i][j],2) / double(i_block) ;
		}
		Gave << (i+0.5)*bin_size << "\t " << mean << "\t " << sqrt((mean2 - pow(mean,2))/(i_block-1)) << endl;
	}
	Gave.close();
	
	return;
}



void ConfXYZ(int nconf){			//Write configuration in .xyz format
	ofstream WriteXYZ;

	WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
	WriteXYZ << npart << endl;
	WriteXYZ << "This is only a comment!" << endl;
	for (int i=0; i<npart; ++i){
		WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
	}
	WriteXYZ.close();
}



double Pbc(double r){				//Algorithm for periodic boundary conditions with side L = box
	return r - box * rint(r/box);
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
