/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include "random.h"
#include <vector>
#ifndef __Genetics__
#define __Genetics__

using namespace std;


class Popolazione;
class Individuo;
class Mappa;
struct Citta;



class Popolazione {

public:
	int n_pop, l_DNA;
	double media;
	double stdev;
	double best;
	double elitarieta, mutabilita;
	Random* rnd;
	Mappa* map;

	vector<Individuo> popolo;

	
// constructors
	Popolazione(Random* generatore, Mappa* mappa, int n_individui, int lunghezza_DNA, double elite, double mut);

// destructor
	~Popolazione();

// methods
	void Popolazione_Random();
	void Nuova_Generazione(int n_accoppiamenti);
	Individuo Accoppia(int a, int b);
	void Rimpiazza_a_caso(Individuo nuovo);
	
	void Mostra();
	void Ordina();				// Raddrizza e Aggiorna!
	void Statistica();
};





class Individuo {

public:
	int l_DNA;
	Random* rnd;
	vector<int> DNA;
	double length;

// constructors
	Individuo(Random* generatore, int lunghezza_DNA, vector<int> patrimonio);
	Individuo(Random* generatore, int lunghezza_DNA);

// destructor
	~Individuo();

// methods	
	Individuo Duplica();
	void Standard();
	void Aggiorna(Mappa* map);
	void Permuta(int n_perm);
	double Misura_Lunghezza_Percorso(Mappa* map);
	void Mostra();
	void Stampa(string nome_file);
	
	void Mutazione_1();
	void Mutazione_2();
	void Mutazione_3();
	void Mutazione_4();
	
	void Raddrizza();
	
	
	
};





class Mappa {

public:
	int n_punti;
	Random* rnd;
	vector<Citta> posizioni;

// constructors
	Mappa(Random* generatore, int numero_punti);
	Mappa(string input_file);

// destructor
	~Mappa();

// methods
	void Genera_in_quadrato(double lato);
	void Genera_su_cerchio(double raggio);
	double Misura_Distanza_Citta(int prima, int seconda);
	double Misura_Lunghezza_Percorso(Individuo percorso);
	void Mostra();
	void Stampa(string nome_file);
};




struct Citta {
   double x;
   double y;
};


#endif // __Genetics__

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
