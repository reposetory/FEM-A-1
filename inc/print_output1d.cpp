#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

void print_output1d(string filename,string solvername,vector<double> grids,vector<double> u_ini,MatrixXd u,double h_space,double k_time,double T_end){
/*
save the result to a file
*/

int n_step=grids.size();
int n_time=T_end/k_time;

//make a separate file for each time step, name has time value
for (int i = 0; i < n_time; i++){

ofstream writefile;
string fullname;
std::ostringstream strs;
cout.precision(4); 
strs <<  (i+1.0)*k_time;
std::string timename = strs.str();

fullname = filename + "_" + solvername + "_time_" + timename + "_.dat";
writefile.open (fullname.c_str() , ios::out);
//writefile<<"This is the output for 1D heat equation"<<endl;
//writefile<<"grid points "<<'\n';

for(int j=0;j<n_step;j++){
    writefile << grids[j]<<" ";
    writefile << '\t'; 
//    writefile << u_ini[i] << " ";
    writefile << u(i,j) << " ";
    writefile << '\n'; 
}


writefile.close();
}

}
