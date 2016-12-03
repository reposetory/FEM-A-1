#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

void print_output(string filename,string solvername,vector<double> grids,vector<double> u_ini,MatrixXd u,double h_space,double k_time,double T_end){
/*
save the result to a file
*/
ofstream writefile;
string fullname;
fullname=filename+"_"+solvername+".dat";
writefile.open (fullname.c_str() , ios::out);
writefile<<"This is the output for 1D heat equation"<<endl;

int n_step=grids.size();
int n_time=T_end/k_time;

writefile<<"grid points "<<'\n';

for(int i=0;i<n_step;i++){
    writefile<<grids[i]<<" ";

}
writefile<<'\n';
writefile<<"Time 0"<<'\n';
for(int i=0;i<n_step;i++){
    writefile<<u_ini[i]<<" ";
}
writefile<<'\n';


for(int i=0;i<n_time;i++){
    writefile<<"Time "<<double(i+1)*k_time<<'\n';
    for(int j=0;j<n_step;j++){
    writefile<<u(i,j)<<" ";
    }
    writefile<<'\n';
}
writefile.close();


}
