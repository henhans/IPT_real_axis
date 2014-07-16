#include "pt.h"
#include "routines.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

pt::pt( init Init )
{
  Nw = Init.get_Nw();
  U = Init.get_U();
  T = Init.get_T();

  omega = new double [Nw];
  fermi = new double [Nw];
  DOS = new double [Nw];
  Ap = new double [Nw];
  Am = new double [Nw];
  P1 = new double [Nw];
  P2 = new double [Nw];
  isig = new double [Nw];
  rsig = new double[Nw];
  sigma = new complex<double> [Nw];
  sigma_new = new complex<double> [Nw];
  G0 = new complex<double> [Nw];
  G = new complex<double> [Nw];

  for (int i=0; i< Nw; i++)
  {
     sigma[i] =0;
     G0[i] = Init.G0[i];
     omega[i] = Init.omega[i];
     fermi[i] = Init.fermi[i];
     DOS[i] = Init.DOS[i];
     //cout<< G0[i]<<endl;
  }
  //cout << Init.omega[0]<< endl;
}

void pt::get_sig()
{
   for( int i=0; i< Nw; i++ )
   {
     Ap[i] = (-1/pi)*imag(G0[i])*fermi[i];
     Am[i] = (-1/pi)*imag(G0[i])*(1- fermi[i]);
   }

   double dh= omega[1]-omega[0];

   for (int ix=0; ix<Nw; ix++)
   {
     double sum1=0;
     double sum2=0;

     for (int iy=0; iy<Nw; iy++)
     { 
       int iz = (iy-Nw/2) - (ix-Nw/2) + Nw/2;
       if (iz<0 || iz>=Nw )
         iz=-1;

       if (iz>=0)
       {
         sum1 += Am[iy] * Ap[iz];
         sum2 += Ap[iy] * Am[iz];
       }
     }
     P1[ix] = sum1*dh;
     P2[ix] = sum2*dh;
   }

   for (int ix=0; ix<Nw; ix++)
   {
     double sum1=0;
     double sum2=0;

     for (int iy=0; iy<Nw; iy++)
     {
       int iz = (iy-Nw/2) - (ix-Nw/2) + Nw/2;
       if (iz<0 || iz>=Nw )
         iz=-1;

       if (iz>=0)
       {
         sum1 += Ap[iy] * P1[iz];
         sum2 += Am[iy] * P2[iz];
       }
     }
     isig[ix] = (sum1+sum2)*dh;
     isig[ix] *= -sqr(U)*pi;
   }

   KramarsKronig(Nw, omega, isig, rsig);

   for(int i=0; i<Nw; i++)
   {
     sigma_new[i] = rsig[i] + isig[i]*(1j);
     //printf("%f \t %f \t %f \n", omega[i], real(sigma_new[i]), imag(sigma_new[i]));
   }
   
}

void pt::mix_sig(double mix)
{
  for( int i=0; i< Nw; i++)
  {
    sigma[i] = sigma[i]*(1-mix) + sigma_new[i]*mix;
  }
}

double pt::get_diff()
{
  double diff[Nw];
  for (int i=0; i<Nw; i++)
  {
    diff[i] = abs(sigma_new[i] -sigma[i] );
  }
  
  return TrapezIntegral( Nw , diff , omega ); 
}

void pt::get_G_G0()
{
  for( int i=0; i<Nw; i++)
    G[i] = Hilbert(Nw, omega[i]-sigma[i], omega, DOS);

  for( int i=0; i<Nw; i++)
    G0[i] = 1.0/(1.0/G[i] + sigma[i]);
  //G0[i] = 1/(omega[i]-(0.5)**2*G[i]);

  for (int i=0; i<Nw; i++) // remove the points violate casulty
    if ( imag(G0[i])>0 )
      G0[i] = real(G0[i]) -1e-10j;

}

void pt::printdata(const char* filename)
{
  FILE *f;
  f = fopen(filename, "w");
  for (int i=0; i<Nw; i++)
    fprintf(f,"%.15le %.15le %.15le %.15le %.15le\n", omega[i], -real(G[i]), -imag(G[i]), real(sigma[i]), imag(sigma[i]));
  fclose(f);

}
