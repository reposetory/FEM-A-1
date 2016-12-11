#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

void print_output(string filename,string solvername,vector<double> grids,vector<double> u_ini,MatrixXd u,double h_space,double k_time,double T_end){
//save the result to a file
int n_step=grids.size();
int n_time=T_end/k_time;
double timeat;
ofstream writefile;
string fullname;
string path;
std::ostringstream strs;
path = "./output/" + solvername + "/";
//fullname = "./output/" + solvername + "/" + filename + "_" + solvername + "_.dat";
fullname = "./output/out_" + filename + "_" + solvername + "_.dat";
writefile.open(fullname.c_str(), ios::out);

for (int i = 0; i < n_time; i++){
//writefile<<"This is the output for 1D heat equation"<<endl;
//writefile<<"grid points "<<'\n';
timeat = k_time*i;
for(int j=0;j<n_step;j++){
  if(j == 0){
    writefile << "-1 " << '\t' << timeat << " " << '\t' << '\n';
  }
    writefile << grids[j]<<" ";
    writefile << '\t';
    writefile << u(i,j) << " " << '\t';
/*  if(j ==0){
    writefile << " " <<  timeat << " " << '\t';
  } else{
    writefile << " 0 " << '\t';
  }
*/
  writefile << '\n';

  if(j == n_step-1 && i != n_time-1){
    writefile << '\n' << '\n';
  }
}
}
writefile.close();
}





void print_output_2D(string filename,string solvername,vector<double> grids, MatrixXd u_ini,MatrixXd u,double h_space,double k_time,double T_end){
int n_step=grids.size();
int n_time=T_end/k_time;
double timeat;
ofstream writefile;
string fullname;
string path;
std::ostringstream strs;
path = "./output/" + solvername + "/";
//fullname = "./output/" + solvername + "/" + filename + "_.dat";
fullname = "./output/out_" + filename + "_" + solvername + "2D_.dat";
writefile.open(fullname.c_str(), ios::out);

for (int i = 0; i < n_time; i++){
timeat = k_time*i;
  for (int j = 0; j < n_step;j++){
    for(int k = 0; k < n_step; k++){
      if(j == 0){
        writefile << "-1 " << '\t' << timeat << " " << '\t' << "0 " << '\t'  << '\n';
      }

      writefile << grids[j] << " " << '\t';
      writefile << grids[k] << " " << '\t';
      writefile << u(i,j+k*n_time) << " " << '\t';
      writefile << '\n';

      if(j == n_step-1 && i != n_time-1){
        writefile << '\n' << '\n';
      }

    }
  }
}
writefile.close();
}



void print_output_3D(string filename,string solvername,MatrixXd grid_3d, MatrixXd u_ini,MatrixXd u,double h_space,double k_time,double T_end){
/*
save the result to a file
*/
ofstream writefile;
string fullname;
fullname=filename+"_"+solvername+"_3D"+".dat";
writefile.open (fullname.c_str() , ios::out);
writefile<<"This is the output for 3D heat equation"<<endl;
writefile << "Parameters:" << '\n' << "sovername: " << solvername << '\n' << "space step: " << h_space << '\n' << "time step: " << k_time << '\n' << "total time: " << T_end << '\n'<<endl;

int n_step=grid_3d.rows();
int n_time=T_end/k_time;

writefile<<"grid points "<<'\n';

for(int i=0;i<3;i++){
  for (int j =0;j<n_step;j++) {
		writefile << grid_3d(j,i) << " ";
  }
  writefile << '\n';
}

writefile<<"Time 0"<<'\n';
for (int j =0;j<n_step;j++) {
  writefile << u_ini(j) << " ";
}
writefile << '\n';

for(int n=0;n<n_time;n++){
  writefile<<"Time "<<double(n+1)*k_time<<'\n';
  for (int j =0;j<n_step;j++) {
    writefile << u(n,j) << " ";
  }
  writefile << '\n';
}

writefile.close();


}
