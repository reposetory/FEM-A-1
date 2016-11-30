#ifndef CONVER
#define CONVER

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;

// study the convergence stability and accuracy for 1d four basic algorithm
void convergence_1d(string solvername,string boundaryname,double delta=10e-7,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T);
// study the convergence stability and accuracy for 1d fem
void convergence_1d_fem();

#endif
