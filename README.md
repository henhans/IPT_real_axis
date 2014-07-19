IPT_real_axis
=============

DMFT with IPT solver on linear real axis at half filling. The coding is based on Dr. Haule's class material at http://www.physics.rutgers.edu/~haule/681/perturbation.html. Type "make" to compile the file, there are parallel and nonparallel version of makefile in the folder. It'll generate an main.exe file. Run ./main.exe will generate an ouput file "ipt.dat" with omega, -re(G), -im(G), re(Sigma), im(Sigma) from column 1 to 5 respectively. Tuning the paramter U and T we can see different metal or insulator solutions. If the calculation does not converge, try tuning mix constant to check the convergence.

The class init.h is to initialize the parameters and functions. The class pt.h do the main iterative perturbation calculation and store the data for each iterations. The rouines.h has the basic function for doing integration, Hilbert transform and KramarsKronig relation.

Tsung-Han Lee 07/16/2014
