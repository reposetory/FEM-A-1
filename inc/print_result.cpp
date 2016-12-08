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




void print_output_2D(string filename,string solvername,vector<double> grids, MatrixXd u_ini,MatrixXd u,double h_space,double k_time,double T_end){
/*
save the result to a file
*/
ofstream writefile;
string fullname;
fullname=filename+"_"+solvername+".dat";
writefile.open (fullname.c_str() , ios::out);
writefile<<"This is the output for 3D heat equation"<<endl;
writefile << "Parameters:" << '\n' << "sovername: " << solvername << '\n' << "space step: " << h_space << '\n' << "time step: " << k_time << '\n' << "total time: " << T_end << '\n'<<endl;

int n_step=grids.size();
int n_time=T_end/k_time;

writefile<<"grid points "<<'\n';

for (int j = n_step - 1; j >= 0; j--) {
	for (int i = 0; i < n_step; i++) {
		writefile << grids[i] << " ";
		//cout << "grids= "<<grids[i] << ' ';
	}
	writefile << '\n';
}

writefile<<'\n';
writefile<<"Time 0"<<'\n';
for (int j = n_step - 1; j >= 0; j--) {
	for (int i = 0; i < n_step; i++) {
		writefile << u_ini(i,j) << " ";
	}
  writefile <<'\n';
}
writefile<<'\n';
writefile <<'\n';

for(int n=0;n<n_time;n++){
	int m = 0;
    writefile<<"Time "<<double(n+1)*k_time<<'\n';
	for (int i = 0; i < n_step; i++) {
		for (int j = 0; j < n_step; j++) {
			writefile << u(n, m) << " ";
			m++;
		}
		writefile << '\n';
	}
	writefile << '\n';
}
writefile.close();


}



void print_output_3D(string filename,string solvername,MatrixXd grid_3d, MatrixXd u_ini,MatrixXd u,double h_space,double k_time,double T_end){
/*
save the result to a file
*/
ofstream writefile;
string fullname;
fullname=filename+"_"+solvername+".dat";
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
