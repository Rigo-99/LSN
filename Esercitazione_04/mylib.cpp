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
		double sigma = stdev(block,i);
		out.precision(int(2-log(sigma)));
		out << fixed << media(block,i) << " " << sigma << endl;
	}
	out.close();
}



void Print_media_sigma_blocchi_multi(double block[][9999], int size, int n_param, const char* NomeFile[]){
	
	for(int i=0; i<n_param; i++){
		ofstream out(NomeFile[i]);
	
		for(int j=1; j<=size; j++){
			double sigma = stdev(block[i],j);
			out.precision(int(2-log(sigma)));
			out << fixed << media(block[i],j) << " " << sigma << endl;
		}
		out.close();
	}
}



