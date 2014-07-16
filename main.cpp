/* DMFT with IPT solver on real axis based on Dr. Haule's lecture materials.   
                                                   07/16/2014 Tsung-Han Lee */
#include "init.h"
#include "pt.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
  int Nw=801; //number of omega point
  double Lw=4; //cut of of the frequency
  double U=3.0; // coulomb potential
  double T=0.02; // temperature
  double gamma=0.04; // brodening pole

  int Nit=400; // number of DMFT iteration
  double mix=0.9; // mixing constant for old and new solution

  
  init Init( Nw, Lw, U, T, gamma );

  Init.init_funcs();

  pt Pt( Init);
  double old_diff=1e10;
  //cout << old_diff << endl;

  for( int it=0; it< Nit; it++)   
  { 
    Pt.get_sig();
    double diff = Pt.get_diff(); //calculate difference
    //cout << diff <<endl;

    // mixing solutions
    if (diff<1e-4) 
      break;
    if (diff>old_diff)
        mix = mix/1.2;
    old_diff = diff;
    Pt.mix_sig(mix);
    printf("it= %i \t diff= %f \t mix= %f \n", it, diff, mix);

    Pt.get_G_G0(); // calculate Green's functions
  }

  Pt.printdata("ipt.dat"); 

  return 0;
}
