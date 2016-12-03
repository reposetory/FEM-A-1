#ifndef RESULT
#define RESULT

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;


void print_output(string filename,string solvername,vector<double>& grids,vector<double>& u_ini,MatrixXd& u,double& h_space,double& k_time,double& T_end);


#endif
