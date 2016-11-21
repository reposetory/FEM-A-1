#ifndef ALGORITHM
#define ALGORITHM


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

void initial_boundary(vector<double>& u_ini,vector<double>& grid);

void solver_back_euler(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T) ;

#endif