#ifndef CONVER
#define CONVER

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;




// calculate differences between two timesteps, for convergence test.
// output from this function is a ".dat" file ended with "_difference" that records the difference between the current time steo and previous time step
// there will be a screen output that says whether the algorithm is converge or not
void differences_1d(string outputfilename,string solvername,MatrixXd &u,vector<double> u_ini,vector<double>  grid,double k,double h,double T);
        //output u - u_ini per point per time step for plotting to turn into a video to show if plot flattens over time
        //print out yes/no


// for stability test
// output from this file is three ".dat" files ended with "_plus" "_minus" and "_original" that record the solutios with  u_ini, u_ini+delta, u_ini-delta as initial condition.
// post-process requires plot the three ".dat" file in one figure to show whether a small disturb will have a significant effect on the solution
void stability_1d(string outputfilename,string solvername,string boundaryname,vector<double> u_ini,vector<double> grid,double k,double h,double T,double delta=10e-7);

#endif
