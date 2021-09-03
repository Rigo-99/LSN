#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;


double media(double v[], int size) {
	double sum = 0;	
	for(int i=0; i<size; i++){
		sum += v[i];
	}
	return sum/double(size);
}


double stdev(double v[], int size) {

	if (size == 0)
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


double dist(double v[3]){
	return (sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2)));
}



double psiT (double x, double mu, double sigma){
	return exp(-pow(x-mu,2)/(2*pow(sigma,2))) + exp(-pow(x+mu,2)/(2*pow(sigma,2)));
}


double psi2T (double x, double mu, double sigma){
	return pow(psiT(x,mu,sigma),2);
}



double d2psiT (double x, double mu, double sigma){
	return (exp( -pow(mu+x,2)/(2*pow(sigma,2)) ) * (exp( 2*mu*x/pow(sigma,2) ) *(mu-sigma-x)*(mu+sigma-x)+pow(mu+x,2)-pow(sigma,2)) )/pow(sigma,4);
}



double K (double x, double mu, double sigma){
	double h_bar = 1;
	double m = 1;	
	return (double(-pow(h_bar,2))/double(2*m)) * d2psiT(x, mu, sigma) / psiT(x, mu, sigma) ;
}



double V (double x){
	return pow(x,4) - (5./2.)*pow(x,2);
}








void show_vec(double v[], int size, const char* header){
	cout << "**** " << header << " ****" << endl;
	for (int k = 0; k < size; k++)
		cout << v[k] << endl;
}


void show_vec_2(vector<int> v, const char* header){
	if (v.size() > 0){
		for (int k = 0; k < v.size(); k++)
			cout << v[k] << "\t";
	}
	cout << endl;
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
	
	for(int i=0; i<size; i++){
		out << media(block,i) << " " << stdev(block,i) << endl;
	}
	out.close();
}





