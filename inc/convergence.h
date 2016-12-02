#ifndef CONVER
#define CONVER

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;



// calculate differences between two timesteps, for convergence
void differences_1d(string outputfilename, string solvername,MatrixXd & u, MatrixXd & u_ini, MatrixXd & grid);
        //output u - u_ini per point per time step for plotting to turn into a video to show if plot flattens over time
        //print out yes/no
// 1D (2D periodic boundary conditions) convergence stability and accuracy for the 1d four basic algorithms
void convergence_1d(string outputfilename,string solvername,string boundaryname,vector<double> &u_ini,vector<double>  &grid,double& k,double& h,double& T,double delta=10e-7);

#endif
