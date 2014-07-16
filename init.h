#include <complex>

using namespace std;

class init
{
  public:
  init(int Nw_in, double Lw_in, double U_in, double T_in, double gamma_in );

  void init_funcs();
  int get_Nw();
  double get_U();
  double get_T();

  double* omega;
  double* fermi;
  double* DOS;
  complex <double>* G0;
  
  private:
  int Nw; //number of omega point
  double Lw; //cut of of the frequency
  double U; // coulomb potential
  double T; // temperature
  double gamma; // brodening pole

};
