#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#ifndef _funzioni_h_
#define _funzioni_h_

double media(double v[], int size) ;
double stdev(double v[], int size) ;

void show_vec(double v[], int size, const char* header) ;
void Print(double v[], int size, const char* NomeFile) ;
void Print_valore_incertezza(double val[], double sigma[], int size, const char* NomeFile) ;
void Print_media_sigma_blocchi(double blocchi[], int size, const char* NomeFile);


#endif

