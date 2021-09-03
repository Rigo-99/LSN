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
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "genetics.h"
#include "random.h"

using namespace std;





/******************** P O P O L A Z I O N E ***********************/


Popolazione :: Popolazione(Random* generatore, Mappa* mappa, int n_individui, int lunghezza_DNA, double elite, double mut){
	
	rnd = generatore;
	map = mappa;
	n_pop = n_individui;
	l_DNA = lunghezza_DNA;
	elitarieta = elite;
	mutabilita = mut;
	return;
}




Popolazione :: ~Popolazione(){}




void Popolazione :: Popolazione_Random(){
	
	Individuo tipo(rnd, l_DNA);
	tipo.Standard();
	tipo.Aggiorna(map);
	
	popolo.push_back(tipo);
	
	for(int i=1;i<n_pop;i++){
		tipo.Permuta(l_DNA);
		tipo.Raddrizza();
		tipo.Aggiorna(map);
		popolo.push_back(tipo);
		
	}
	Ordina();
}




Individuo Popolazione :: Accoppia(int a, int b){
	
	int m = rnd->Randint(2,l_DNA-2);
	
	vector<int> patrimonio (popolo[a].DNA.begin(), popolo[a].DNA.begin()+m);
	
	int j=0;
	int r=m;
	
	while (r < l_DNA){
		
		if ( find(patrimonio.begin(), patrimonio.end(), popolo[b].DNA[j]) == patrimonio.end() ){
			
			patrimonio.push_back (popolo[b].DNA[j]);
			r++;
		}
		j++;
	}
	
	
	
	Individuo figlio (rnd, l_DNA, patrimonio);
	
	/*
	cout << "taglio dopo il " << m <<"° elemento" << endl;
	cout << "Padre:  " << flush;
	popolo[a].Mostra();
	cout << "Madre:  " << flush;
	popolo[b].Mostra();
	cout << "Figlio: " << flush;
	figlio.Mostra();
	cout << endl;
	*/

	
	return figlio;
}




void Popolazione :: Rimpiazza_a_caso(Individuo nuovo){
	
	int i = rnd->Randint(ceil(n_pop/2),n_pop-1);	// rimpiazza nella seconda metà
	
	popolo[i] = nuovo;
	
	return;
}




void Popolazione :: Nuova_Generazione(int n_accoppiamenti){

	Ordina();
	
	for(int i = 0; i<n_accoppiamenti; i++){
		
		int j = int(ceil(n_pop * pow(rnd->Rannyu(),elitarieta)))-1;
		int k = int(ceil(n_pop * pow(rnd->Rannyu(),elitarieta)))-1;

		Individuo figlio = Accoppia(j,k);
		
		if (rnd->Rannyu() < mutabilita){
			
			switch (rnd->Randint(1,4)){
				case 1: figlio.Mutazione_1();
				break;
				case 2: figlio.Mutazione_2();
				break;
				case 3: figlio.Mutazione_3();
				break;
				case 4: figlio.Mutazione_4();
				break;
			}
		}
		figlio.Raddrizza();
		figlio.Aggiorna(map);
		Rimpiazza_a_caso(figlio);
	}
	
	Ordina();

	return;
}




void Popolazione :: Ordina(){

	sort (popolo.begin(), popolo.end(), [&](Individuo a, Individuo b){
		return (a.length < b.length);
	});
	
	
}




void Popolazione :: Statistica(){

	Ordina();
	
	int ultimo = int(n_pop/2);
	
	double cum_meta = 0;
	double cum = 0;
	double cum2 = 0;
	
	for(int i=0; i<ultimo; i++){
		cum_meta += popolo[i].length;
	}
	for(int i=0; i<n_pop; i++){
		cum += popolo[i].length;
		cum2 += pow(popolo[i].length,2);
	}
				
	media = cum_meta / double(ultimo);
	best = popolo[0].length;
	stdev = sqrt(cum2/double(n_pop) - pow(cum/double(n_pop),2));
		
	return;
}




void Popolazione :: Mostra(){
	cout << "** POPOLAZIONE **" << endl;
	for(int i=0;i<n_pop;i++){
		popolo[i].Mostra();
	}
	cout << "*****************" << endl;
}



/******************** I N D I V I D U O ***********************/




Individuo :: Individuo(Random* generatore, int lunghezza_DNA, vector<int> patrimonio){
	l_DNA = lunghezza_DNA;
	rnd = generatore;
	DNA = patrimonio;
	length = -1;
	return;
}




Individuo :: Individuo(Random* generatore, int lunghezza_DNA){
	l_DNA = lunghezza_DNA;
	rnd = generatore;
	DNA.resize(l_DNA, 0);
	length = -1;
	return;
}




Individuo :: ~Individuo(){}
	
	
	
	
Individuo Individuo :: Duplica(){

	return Individuo(rnd, l_DNA, DNA);

}




void Individuo :: Standard(){

	for(int i=0; i<l_DNA; i++){
		DNA[i] = i;
	}

	return;
}




double Individuo :: Misura_Lunghezza_Percorso(Mappa* map){
	double cum = 0;
	
	for (int i=0; i<l_DNA ; i++){
		cum += map->Misura_Distanza_Citta(DNA[i], DNA[(i+1)%l_DNA]);
	}
	length = cum;
	return cum;
}




void Individuo :: Permuta(int n_perm){
	
	for(int i=0; i<n_perm; i++){
		int primo_indice = rnd->Rannyu(0,l_DNA);
		int secondo_indice = rnd->Rannyu(0,l_DNA);
		
		swap(DNA[primo_indice], DNA[secondo_indice]);
	}
	return;
}




void Individuo :: Mutazione_1(){
	Permuta(1);
	return;
}




void Individuo :: Mutazione_2(){
	
	int ini = 0;
	int fin = 0;
	
	while (ini == fin){
		ini = int(floor(rnd->Rannyu(0,l_DNA)));
		fin = int(floor(rnd->Rannyu(0,l_DNA)));
	}
	
	if (ini>fin){
		swap(ini,fin);
	}
		
	int n_ini = ini;
	

	while(n_ini == ini){
		n_ini = int(floor(rnd->Rannyu(0,l_DNA-(fin-ini)+1)));
	}
	
	//cout << "da " << ini << " a " << fin << " con new " << n_ini << endl;
	
	vector<int> cut (DNA.begin()+ini, DNA.begin()+fin+1);
	DNA.erase (DNA.begin()+ini, DNA.begin()+fin+1);
	
	if(n_ini == l_DNA-(fin-ini)){
		DNA.insert(DNA.end(), cut.begin(), cut.end());	
	}
	else{
		DNA.insert(DNA.begin()+n_ini, cut.begin(), cut.end());	
	}
	
	return;
}



void Individuo :: Mutazione_3(){
	
	int ini_1 = rnd->Rannyu(0,l_DNA-1);
	int ini_2 = rnd->Rannyu(ini_1+1,l_DNA);
	
	int limite = min(ini_2-ini_1 , l_DNA-ini_2);	
	int len = rnd->Rannyu(1,limite+1);
	
	vector<int> cut_1 (DNA.begin()+ini_1, DNA.begin()+ini_1+len);
	vector<int> cut_2 (DNA.begin()+ini_2, DNA.begin()+ini_2+len);
	
	DNA.erase (DNA.begin()+ini_2, DNA.begin()+ini_2+len);
	DNA.insert(DNA.begin()+ini_2, cut_1.begin(), cut_1.end());
	
	DNA.erase (DNA.begin()+ini_1, DNA.begin()+ini_1+len);
	DNA.insert(DNA.begin()+ini_1, cut_2.begin(), cut_2.end());
	
	return;
}




void Individuo :: Mutazione_4(){
	
	int ini = 0;
	int fin = 0;
	
	while (ini == fin){
		ini = rnd->Rannyu(0,l_DNA);
		fin = rnd->Rannyu(0,l_DNA);
	}
	
	if (ini>fin){
		swap(ini,fin);
	}
	
	vector<int> shifting (DNA.begin()+ini, DNA.begin()+fin+1);
	reverse(shifting.begin(),shifting.end()); 
	DNA.erase (DNA.begin()+ini, DNA.begin()+fin+1);
	DNA.insert(DNA.begin()+ini, shifting.begin(), shifting.end());
	
	return;
}




void Individuo :: Raddrizza(){
	
	//cout << endl;
	//Mostra();
	
	auto it = find (DNA.begin(), DNA.end(), 0);
	
	vector<int> cut (it, DNA.end());
	DNA.erase (it, DNA.end());
	
	DNA.insert(DNA.begin(), cut.begin(), cut.end());
	
	//Mostra();
	
	return;
}




void Individuo :: Aggiorna(Mappa* map){
	double cum = 0;
	
	for (int i=0; i<l_DNA; i++){
		cum += map->Misura_Distanza_Citta(DNA[i], DNA[(i+1)%l_DNA]);
	}
	length = cum;
	return;
}




void Individuo :: Mostra(){

	for(int i=0; i<l_DNA; i++){
		cout << DNA[i] << " \t";
	}
	cout << " →  " << length << endl;
	return;
}




void Individuo :: Stampa(string nome_file){
	
	ofstream out_path (nome_file);
	
	for(int i=0; i<l_DNA; i++){
		out_path << DNA[i] << " " << DNA[(i+1)%l_DNA] << endl;
	}
	
	out_path.close();
	
	return;
}





/******************** M A P P A ***********************/





Mappa :: Mappa(Random* generatore, int numero_punti){

	rnd = generatore;
	n_punti = numero_punti;
	
	return;
}



Mappa :: Mappa(string input_file){
	ifstream in (input_file);
	
	n_punti = 0;
	posizioni.clear();
	
	Citta pos;

	int trash;

	in >> trash;
	
	while (!(in.eof())){
		n_punti ++;
		
		in >> pos.x;
		in >> pos.y;
		posizioni.push_back(pos);
		
		in >> trash;
	}
	
}



Mappa :: ~Mappa(){}




void Mappa :: Genera_in_quadrato(double lato){
	
	posizioni.clear();
	
	Citta pos;
	
	for (int i=0; i<n_punti; i++){
		pos.x = lato*rnd->Rannyu();
		pos.y = lato*rnd->Rannyu();
		
		posizioni.push_back(pos);
	}
	return;
}




void Mappa :: Genera_su_cerchio(double raggio){
	
	posizioni.clear();
	
	Citta pos;
	
	for (int i=0; i<n_punti; i++){
		double angolo = rnd->Rannyu(0,2*M_PI);
		pos.x = raggio*cos(angolo);
		pos.y = raggio*sin(angolo);
		
		posizioni.push_back(pos);
	}
	return;
}




double Mappa :: Misura_Distanza_Citta(int prima, int seconda){

	//cout << prima << " - " << seconda << flush;

	double distanza = sqrt( pow(posizioni[prima].x - posizioni[seconda].x , 2) + pow(posizioni[prima].y - posizioni[seconda].y , 2) );

	//cout << " = " << distanza << endl;

	return distanza;
}




double Mappa :: Misura_Lunghezza_Percorso(Individuo percorso){
	double cum = 0;
	
	int l = percorso.l_DNA;
	
	for (int i=0; i<l ; i++){
		cum += Misura_Distanza_Citta(percorso.DNA[i], percorso.DNA[(i+1)%l]);
	}
	return cum;
}




void Mappa :: Mostra(){
	
	for (int i=0; i<n_punti ; i++){
		cout << "(" << posizioni[i].x << " , " << posizioni[i].y << ")" << endl;
	}
	
	return;
}



void Mappa :: Stampa(string nome_file){
	
	ofstream out_map (nome_file);
	
	for (int i=0; i<n_punti ; i++){
		out_map << i << " " << posizioni[i].x << " " << posizioni[i].y << endl;
	}
	
	out_map.close();
	
	return;
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
