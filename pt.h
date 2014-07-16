#include <complex>
//#include "init.h"

using namespace std;

class init;

class pt
{
  public:
  pt(init Init);

  void get_sig();
  void mix_sig(double mix);
  double get_diff();
  void get_G_G0();  
  void printdata(const char* filename);

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
