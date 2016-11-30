#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;

// generate a simple initiial boundary condition u(,0)=sin(x)+sin(10x)
void initial_boundary(vector<double>& u_ini,vector<double>& grid){
    
    int ngrids=grid.size();
    for (int i=0;i<ngrids;i++){
        u_ini[i]=sin(grid[i])+sin(110*grid[i]);
 //       cout<<u_ini[i]<<endl;
    }
    
    
}


void solver_back_euler(MatrixXd& u,vector<double>& u_ini,vector<double>& grid,double& k,double& h,double& T) {
    
   int n_step=grid.size();
   int n_time=T/k;
   MatrixXd Q_factor( n_step, n_step);
   MatrixXd u_t( n_step,1),u_tau( n_step,1);
   
// set the initial value of u(x)
   for(int i=0;i<n_step;i++){
       u_t(i,0)=u_ini[i];
   }
 //  cout<<"the u_ini is "<<'\n'<<u_t<<endl;
// use the numerical scheme for the heat equation up to time T
   for(int i=0;i<n_time;i++){
       
       // generate the numerical operator matrix Q_factor
       for(int j=0;j<n_step;j++){
            Q_factor(j,j)=1.0+2.0*k/(h*h);
            if(j==0){
                Q_factor(j,j+1)=-k/(h*h);
                Q_factor(j,n_step-1)=-k/(h*h);
            }
            else if(j==n_step-1){
                Q_factor(j,j-1)=-k/(h*h);
                Q_factor(j,0)=-k/(h*h);
            }
            else{
                Q_factor(j,j+1)=-k/(h*h);
                Q_factor(j,j-1)=-k/(h*h);
            }
       }
       
 // solve the equation Q_factor*u_tau=u_t
   // use the linear solve in Eigen class
       ColPivHouseholderQR< MatrixXd> dec(Q_factor);
       u_tau=dec.solve(u_t);
 //      cout<<"the new u_tau is "<<'\n'<<u_tau<<endl;
       
       // store the result in u
       for (int j=0;j< n_step;j++){
           u(i,j)=u_tau(j);
       }
       // prepare for the next iteration
       u_t=u_tau;
       
   }
    
    
    
}