#ifndef READ
#define READ

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

 void read_input(string input_filename, string& filename, string& solvername, vector<double>& grids, double& h_space, double& k_time, double& T_end,int & dimension) ;


#endif
