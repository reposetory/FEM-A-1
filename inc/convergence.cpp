#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <algorithm.h>

using namespace Eigen;
using namespace std;

// study the convergence stability and accuracy for the four basic algorithm
void convergence_1d(string solvername,string boundaryname,double delta=10e-7,vector<double> &u_ini,vector<double>& grid,double& k,double& h,double& T){

  int ntime;
  int ngrids;
  ngrids=grid.size();
  ntime=T/k;
  MatrixXd u_original_solution(ntime,ngrids);

  //use different solver for the original solutio
    if (solvername=="BE" ) {
        solver_back_euler_1D(u_original_solution,u_ini,grid,k,h,T) ;
      }
    else if (solvername=="E" ){
        solver_euler_1D(u_original_solution,u_ini,grid,k,h,T) ;
    }
    else if (solvername=="CN" ){
        solver_crank_nicolson_1D(u_original_solution,u_ini,grid,k,h,T);
    }
    else if (solvername=="DF" ){
        solver_DuFort_Frankel_1D(u_original_solution,u_ini,grid,k,h,T);
    }
    else{
      cout << "No solver for the input" << endl;
    }

// stability study, give a small disturbulation delta on initial condition

  MatrixXd u_delta_plus(ntime,ngrids),u_delta_minus(ntime,ngrids);
  vector<double> u_ini_plus(ngrids,0),u_ini_minus(ngrids,0);

  //update the initial condtion with disturb
  boundary_1d_1(u_ini_plus,grid,delta);
  boundary_1d_1(u_ini_minus,grid,-delta);

  // solver the new problem
  //use different solver for the original solutio
    if (solvername=="BE" ) {
        solver_back_euler_1D(u_delta_plus,u_ini_plus,grid,k,h,T) ;
        solver_back_euler_1D(u_delta_minus,u_ini_minus,grid,k,h,T) ;
      }
    else if (solvername=="E" ){
        solver_euler_1D(u_delta_plus,u_ini_plus,grid,k,h,T) ;
        solver_euler_1D(u_delta_minus,u_ini_minus,grid,k,h,T) ;
    }
    else if (solvername=="CN" ){
        solver_crank_nicolson_1D(u_delta_plus,u_ini_plus,grid,k,h,T);
        solver_crank_nicolson_1D(u_delta_minus,u_ini_minus,grid,k,h,T);

    }
    else if (solvername=="DF" ){
        solver_DuFort_Frankel_1D(u_delta_plus,u_ini_plus,grid,k,h,T);
        solver_DuFort_Frankel_1D(u_delta_minus,u_ini_minus,grid,k,h,T);
    }
    else{
      cout << "No solver for the input" << endl;
    }
  // save the data for different cases



}
