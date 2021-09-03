/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//parameters, observables
const int m_props=120;				// abbastanza grande, mi serve per fare un array bidimensionale statico GLOBALE
int n_props,nbins;
int iv,ik,it,ie,ig,igofr;
double stima_pot, stima_kin, stima_etot, stima_temp, stima_gave;
double bin_size;

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];

// averages
double acc,att;
const int massimo_misure = 9999;	// abbastanza grande, mi serve per fare un array bidimensionale statico GLOBALE
double blocchi[m_props][massimo_misure];
int i_block=0;
int len_block=0;
double media_pot, media_kin, media_etot, media_temp, media_gave = 0;
double media_temp_scaling = 0;
int i_scaling = 0;

double stima_g[100];
double media_g[100];


// thermodynamical state
int npart;
double energy,temp,vol,rho,box,rcut;
double vtail;

// simulation
int nstep, iprint, seed;
double delta;

//functions
void Input(bool restart);
void Move(void);
void Rescale(void);
void ConfFinal(void);
void ConfXYZ(int);
void Salva_Blocchi(void);
void Measure(bool in_blocchi);
double Force(int, int);
double Pbc(double);
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
