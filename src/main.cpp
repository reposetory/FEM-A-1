#include <iostream>
#include <string>
#include <algorithm.h> //This is the library that contains the implementation of different numerical algorithm
#include <vector>
#include <Eigen/Dense>
#include <convergence.h>
#include <print_result.h>
#include <read_input.h>

using Eigen::MatrixXd;
using namespace std;



int main(int argc, char* argv[]) {



/*
 read the mesh information
 from the input file

 */
// variables that define a numerical scheme
// grid is the space discretization
// h is the time step,T is the total time,k is the space step
  string filename,solvername,inputfile;
  vector<double> grid;
  double k,h,T;
  int dimension;
  inputfile="parameters";


  read_input(inputfile,filename,solvername, grid,h,k,T,dimension);
  cout<<"filename and solvername is "<<filename<<" "<<solvername<<" "<<endl;
  cout<<"k,h,T are "<<k<<" "<<h<<" "<<T<<endl;
  cout<<"the total number of grids are "<<grid.size()<<endl;

  if(dimension==1){

/*
 solve the heat equation ut=uxx
 */

//for one-dimensional demo; assume 2pi periodic,
//initial condition is u(,0)=sin(x)+sin(10x)
  int ngrids,ntime;
  ngrids=grid.size();
  ntime=T/k;
  vector<double> u_ini(ngrids,0);
  initial_boundary(u_ini,grid);

// solve the 1D heat equation with the given parameters


  MatrixXd u(ntime,ngrids);


//use different solver
  if (solvername=="BE" ) {
      solver_back_euler_1D(u,u_ini,grid,k,h,T) ;
    }
  else if (solvername=="E" ){
      solver_euler_1D(u,u_ini,grid,k,h,T) ;
  }
  else if (solvername=="CN" ){
      solver_crank_nicolson_1D(u,u_ini,grid,k,h,T);
  }
  else if (solvername=="DF" ){
      solver_DuFort_Frankel_1D(u,u_ini,grid,k,h,T);
  }
  else if (solvername=="FE" ){
      solver_FEM_1D(u,u_ini,grid,k,h,T);
  }
  else{
    cout << "No solver for the input" << endl;
  }

/*
 save the solution to a data file
 */
    print_output(filename,solvername,grid,u_ini,u,h,k,T);


    // convergence and stability
      differences_1d(filename, solvername,u,u_ini,grid,k, h, T);
      string boundaryname;
      boundaryname="1d_1";
      convergence_1d(filename, solvername, boundaryname,u_ini,grid, k,h, T);
    }
    else if(dimension==2){

    }


    return 0;

}
