#include <iostream>
#include <string>
#include <algorithm.h> //This is the library that contains the implementation of different finite element algorithm
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

void read_input(string filename,vector<double>&  grids,double& h_space,double& k_time,double& T_end);

void print_output(string filename,vector<double>& grids,vector<double>& u_ini,MatrixXd& u,double& h_space,double& k_time,double& T_end); 

int main(int argc, char* argv[]) {
 
/*
 get the input file name
 */

    string filename;
    if (argc<2){
        cout<<"please enter the input file name"<<endl;
        cin>>filename;
    }
    else{
        filename=argv[1];
    }
    cout<<"the input file name is "<<filename<<endl;
    
    
    
/*
 read the mesh information
 from the input file
 
 */
// variables that define a numerical scheme
// grid is the space discretization, k is the space step
// h is the time step,T is the total time    
  vector<double> grid;
  double k,h,T; 
   
  read_input(filename,grid,h,k,T);

 cout<<"k,h,T are "<<k<<" "<<h<<" "<<T<<endl; 
 cout<<"the total number of grids are "<<grid.size()<<endl;  

 
/*
 solve the heat equation ut=uxx
 */
    
//for one-dimensional demo; assume 2pi periodic,
//initial condition is u(,0)=sin(x)+sin(10x)
  int ngrids;
  ngrids=grid.size();
  vector<double> u_ini(ngrids,0);
  initial_boundary(u_ini,grid); 

// solve the 1D heat equation with the given parameters
  
  int ntime;
  ntime=T/k; 
  MatrixXd u(ntime,ngrids);
  
 solver_back_euler(u,u_ini,grid,k,h,T) ;
 
    
/*
 save the solution to a data file
 */
    print_output(filename,grid,u_ini,u,h,k,T);

    
    
    return 0;

}
