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
void initial_boundary_2D(MatrixXd& u_ini, vector<double> grid) {
	int ngrids = grid.size();
	for (int i = 0; i < ngrids; i++)
		for (int j = 0; j < ngrids; j++)
			u_ini(i, j) = 1 + sin(grid[i] * grid[j]) + sin(10 * grid[i] * grid[j]);
}
//2D boundary conditions
void boundary_1d_1_2D(MatrixXd& u_ini, vector<double> grid, double delta = 0.0) {
	int ngrids = grid.size();
	for (int i = 0; i < ngrids; i++)
		for (int j = 0; j < ngrids; j++)
			u_ini(i, j) = 1 + sin(grid[i] * grid[j]) + sin(10 * grid[i] * grid[j]) + delta;
}



//
void solver_back_euler_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T) {

	int n_step = grid.size();
	int n_time = T / k;
	int m, num_row;
	double sigma = k / (h*h);
	MatrixXd Q_factor = MatrixXd::Zero(n_step*n_step, n_step*n_step);
	MatrixXd u_t(n_step*n_step, 1), u_tau(n_step*n_step, 1);

	// set the initial value of u(x)
	m = 0;
	for (int i = 0; i < n_step; i++) {
		for (int j = 0; j < n_step; j++) {
			u_t(m, 0) = u_ini(i,j);
			m++;
		}
	}
	//  cout<<"the u_ini is "<<'\n'<<u_t<<endl;
	// use the numerical scheme for the heat equation up to time T
//	cout << "k,h" << k << " " << h << endl;
//	cout << "step,time" << n_step << " " << n_time << endl;
		// generate the numerical operator matrix Q_factor
		for (int i = 0; i < n_step; i++) {
			for (int j = 0; j < n_step; j++) {
				if (i == 0 && j == 0) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = - sigma;
					Q_factor(num_row, n_step - 1) = -sigma;
					Q_factor(num_row, n_step) = -sigma;
					Q_factor(num_row, n_step*(n_step - 1)) = -sigma;
				}
				else if (i == n_step - 1 && j == 0) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, 0) = -sigma;
					Q_factor(num_row, num_row + n_step) = -sigma;
					Q_factor(num_row, num_row + n_step*(n_step - 1)) = -sigma;
				}
				else if (i == 0 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = -sigma;
					Q_factor(num_row, n_step -1 + n_step *(n_step-1)) = -sigma;
					Q_factor(num_row, 0) = -sigma;
					Q_factor(num_row, n_step*(n_step-2)) = -sigma;
				}
				else if (i == n_step - 1 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor(num_row, n_step*(n_step-1)) = -sigma;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, n_step - 1) = -sigma;
					Q_factor(num_row, (n_step -1) + n_step*(n_step - 2)) = -sigma;
				}
				else if (j == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row + n_step * (n_step - 1)) = -sigma;
					}
				}
				else if (j == n_step - 1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
						Q_factor(num_row, k) = -sigma;
					}
				}
				else if (i == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor(num_row, num_row + (n_step - 1)) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
					}
				}
				else if (i == n_step -1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor(num_row, num_row - (n_step - 1)) = -sigma;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
					}
				}
				else if(i > 0 && i < n_step -1 && j > 0 && j < n_step -1){
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = -sigma;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, num_row + n_step) = -sigma;
					Q_factor(num_row, num_row - n_step) = -sigma;
				}
				num_row = i + j*n_step;
				Q_factor(num_row, num_row) = 1.0 + 4.0*sigma;
			}
		}
	// solve the equation Q_factor*u_tau=u_t
	// use the linear solve in Eigen class
//	ColPivHouseholderQR< MatrixXd> dec(Q_factor);
	for (int n = 0; n<n_time; n++) {
//		u_tau = dec.solve(u_t);

        u_tau= Q_factor.lu().solve(u_t);
		// store the result in u
		m = 0;
		for (int i = 0; i < n_step; i++) {
			for (int j = 0; j < n_step; j++) {
				u(n, m) = u_tau(m);
				m++;
			}
		}
		// prepare for the next iteration
		u_t = u_tau;
	}
}

void solver_euler_2D(MatrixXd& u, MatrixXd u_ini, vector<double> grid, double k, double h, double T) {

	int n_step = grid.size(), m;
	int n_time = T / k;
	//cout << "n_step= " << n_step << ' ' << "n_time= " << n_time << endl;
	//MatrixXd Q_factor( n_step, n_step);
	MatrixXd u_t(n_step, n_step), u_tau(n_step, n_step);
	//cout << "size of u is " << u.rows() << ' ' << u.cols() << endl;
	// set the initial value of u(x)
	u_t = u_ini;
	//for (int i = 0; i<n_step; i++) {
		//u_t(i, 0) = u_ini[i];
	//}

	// use the numerical scheme for the heat equation up to time T
	for (int n = 0; n < n_time; n++)
	{
		//cout << '\n' << "time: " << n << '\n';

		// using euler method to update u_tau
		for (int i = 0; i < n_step; i++)
		{
			for (int j = 0; j < n_step; j++) {
				if (i == 0 && j == 0) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(n_step - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, n_step - 1));
				}
				else if (i == n_step - 1 && j == n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(0, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, 0) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
				else if (i == 0 && j == n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(n_step - 1, j) + u_t(i, 0) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
				else if (i == n_step - 1 && j == 0) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(0, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, n_step - 1));
				}
				else if (i == 0 && j > 0 && j < n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(n_step - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
				else if (i == n_step - 1 && j > 0 && j < n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(0, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
				else if (i > 0 && i < n_step - 1 && j == 0) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, n_step - 1));
				}
				else if (i > 0 && i < n_step - 1 && j == n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, 0) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
				else if (i > 0 && i < n_step - 1 && j>0 && j < n_step - 1) {
					u_tau(i, j) = u_t(i, j) + (k / (h*h))*(u_t(i + 1, j) - 2 * u_t(i, j) + u_t(i - 1, j) + u_t(i, j + 1) - 2 * u_t(i, j) + u_t(i, j - 1));
				}
			}
		}
		// store the result in the big matrix u
		m = 0;
		//cout << '\n' << "time: " << n << '\n';
		for (int p = 0; p < n_step; p++)
		{
			//cout << '\n'<<"row = " << p << '\n';
			for (int q = 0; q < n_step; q++)
			{
				u(n, m) = u_tau(p, q);
				m++;
				//cout << u_tau(p,q) << ' ';
			}
		}
		// prepare for the next iteration
		u_t = u_tau;
	}
}


void solver_crank_nicolson_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T){

	int n_step = grid.size();
	int n_time = T / k;
	int m, num_row;
	double sigma = k / (h*h)/2.0;
	MatrixXd Q_factor = MatrixXd::Zero(n_step*n_step, n_step*n_step);
	MatrixXd Q_factor_B = MatrixXd::Zero(n_step*n_step, n_step*n_step);
	MatrixXd u_t(n_step*n_step, 1), u_tau(n_step*n_step, 1);

	// set the initial value of u(x)
	m = 0;
	for (int i = 0; i < n_step; i++) {
		for (int j = 0; j < n_step; j++) {
			u_t(m, 0) = u_ini(i, j);
			m++;
		}
	}
	//  cout<<"the u_ini is "<<'\n'<<u_t<<endl;
	// use the numerical scheme for the heat equation up to time T
	cout << "k,h" << k << " " << h << endl;
	cout << "step,time" << n_step << " " << n_time << endl;
		// generate the numerical operator matrix Q_factor
		for (int i = 0; i < n_step; i++) {
			for (int j = 0; j < n_step; j++) {
				if (i == 0 && j == 0) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = -sigma;
					Q_factor(num_row, n_step - 1) = -sigma;
					Q_factor(num_row, n_step) = -sigma;
					Q_factor(num_row, n_step*(n_step - 1)) = -sigma;
				}
				else if (i == n_step - 1 && j == 0) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, 0) = -sigma;
					Q_factor(num_row, num_row + n_step) = -sigma;
					Q_factor(num_row, num_row + n_step*(n_step - 1)) = -sigma;
				}
				else if (i == 0 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = -sigma;
					Q_factor(num_row, n_step - 1 + n_step *(n_step - 1)) = -sigma;
					Q_factor(num_row, 0) = -sigma;
					Q_factor(num_row, n_step*(n_step - 2)) = -sigma;
				}
				else if (i == n_step - 1 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor(num_row, n_step*(n_step - 1)) = -sigma;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, n_step - 1) = -sigma;
					Q_factor(num_row, (n_step - 1) + n_step*(n_step - 2)) = -sigma;
				}
				else if (j == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row + n_step * (n_step - 1)) = -sigma;
					}
				}
				else if (j == n_step - 1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
						Q_factor(num_row, k) = -sigma;
					}
				}
				else if (i == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor(num_row, num_row + (n_step - 1)) = -sigma;
						Q_factor(num_row, num_row + 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
					}
				}
				else if (i == n_step - 1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor(num_row, num_row - (n_step - 1)) = -sigma;
						Q_factor(num_row, num_row - 1) = -sigma;
						Q_factor(num_row, num_row + n_step) = -sigma;
						Q_factor(num_row, num_row - n_step) = -sigma;
					}
				}
				else if (i > 0 && i < n_step - 1 && j > 0 && j < n_step - 1) {
					num_row = i + j*n_step;
					Q_factor(num_row, num_row + 1) = -sigma;
					Q_factor(num_row, num_row - 1) = -sigma;
					Q_factor(num_row, num_row + n_step) = -sigma;
					Q_factor(num_row, num_row - n_step) = -sigma;
				}
				num_row = i + j*n_step;
				Q_factor(num_row, num_row) = 1.0 + 4.0*sigma;
			}
		}

		sigma = -1.0*sigma;
			// generate the numerical operator matrix Q_factor
		for (int i = 0; i < n_step; i++) {
			for (int j = 0; j < n_step; j++) {
				if (i == 0 && j == 0) {
					num_row = i + j*n_step;
					Q_factor_B(num_row, num_row + 1) = -sigma;
					Q_factor_B(num_row, n_step - 1) = -sigma;
					Q_factor_B(num_row, n_step) = -sigma;
					Q_factor_B(num_row, n_step*(n_step - 1)) = -sigma;
				}
				else if (i == n_step - 1 && j == 0) {
					num_row = i + j*n_step;
					Q_factor_B(num_row, num_row - 1) = -sigma;
					Q_factor_B(num_row, 0) = -sigma;
					Q_factor_B(num_row, num_row + n_step) = -sigma;
					Q_factor_B(num_row, num_row + n_step*(n_step - 1)) = -sigma;
				}
				else if (i == 0 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor_B(num_row, num_row + 1) = -sigma;
					Q_factor_B(num_row, n_step - 1 + n_step *(n_step - 1)) = -sigma;
					Q_factor_B(num_row, 0) = -sigma;
					Q_factor_B(num_row, n_step*(n_step - 2)) = -sigma;
				}
				else if (i == n_step - 1 && j == n_step - 1) {
					num_row = i + j*n_step;
					Q_factor_B(num_row, n_step*(n_step - 1)) = -sigma;
					Q_factor_B(num_row, num_row - 1) = -sigma;
					Q_factor_B(num_row, n_step - 1) = -sigma;
					Q_factor_B(num_row, (n_step - 1) + n_step*(n_step - 2)) = -sigma;
				}
				else if (j == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor_B(num_row, num_row - 1) = -sigma;
						Q_factor_B(num_row, num_row + 1) = -sigma;
						Q_factor_B(num_row, num_row + n_step) = -sigma;
						Q_factor_B(num_row, num_row + n_step * (n_step - 1)) = -sigma;
					}
				}
				else if (j == n_step - 1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = k + j*n_step;
						Q_factor_B(num_row, num_row - 1) = -sigma;
						Q_factor_B(num_row, num_row + 1) = -sigma;
						Q_factor_B(num_row, num_row - n_step) = -sigma;
						Q_factor_B(num_row, k) = -sigma;
					}
				}
				else if (i == 0) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor_B(num_row, num_row + (n_step - 1)) = -sigma;
						Q_factor_B(num_row, num_row + 1) = -sigma;
						Q_factor_B(num_row, num_row + n_step) = -sigma;
						Q_factor_B(num_row, num_row - n_step) = -sigma;
					}
				}
				else if (i == n_step - 1) {
					for (int k = 1; k < n_step - 1; k++) {
						num_row = i + k*n_step;
						Q_factor_B(num_row, num_row - (n_step - 1)) = -sigma;
						Q_factor_B(num_row, num_row - 1) = -sigma;
						Q_factor_B(num_row, num_row + n_step) = -sigma;
						Q_factor_B(num_row, num_row - n_step) = -sigma;
					}
				}
				else if (i > 0 && i < n_step - 1 && j > 0 && j < n_step - 1) {
					num_row = i + j*n_step;
					Q_factor_B(num_row, num_row + 1) = -sigma;
					Q_factor_B(num_row, num_row - 1) = -sigma;
					Q_factor_B(num_row, num_row + n_step) = -sigma;
					Q_factor_B(num_row, num_row - n_step) = -sigma;
				}
				num_row = i + j*n_step;
				Q_factor_B(num_row, num_row) = 1.0 + 4.0*sigma;
			}
		}


			// solve the equation Q_factor*u_tau=u_t
			// use the linear solve in Eigen class
			ColPivHouseholderQR< MatrixXd> dec(Q_factor);
			for (int n = 0; n < n_time; n++) {
				u_tau = dec.solve(Q_factor_B*u_t);
				//      cout<<"the new u_tau is "<<'\n'<<u_tau<<endl;

				// store the result in u
				m = 0;
				for (int i = 0; i < n_step; i++)
				{
					for (int j = 0; j < n_step; j++) {
						u(n, m) = u_tau(m);
						m++;
					}
				}
				// prepare for the next iteration
				u_t = u_tau;
			}
	//cout << "size of the Q_factor: " << Q_factor.rows() << ' ' << "x" << Q_factor.cols() << endl;
	//cout << "sigma: " << sigma << endl;
	//for (int i = 0; i < n_step*n_step; i++) {
	//for (int j = 0; j < n_step*n_step; j++) {
	//cout << Q_factor(i, j) << ' ';
	//}
	//cout << '\n';
	//}
}



void solver_DuFort_Frankel_2D(MatrixXd &u, MatrixXd u_ini, vector<double> grid, double k, double h, double T) {


	int n_step = grid.size(), m;
	int n_time = T / k;
	double sigma = k / (h*h);
	//cout << "n_step= " << n_step << ' ' << "n_time= " << n_time << endl;
	//MatrixXd Q_factor( n_step, n_step);
	MatrixXd u_t(n_step, n_step), u_tau(n_step, n_step), u_pre(n_step, n_step);
	//cout << "size of u is " << u.rows() << ' ' << u.cols() << endl;
	// set the initial value of u(x)
	u_t = u_ini;
	u_pre = u_ini;
	//for (int i = 0; i<n_step; i++) {
		//u_t(i, 0) = u_ini[i];
		//u_pre(i, 0) = u_ini[i];
	//}

	// use the numerical scheme for the heat equation up to time T
	for (int n = 0; n < n_time; n++)
	{
		// using DuFort_Frankel to update u_tau
		for (int i = 0; i < n_step; i++)
		{
			for (int j = 0; j < n_step; j++) {
				if (i ==0 && j == 0) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1,j) + u_t(n_step - 1,j) + u_t(i,j + 1) + u_t(i,n_step -1)) + (1.0 - 4.0*sigma)*u_pre(i,j));
				}
				else if (i == n_step-1 && j == n_step - 1) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(0, j) + u_t(i - 1, j) + u_t(i, 0) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if (i == 0 && j == n_step - 1) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1, j) + u_t(n_step - 1, j) + u_t(i, 0) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if (i == n_step - 1 && j == 0) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(0, j) + u_t(i - 1, j) + u_t(i, j + 1) + u_t(i, n_step - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if (i == 0 && j > 0 && j < n_step - 1) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1, j) + u_t(n_step - 1, j) + u_t(i, j + 1) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if (i == n_step - 1 && j > 0 && j < n_step - 1) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(0, j) + u_t(i - 1, j) + u_t(i, j + 1) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if (i > 0 && i < n_step - 1 && j == 0) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1, j) + u_t(i - 1, j) + u_t(i, j + 1) + u_t(i, n_step - 1)) + (1.0 - 4.0*sigma) *u_pre(i, j));
				}
				else if (i > 0 && i < n_step - 1 && j == n_step - 1) {
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1, j) + u_t(i - 1, j) + u_t(i, 0) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
				else if(i > 0 && i < n_step - 1 && j>0 && j < n_step - 1)
				{
					u_tau(i, j) = (1.0 / (1.0 + 4.0*sigma))*(2.0*sigma*(u_t(i + 1, j) + u_t(i - 1, j) + u_t(i, j + 1) + u_t(i, j - 1)) + (1.0 - 4.0*sigma) * u_pre(i, j));
				}
			}
		}
		// store the result in the big matrix u
		m = 0;
		//cout << '\n' << "time: " << n << '\n';
		for (int p = 0; p < n_step; p++)
		{
			//cout << '\n'<<"row = " << p << '\n';
			for (int q = 0; q < n_step; q++)
			{
				u(n, m) = u_tau(p, q);
				m++;
				//cout << u_tau(p,q) << ' ';
			}
		}
		// prepare for the next iteration
		u_pre = u_t;
		u_t = u_tau;
	}

}


//2D FEM algorithm
//************************************************************//
//local stiffness matrix
void calculate_ele_stiff_2d(MatrixXd &B_ele,MatrixXd &A_ele,MatrixXd x){
// use linear quadratic element for 2d case

    //     MatrixXd B_ele=MatrixXd::Zero( 4, 4);//the element mass matrix
    //     MatrixXd A_ele=MatrixXd::Zero( 4, 4);// the element stiffness matrix
//define guass integration points
         MatrixXd xi=MatrixXd::Zero( 2, 4);
         double cn= 0.5773502691896260;

         xi(0, 0) = -cn;
         xi(0, 1) = cn;
         xi(0, 2) = cn;
         xi(0, 3) = -cn;
         xi(1, 0) = -cn;
         xi(1, 1) = -cn;
         xi(1, 2) = cn;
         xi(1, 3) = cn;

//loop over the gauss integration points
        for (int i=0;i<4;i++){
          // calculate shape function and derivatives of shape function

                   double g1,g2,h1,h2,dg1,dg2,dh1,dh2;
                   MatrixXd f=MatrixXd::Zero(4,1),df=MatrixXd::Zero(4,2);

                          g1 = 0.5*(1.0 - xi(0,i));
                          g2 = 0.5*(1.0+ xi(0,i));
                          h1 = 0.5*(1.0- xi(1,i));
                          h2 = 0.5*(1.0 + xi(1,i));
                          f(0) = g1*h1;
                          f(1) = g2*h1;
                          f(2) = g2*h2;
                          f(3) = g1*h2;
                          dg1 = -0.5;
                          dg2 = 0.5;
                          dh1 = -0.5;
                          dh2 = 0.5;
                          df(0, 0) = dg1*h1;
                          df(1, 0) = dg2*h1;
                          df(2, 0) = dg2*h2;
                          df(3, 0) = dg1*h2;
                          df(0, 1) = g1*dh1;
                          df(1, 1) = g2*dh1;
                          df(2, 1) = g2*dh2;
                          df(3, 1) = g1*dh2;
        //calculate the jacobi matrix (dxdxi) and determinate of jacobi matrix
              double jacobi;
              MatrixXd dxdxi=MatrixXd::Zero(2,2),dxidx=MatrixXd::Zero(2,2);
              dxdxi=x*df;
              dxidx=dxdxi.inverse();
              jacobi=dxdxi.determinant();

        // caclulate dNdx
         MatrixXd dNdx=MatrixXd::Zero(4,2);
         dNdx=df*dxidx;

        //calculate the stiffness matrix and mass matrix for current integration point
         for (int j=0;j<4;j++){
           for (int k=0;k<4;k++){
               B_ele(j,k)=B_ele(j,k)+f(j)*f(k)*jacobi;
               A_ele(j,k)=A_ele(j,k)+dNdx(j,0)*dNdx(k,0)+dNdx(j,1)*dNdx(k,1);

           }
         }

        }

}



 void solver_FEM_2D(MatrixXd &u,MatrixXd u_ini, MatrixXd grid, double k, double h, double T){

   int nx,ny,node_all;
   nx=u_ini.rows();
   ny=u_ini.cols();
   node_all=nx*ny;
   // for 2-D case create the element connectivity
   MatrixXd element_set=MatrixXd::Zero((nx-1)*(ny-1),4);
   int ele_all=0;

   for (int i=0;i<(nx-1);i++){
     for(int j=0;j<(ny-1);j++){
       element_set(ele_all,0)=i+j*(nx);
       element_set(ele_all,1)=i+j*(nx)+1;
       element_set(ele_all,2)=i+j*(nx)+1+nx;
       element_set(ele_all,3)=i+j*(nx)+nx;
       ele_all=ele_all+1;
     }
   }

// check the element is assembled correctly
   if (ele_all != (nx-1)*(ny-1) ){
     cout<<"there is something wrong with element connectivity!"<<endl;
   }

 //create a local node_all*2 matrix contains all node coordinates
   MatrixXd grid_coord=MatrixXd::Zero(node_all,2);
   for (int i=0;i<(nx);i++){
     for(int j=0;j<(ny);j++){
        grid_coord(i+j*nx,0)=i*h;
        grid_coord(i+j*nx,1)=j*h;
     }
   }

  //read the initial boundary into the form could be used in FEM solver

 	MatrixXd u_ini_fem(node_all,1);

 	for (int i=0;i<(nx);i++){
	 	for(int j=0;j<(ny);j++){
				u_ini_fem(i+j*nx)=u_ini(i,j);
	 	}
 	}

   //assemble the local element to global coordinate
   //*************************************************//
   //create the golbal mass matrix and stiffness matrix
   MatrixXd B=MatrixXd::Zero( node_all, node_all), A=MatrixXd::Zero(node_all, node_all);
   // create the local mass matrix and stiffness matrix
   MatrixXd B_ele=MatrixXd::Zero( 4, 4),A_ele=MatrixXd::Zero( 4, 4);//the element mass matrix and stiffness matrix
   MatrixXd x=MatrixXd::Zero( 2, 4);//the coordinates of element points
   int global_x,global_y;

   for (int i=0;i<(ele_all);i++){

      //get the coordinates for nodes in the element
       for(int j=0;j<4;j++){
         x(0,j)=grid_coord(element_set(i,j),0);
         x(1,j)=grid_coord(element_set(i,j),1);
       }

			//  cout<<"block1"<<endl;
       //get local stiffness
       calculate_ele_stiff_2d(B_ele,A_ele,x);
    //   cout<<"block2"<<endl;
       //assmble the local stiffness matrix to global coordinates
       for (int j=0;j<4;j++){
         for(int k=0;k<4;k++){
            global_x=element_set(i,j);
            global_y=element_set(i,k);
            B(global_x,global_y)=B(global_x,global_y)+B_ele(j,k);
            A(global_x,global_y)=A(global_x,global_y)+A_ele(j,k);

         }
       }
     }

//decompose of the stiffness and mass matrix
    //        ColPivHouseholderQR< MatrixXd> dec(B+k*A);
// the end of finite element space discretization
//*************************************************************************//

   // solve the heat equation with back ward euler in time integration

       int n_time;
       n_time=T/k;
       MatrixXd u_t(node_all,1),u_tau(node_all,1);

       u_t=u_ini_fem;
			 ColPivHouseholderQR< MatrixXd> dec(B+k*A);

       for(int i=0;i<n_time;i++){

         // solve the equation (B+k*A)*u_tau=B*u_t
           // use the linear solve in Eigen class
           u_tau=dec.solve(B*u_t);


       // store the result in the big matrix u
         for (int j=0;j< node_all;j++){
             u(i,j)=u_tau(j);
         }
       // prepare for the next iteration
       u_t=u_tau;

       }

//end of time integration
//*******************************************************************************//
 }
