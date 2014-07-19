#include "init.h"
#include "routines.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifdef _OMP
#include <omp.h>
#endif

using namespace std;

init::init( int Nw_in, double Lw_in, double U_in, double T_in, double gamma_in )
{
  Nw = Nw_in;
  Lw = Lw_in;
  U = U_in;
  T = T_in;
  gamma = gamma_in;

  omega = new double [Nw];
  fermi = new double [Nw];
  DOS   = new double [Nw];
  G0    = new complex<double> [Nw];
}

void init::init_funcs()
{
  for( int i=0; i<Nw; i++)
  {
    omega[i] = -Lw + 2.0*Lw*i/(Nw-1) ;
    //cout<< omega[i] <<endl;
    fermi[i] = FermiFunction(omega[i], T );
    DOS[i]   = SemiCircleDOS(omega[i]);
  }

  for( int i=0; i<Nw; i++)
  {
    G0[i]    = Hilbert(Nw, (omega[i])+0.001j , omega, DOS);
    //printf("%f \t %f \t %f \t %f \t %f \n", omega[i], fermi[i], DOS[i], real(G0[i]), imag(G0[i]) );
  }

}

int init::get_Nw()
{
  return Nw;
}

double init::get_U()
{
  return U;
} 

double init::get_T()
{
  return T;
}
