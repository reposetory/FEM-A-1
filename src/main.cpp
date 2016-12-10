#include <iostream>
#include <string>
#include <algorithm.h> //This is the library that contains the implementation of different numerical algorithm
#include <algorithm2D.h>
#include <algorithm3D.h>
#include <vector>
#include <Eigen/Dense>
#include <convergence.h>
#include <print_result.h>
#include <read_input.h>
#include <mpi.h>

using Eigen::MatrixXd;
using namespace std;



int main(int argc, char* argv[]) {

	MPI::Init(argc,argv);
// variables that define a numerical scheme
// grid is the space discretization
// h is the time step,T is the total time,k is the space step
  string filename,solvername,inputfile;
  vector<double> grid;
  double k,h,T;
  int dimension;
  inputfile="parameters";

  read_input(argc, argv,inputfile,filename,solvername, grid,h,k,T,dimension);

  if(dimension==1){
 //solve the heat equation ut=uxx
//for one-dimensional demo; assume 2pi periodic,
//initial condition is u(,0)=sin(x)+sin(10x)
  int ngrids,ntime;
  ngrids=grid.size();
  ntime=T/k;
  vector<double> u_ini(ngrids,0);
  initial_boundary(u_ini,grid);


  MatrixXd u=MatrixXd::Zero(ntime,ngrids);
// solve the 1D heat equation with the given parameters
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
      differences_1d(argc,  argv,filename, solvername,u,u_ini,grid,k, h, T);
      string boundaryname;
      boundaryname="1d_1";
      stability_1d(argc,  argv,filename, solvername, boundaryname,u_ini,grid, k,h, T);

    }
    else if(dimension==2){
		//solve the heat equation ut=uxx of 2D
    // assume 2pi periodic,
		//initial condition is u(,0)=sin(xy)+sin(10xy)
		int ngrids, ntime;
		ngrids = grid.size();
		ntime = T / k;
		MatrixXd u_ini(ngrids, ngrids);
		initial_boundary_2D(u_ini, grid);

		MatrixXd u=MatrixXd::Zero(ntime, ngrids*ngrids);
		// solve the 1D heat equation with the given parameters
		//use different solver
		if (solvername == "E") {
			solver_euler_2D(u, u_ini, grid, k, h, T);
		}
		else if (solvername == "BE") {
			solver_back_euler_2D(u, u_ini, grid, k, h, T);
		}

		else if (solvername == "CN") {
			solver_crank_nicolson_2D(u, u_ini, grid, k, h, T);
		}

		else if (solvername == "DF") {
			solver_DuFort_Frankel_2D(u, u_ini, grid, k, h, T);
		}

		else if (solvername == "FE") {
      MatrixXd   grid_fem = MatrixXd::Zero(2,ngrids*ngrids);
			solver_FEM_2D(u, u_ini,grid_fem , k, h, T);
		}
		else {
			cout << "No solver for the input" << endl;
		}

		/*
		save the solution to a data file
		*/
		print_output_2D(filename, solvername, grid, u_ini, u, h, k, T);

		/*
		// convergence and stability
		differences_1d(filename, solvername, u, u_ini, grid, k, h, T);
		string boundaryname;
		boundaryname = "1d_1";
		convergence_1d(filename, solvername, boundaryname, u_ini, grid, k, h, T);
		*/
    }
  else if(dimension==3){

    int ngrids, ntime,node_total;
		ngrids = grid.size();
    node_total=ngrids*ngrids*ngrids;
		ntime = T / k;
		MatrixXd u_ini= MatrixXd::Zero(node_total,1);
    MatrixXd grid_3d= MatrixXd::Zero(node_total,3);
    MatrixXd u=MatrixXd::Zero(ntime, node_total);

    //apply initial boundary to 3D problem
    initial_boundary_3D(u_ini, grid_3d,grid,ngrids);
    //solver 3D with back_euler scheme
    solver_back_euler_3D(u,u_ini,grid_3d,  k,  h,  T, ngrids);



   /*
    this is only a templorary print function for testing purpose, feel free to change it

    grid_3d is a (totalnode)*3 matrix, the rows represent points, the first column is x axis (from 0 to 2pi). the second column is y axis(from 0 to 2pi), and the third is for z

    u_ini is a totalnode*1 matrix, it store the initial heat information, the node sequence is the same as grid_3d, that is the same row represent the same point

    u is a totaltime*totalnode matrix, the rows represent each time step, the columns represent the heat at each point, the node sequence is also the same as grid_3d, that is j columns
    in u represent the same node as j rows in grid_3d

    h is grid length, x y z takes the same value of h
    k is time step length
   T is the target computational time
   */
		print_output_3D(filename, solvername,grid_3d, u_ini, u, h, k, T);



  }
	  MPI::Finalize();
    return 0;

}
