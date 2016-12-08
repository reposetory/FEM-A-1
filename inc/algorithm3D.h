#ifndef algorithm3D
#define ALGORITHM3D


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;
//boundary conditions

void  initial_boundary_3D(MatrixXd& u_ini,  MatrixXd& grid_3d, vector<double> grid,int ngrid);

void boundary_3D_1(MatrixXd& u_ini,  MatrixXd& grid_3d, vector<double> grid,int ngrid,double delta=0.0);


//3D euler algorithm
void solver_back_euler_3D(MatrixXd &u, MatrixXd u_ini,MatrixXd grid_3d, double k, double h, double T,int ngrid);



#endif
