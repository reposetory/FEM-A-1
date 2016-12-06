#ifndef ALGORITHM2D
#define ALGORITHM2D


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;
//boundary conditions
void initial_boundary_2d(vector<double>& u_ini,vector<double> grid);
void boundary_2d_1(vector<double>& u_ini,vector<double> grid,double delta=0.0);


//2D FEM algorithm
void solver_FEM_2D(MatrixXd u_ini, MatrixXd grid, double k, double h, double T);


#endif
