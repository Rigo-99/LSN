#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#ifndef _funzioni_h_
#define _funzioni_h_

double media(double v[], int size) ;
double stdev(double v[], int size) ;

double dist(double v[3]) ;

double Poly(double x, int grado, double coeff[]);
double f2_1(double x);

double get_r(double x, double y, double z);
double get_theta(double x, double y, double z);
double get_phi(double x, double y, double z);

double psi100 (double x, double y, double z);
double psi210 (double x, double y, double z);

void show_vec(double v[], int size, const char* header) ;
void Print(double v[], int size, const char* NomeFile) ;
void Print_valore_incertezza(double val[], double sigma[], int size, const char* NomeFile) ;
void Print_media_sigma_blocchi(double blocchi[], int size, const char* NomeFile);


#endif

