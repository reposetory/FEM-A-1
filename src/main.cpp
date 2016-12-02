#include <iostream>
#include <string>
#include <algorithm.h> //This is the library that contains the implementation of different numerical algorithm
#include <vector>
#include <Eigen/Dense>
#include <convergence.h>

using Eigen::MatrixXd;
using namespace std;

void read_input(string filename,vector<double>&  grids,double& h_space,double& k_time,double& T_end);

void print_output(string filename,string solvername,vector<double>& grids,vector<double>& u_ini,MatrixXd& u,double& h_space,double& k_time,double& T_end);

int main(int argc, char* argv[]) {

    string filename,solvername;
    //default solver is Backward Euler
    solvername="BE";
    switch (argc) {

        case 3 :    solvername = argv[2];
        case 2 :    filename=argv[1];
            break;
        case 1 :    cout<<"please enter the file name"<<endl;
                    cin>>filename;
            break;
        default :   std::cerr << "Bad number of input parameters!" << std::endl;
            return(-1);
    }
// summary of the input information
    cout<< "the outfile will be named as "<<filename<<endl;

         if(solvername=="BE" ){
          cout<< "The solver used is Backforward Euler "<<endl;
         }
         else if (solvername=="E" ){
           cout<< "The solver used is Euler "<<endl;
         }
         else if (solvername=="CN" ){
            cout<< "The solver used is Crank Nicolson"<<endl;
         }
         else if (solvername=="DF" ){
            cout<< "The solver used is DuFort Frankel"<<endl;
         }
         else if (solvername=="FE" ){
            cout<< "The solver used is FEM"<<endl;
         }
         else{
            cout << "Wrong input solver, default Backforward Euler will be used" << endl;
            solvername="BE";
         }
        cout<<"if you wish to use other solvers, use key words: "<<'\n';
        cout<<"E for Euler"<<'\n';
        cout<<"BE for Backward Euler"<<'\n';
        cout<<"CN for Crank Nicolson"<<'\n';
        cout<<"DF for DuFort Frankel "<<'\n';
        cout<<"as the third command line input.  "<<'\n';
        cout<<"The second command line input stands for filename"<<endl;
/*
 read the mesh information
 from the input file

 */
// variables that define a numerical scheme
// grid is the space discretization
// h is the time step,T is the total time,k is the space step
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


    // convergence stability and accuracy
      string boundaryname;
      boundaryname="1d_1";
      convergence_1d(filename, solvername, boundaryname,u_ini,grid, k,h, T);

      differences_1d(filename, solvername,u,u_ini,grid,k, h, T);

    return 0;

}
