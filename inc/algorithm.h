#ifndef ALGORITHM
#define ALGORITHM


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;
//boundary conditions
void initial_boundary(vector<double>& u_ini,vector<double>& grid);
void boundary_1d_1(vector<double>& u_ini,vector<double>& grid,double delta=0.0);

//1D back_euler algorithm
void solver_back_euler_1D(MatrixXd &u,vector<double> u_ini,vector<double> grid,double k,double h,double T) ;
//1D euler algorithm
void solver_euler_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T) ;
//1D Crank-Nicolson algorithm
void solver_crank_nicolson_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T) ;
//1D Dufort-Frankel
void solver_DuFort_Frankel_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T) ;
//1D FEM
void solver_FEM_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T) ;


#endif
