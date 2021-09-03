#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


double media(double v[], int size) {

	if (size == 0)
		return 0;

	double sum = 0;	
	for(int i=0; i<size; i++){
		sum += v[i];
	}
	return sum/double(size);
}


double stdev(double v[], int size) {

	if (size <= 1)
		return 0;

	double mean = 0;
	double mean2 = 0;
	for(int i=0; i<size; i++){
		mean += v[i] / double(size) ;
		mean2 += pow(v[i],2) / double(size) ;
	}
	return sqrt((mean2 - pow(mean,2))/(size-1));
}



double Poly(double x, int grado, double coeff[]){
	double cum = 0;
	
	for (int d=grado; d>=0; d--){
		cum += coeff[grado-d] * pow(x,d);
	}
	return cum;
}


double f2_1(double x){
	return ((M_PI/2) * cos(x * M_PI/2));
}


double dist(double v[3]){
	return (sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2)));
}


double get_r(double x, double y, double z){
	return sqrt(x*x+y*y+z*z);
}

double get_theta(double x, double y, double z){
	return acos(z/sqrt(x*x+y*y+z*z));
}

double get_phi(double x, double y, double z){
	return atan2(y,x);
}



double psi100 (double x, double y, double z){
	const double a0 = 0.0529e-9;
	double r = get_r(x,y,z);
	return pow(pow(a0,-1.5)*exp(-r)/sqrt(M_PI) , 2);
}


double psi210 (double x, double y, double z){
	const double a0 = 0.0529e-9;
	double r = get_r(x,y,z);
	double theta = get_theta(x,y,z);
	//return pow((pow(a0,-2.5)/8)*sqrt(2/M_PI) * r * exp(-r/2) * cos(theta) , 2);
	return pow(a0,-5)*r*r*exp(-r)*pow(cos(theta),2)/(32*M_PI);
}




void show_vec(double v[], int size, const char* header){
	cout << "**** " << header << " ****" << endl;
	for (int k = 0; k < size; k++)
		cout << v[k] << endl;
}


void Print(double v[], int size, const char* NomeFile) {
	ofstream out(NomeFile);
	for (int k = 0; k < size; k++)
		out << v[k] << endl;

	out.close();
}


void Print_valore_incertezza(double val[], double sigma[], int size, const char* NomeFile) {
	ofstream out(NomeFile);
	
	for(int i=0; i<size; i++){
		out << val[i] << " " << sigma[i] << endl;
	}
	out.close();
}


void Print_media_sigma_blocchi(double block[], int size, const char* NomeFile) {
	ofstream out(NomeFile);
	
	for(int i=1; i<=size; i++){
		out << media(block,i) << " " << stdev(block,i) << endl;
	}
	out.close();
}












