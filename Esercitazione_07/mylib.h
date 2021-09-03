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

double psi2T(double x, double mu, double sigma);
double d2psiT(double x, double mu, double sigma);
double K(double x, double mu, double sigma);
double V(double x);

void show_vec(double v[], int size, const char* header) ;
void Print(double v[], int size, const char* NomeFile) ;
void Print_valore_incertezza(double val[], double sigma[], int size, const char* NomeFile) ;
void Print_media_sigma_blocchi(double blocchi[], int size, const char* NomeFile);
void Print_media_sigma_blocchi_multi(double block[][9999], int size, int n_param, const char* NomeFile[]);

#endif

