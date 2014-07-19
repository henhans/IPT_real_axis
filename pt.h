/* class for perturbation calculations 07/16/2014 Tsung-Han Lee*/

#ifndef PT_
#define PT_
#include <complex>
#include "init.h"

using namespace std;

class init;

class pt
{
  public:
  pt(init Init);

  void get_sig(); // calculate self energy
  void mix_sig(double mix); //mixing self energy
  double get_diff(); // calculate self energy difference betwen consecutive iterations
  void get_G_G0(); // calculate Green's function G and G0
  void printdata(const char* filename); // print out all datas

  double* omega;
  double* fermi;
  double* DOS;
  double* Ap;
  double* Am;
  double* P1;
  double* P2;
  double* isig;
  double* rsig;
  complex<double>* sigma;
  complex<double>* sigma_new;
  complex<double>* G0;
  complex<double>* G;

  //void init_funcs();
  
  private:
  int Nw; //number of omega point
  double U; // coulomb potential
  double T; // temperature

};

#endif
