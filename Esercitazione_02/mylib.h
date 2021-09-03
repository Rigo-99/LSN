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
double g2_2(double x);
double inversa(double x);

void show_vec(double v[], int size, const char* header) ;
void Print(double v[], int size, const char* NomeFile) ;
void Print_valore_incertezza(double val[], double sigma[], int size, const char* NomeFile) ;
void Print_media_sigma_blocchi(double blocchi[], int size, const char* NomeFile);


#endif

