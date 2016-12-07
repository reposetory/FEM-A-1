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

void initial_boundary_2D(MatrixXd& u_ini, vector<double> grid);
void boundary_1d_1_2D(vector<double>& u_ini, vector<double> grid, double delta = 0.0);

//2D FEM algorithm
void solver_FEM_2D(MatrixXd &u,MatrixXd u_ini, MatrixXd grid, double k, double h, double T);


//2D back_euler algorithm
void solver_back_euler_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T);
//2D euler algorithm
void solver_euler_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T);
//2D Crank-Nicolson algorithm
void solver_crank_nicolson_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T);
//2D Dufort-Frankel
void solver_DuFort_Frankel_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T);


#endif
