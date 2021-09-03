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


double g2_2(double x){
	return ((M_PI/2) * (-x+1));
}


double inversa(double x){
	return (1-sqrt(1-x));
}


double dist(double v[3]){
	return (sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2)));
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






