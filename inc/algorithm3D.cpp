#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <print_result.h>
#include <read_input.h>

using namespace Eigen;
using namespace std;

const double PI = 3.141592653589793238463;



//boundary conditions

//2D initial condition u(x,y,0) = 1 + sin(xy)+sin(10xy);
void initial_boundary_3D(MatrixXd& u_ini,  MatrixXd& grid_3d, vector<double> grid,int ngrids) {
	double h;
	h=2*PI/(ngrids+1);
// assign a initial valure to each point in the axies
	for (int i = 0; i < ngrids; i++){
		for (int j = 0; j < ngrids; j++){
			for(int k=0;k<ngrids;k++){
				u_ini(i+j*ngrids+k*ngrids*ngrids) = 1 + sin(grid[i] * grid[j]* grid[k]) + sin(10 * grid[i] * grid[j]* grid[k]);
				grid_3d(i+j*ngrids+k*ngrids*ngrids,0)=i*h;
				grid_3d(i+j*ngrids+k*ngrids*ngrids,1)=j*h;
				grid_3d(i+j*ngrids+k*ngrids*ngrids,2)=k*h;
			}
		}

	}

}
//2D boundary conditions
void boundary_3D_1(MatrixXd& u_ini,  MatrixXd& grid_3d, vector<double> grid,int ngrids,double delta=0.0) {
	double h;
	h=2*PI/(ngrids+1);

	for (int i = 0; i < ngrids; i++){
		for (int j = 0; j < ngrids; j++){
			for(int k=0;k<ngrids;k++){
				u_ini(i+j*ngrids+k*ngrids*ngrids) = 1 + sin(grid[i] * grid[j]* grid[k]) + sin(10 * grid[i] * grid[j]* grid[k])+delta;
				grid_3d(i+j*ngrids+k*ngrids*ngrids,0)=i*h;
				grid_3d(i+j*ngrids+k*ngrids*ngrids,1)=j*h;
				grid_3d(i+j*ngrids+k*ngrids*ngrids,2)=k*h;
			}
		}

	}
}




void solver_back_euler_3D(MatrixXd &u, MatrixXd u_ini,MatrixXd grid_3d, double k, double h, double T,int ngrid) {

	int n_time = T / k;
	double sigma = k / (h*h);
	MatrixXd Q_factor = MatrixXd::Zero(ngrid*ngrid*ngrid, ngrid*ngrid*ngrid);
	MatrixXd u_t(ngrid*ngrid*ngrid, 1), u_tau(ngrid*ngrid*ngrid, 1);



		// generate the numerical operator matrix Q_factor
		for (int x = 0; x< ngrid; x++) {
			int x_left,x_right;
			x_left=(x-1+ngrid)%ngrid;
			x_right=(x+1+ngrid)%ngrid;

			for (int y = 0; y< ngrid; y++){
				int y_left,y_right;
				y_left=(y-1+ngrid)%ngrid;
				y_right=(y+1+ngrid)%ngrid;
				for(int z=0; z< ngrid; z++){
					int z_left,z_right;
					z_left=(z-1+ngrid)%ngrid;
					z_right=(z+1+ngrid)%ngrid;
          Q_factor(x+y*ngrid+z*ngrid*ngrid,x+y*ngrid+z*ngrid*ngrid)=1+6*sigma;
					//difference scheme in x direction
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x_left+y*ngrid+z*ngrid*ngrid)=-sigma;
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x_right+y*ngrid+z*ngrid*ngrid)=-sigma;

					//difference scheme in y direction
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x+y_left*ngrid+z*ngrid*ngrid)=-sigma;
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x+y_right*ngrid+z*ngrid*ngrid)=-sigma;

					//difference scheme in z direction
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x+y*ngrid+z_left*ngrid*ngrid)=-sigma;
					Q_factor(x+y*ngrid+z*ngrid*ngrid,x+y*ngrid+z_right*ngrid*ngrid)=-sigma;
				}
			}
	}

//assign initial value of u_t
  u_t=u_ini;
//solve the value at each time step
	for (int n = 0; n<n_time; n++) {

    u_tau= Q_factor.lu().solve(u_t);

		// store the result in u
		for (int i = 0; i < ngrid*ngrid*ngrid; i++) {
			u(n, i) = u_tau(i);
		}
		// prepare for the next iteration
		u_t = u_tau;
	}


}
