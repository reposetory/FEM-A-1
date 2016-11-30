#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;

//boundary class
// generate a simple initiial boundary condition u(,0)=sin(x)+sin(10x)
void initial_boundary(vector<double>& u_ini,vector<double>& grid){

    int ngrids=grid.size();
    for (int i=0;i<ngrids;i++){
        u_ini[i]=sin(grid[i])+sin(110*grid[i]);
 //       cout<<u_ini[i]<<endl;
    }


}

//a sample boundary condtion with a disturbulation u(,0)=sin(x)+sin(10x)+delta
void boundary_1d_1(vector<double>& u_ini,vector<double>& grid,double delta=0.0){
  int ngrids=grid.size();
  for (int i=0;i<ngrids;i++){
      u_ini[i]=sin(grid[i])+sin(110*grid[i])+delta;

  }
}

//backward euler ALGORITHM
void solver_back_euler_1D(MatrixXd& u,vector<double>& u_ini,vector<double>& grid,double& k,double& h,double& T) {

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


//==============================================================================//
// euler ALGORITHM
void solver_euler_1D(MatrixXd& u,vector<double>& u_ini,vector<double>& grid,double& k,double& h,double& T) {

  int n_step=grid.size();
  int n_time=T/k;
  //MatrixXd Q_factor( n_step, n_step);
  MatrixXd u_t( n_step,1),u_tau( n_step,1);

// set the initial value of u(x)
  for(int i=0;i<n_step;i++){
      u_t(i,0)=u_ini[i];
  }

// use the numerical scheme for the heat equation up to time T
  for(int i=0;i<n_time;i++){

// using euler method to update u_tau
      for (int j=0;j<n_step;j++){
        if(j==0){
          u_tau(j)=u_t(j)+(k/(h*h))*(u_t(j+1)-2*u_t(j)+u_t(n_step-1));
        }
        else if(j==n_step-1){
          u_tau(j)=u_t(j)+(k/(h*h))*(u_t(0)-2*u_t(j)+u_t(j-1));
        }
        else{
          u_tau(j)=u_t(j)+(k/(h*h))*(u_t(j+1)-2*u_t(j)+u_t(j-1));
        }
      }


      // store the result in the big matrix u
      for (int j=0;j< n_step;j++){
          u(i,j)=u_tau(j);
      }
      // prepare for the next iteration
      u_t=u_tau;

  }

}


//============================================================//

void solver_crank_nicolson_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T){
  int n_step=grid.size();
  int n_time=T/k;
  MatrixXd Q_factor_left( n_step, n_step),Q_factor_right(n_step, n_step);
  MatrixXd u_t( n_step,1),u_tau( n_step,1);

// set the initial value of u(x)
  for(int i=0;i<n_step;i++){
      u_t(i,0)=u_ini[i];
  }

// use the numerical scheme for the heat equation up to time T
  for(int i=0;i<n_time;i++){

      // generate the numerical operator matrix Q_factor_left
      for(int j=0;j<n_step;j++){
           Q_factor_left(j,j)=1.0+k/(h*h);
           if(j==0){
               Q_factor_left(j,j+1)=-0.5*k/(h*h);
               Q_factor_left(j,n_step-1)=-0.5*k/(h*h);
           }
           else if(j==n_step-1){
               Q_factor_left(j,j-1)=-0.5*k/(h*h);
               Q_factor_left(j,0)=-0.5*k/(h*h);
           }
           else{
               Q_factor_left(j,j+1)=-0.5*k/(h*h);
               Q_factor_left(j,j-1)=-0.5*k/(h*h);
           }
      }

      // generate the numerical operator matrix Q_factor_right
      for(int j=0;j<n_step;j++){
           Q_factor_right (j,j)=1.0-k/(h*h);
           if(j==0){
               Q_factor_right(j,j+1)=0.5*k/(h*h);
               Q_factor_right(j,n_step-1)=0.5*k/(h*h);
           }
           else if(j==n_step-1){
               Q_factor_right(j,j-1)=0.5*k/(h*h);
               Q_factor_right(j,0)=0.5*k/(h*h);
           }
           else{
               Q_factor_right(j,j+1)=0.5*k/(h*h);
               Q_factor_right(j,j-1)=0.5*k/(h*h);
           }
      }

// solve the equation Q_factor_left*u_tau=Q_factor_right*u_t
  // use the linear solve in Eigen class
      ColPivHouseholderQR< MatrixXd> dec(Q_factor_left);
      u_tau=dec.solve(Q_factor_right*u_t);


      // store the result in u
      for (int j=0;j< n_step;j++){
          u(i,j)=u_tau(j);
      }
      // prepare for the next iteration
      u_t=u_tau;

  }

}


void solver_DuFort_Frankel_1D(MatrixXd &u,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T){


    int n_step=grid.size();
    int n_time=T/k;
    double sigma=k/(h*h);
    //MatrixXd Q_factor( n_step, n_step);
    MatrixXd u_t(n_step,1),u_tau( n_step,1),u_pre( n_step,1);

  // set the initial value of u_n(x) and u_n-1(x)
    for(int i=0;i<n_step;i++){
        u_t(i,0)=u_ini[i];
        u_pre(i,0)=u_ini[i];
    }

  // use the numerical scheme for the heat equation up to time T
    for(int i=0;i<n_time;i++){

  // using DuFort_Frankel to update u_tau
        for (int j=0;j<n_step;j++){
          if(j==0){
            u_tau(j)=(1.0/(1.0+2.0*sigma))*(2.0*sigma*(u_t(j+1)+u_t(n_step-1))+(1.0-2.0*sigma)*u_pre(j));
          }
          else if(j==n_step-1){
            u_tau(j)=(1.0/(1.0+2.0*sigma))*(2.0*sigma*(u_t(0)+u_t(j-1))+(1.0-2.0*sigma)*u_pre(j));
          }
          else{
            u_tau(j)=(1.0/(1.0+2.0*sigma))*(2.0*sigma*(u_t(j+1)+u_t(j-1))+(1.0-2.0*sigma)*u_pre(j));
          }
        }

        // store the result in the big matrix u
        for (int j=0;j< n_step;j++){
            u(i,j)=u_tau(j);
        }
        // prepare for the next iteration
        u_pre=u_t;
        u_t=u_tau;

    }

}
