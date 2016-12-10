#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <algorithm.h>
#include <print_result.h>
#include <read_input.h>
#include <mpi.h>

using namespace Eigen;
using namespace std;


void differences_1d(int argc, char* argv[],string outputfilename,string solvername,MatrixXd &u,vector<double> u_ini,vector<double>  grid,double k,double h,double T){
  //output u - u_ini per point per time step for plotting to turn into a video to show if plot flattens over time
  //print out yes/no
  //MPI::Init(argc,argv);
  int num_procs =MPI::COMM_WORLD.Get_size();
  int rank =MPI::COMM_WORLD.Get_rank();

  if(rank==0){
    cout<<"the solover for convergence study is "<<solvername<<endl;
    T=5.0;
    int ngrids,ntime;
    ngrids=grid.size();
    ntime=T/k;
    MatrixXd u_con(ntime,ngrids);
    //use different solver
      if (solvername=="BE" ) {
          solver_back_euler_1D(u_con,u_ini,grid,k,h,T) ;
        }
      else if (solvername=="E" ){
          solver_euler_1D(u_con,u_ini,grid,k,h,T) ;
      }
      else if (solvername=="CN" ){
          solver_crank_nicolson_1D(u_con,u_ini,grid,k,h,T);
      }
      else if (solvername=="DF" ){
          solver_DuFort_Frankel_1D(u_con,u_ini,grid,k,h,T);
      }
      else if (solvername=="FE" ){
          solver_FEM_1D(u_con,u_ini,grid,k,h,T);
      }
      else{
        cout << "No solver for the input" << endl;
      }


    // calculate the step difference
    MatrixXd u_diff=MatrixXd::Zero(ntime,ngrids);
    MatrixXd error=MatrixXd::Zero( ntime, 1);

    for(int i=0;i<ntime;i++){
      if(i==0){
        for(int j=0;j<ngrids;j++){
          u_diff(i,j)=u_con(i,j)-u_ini[j];
          error(i)=error(i)+u_diff(i,j)*u_diff(i,j);
        }
      }
      else{
        for(int j=0;j<ngrids;j++){
            u_diff(i,j)=u_con(i,j)-u_con(i-1,j);
            error(i)=error(i)+u_diff(i,j)*u_diff(i,j);
        }
      }
    }




    //print the difference matrix into file
    string caselabel;
    caselabel=solvername+"_difference";
    print_output( outputfilename, caselabel,grid,u_ini,  u_diff, h, k, T);

   // determine the convergence
   double com_eror=1.e-3;

   if (error(ntime-1)<com_eror){
     cout<< "The "<<solvername<<" algorithm converges"<<endl;
   }
   else{
        cout<< "The "<<solvername<<" algorithm doesn't converge"<<endl;
   }


  }

//  MPI::Finalize();
}


// study the  stability for the four basic algorithm
void stability_1d(int argc, char* argv[],string outputfilename,string solvername,string boundaryname,vector<double> u_ini,vector<double> grid,double k,double h,double T,double delta=10e-7){

  int ntime;
  int ngrids;
  ngrids=grid.size();
  ntime=T/k;
  MatrixXd u_original_solution(ntime,ngrids);
  MatrixXd u_delta_plus(ntime,ngrids),u_delta_minus(ntime,ngrids);
  vector<double> u_ini_plus(ngrids),u_ini_minus(ngrids);
  string caselabel;



//  MPI::Init(argc,argv);

  int num_procs =MPI::COMM_WORLD.Get_size();
  int rank =MPI::COMM_WORLD.Get_rank();

  if (boundaryname=="1d_1"){
    boundary_1d_1(u_ini_plus,grid,delta);
    boundary_1d_1(u_ini_minus,grid,-delta);
  }
  else{

  }


  if(rank == 0){

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
      else if (solvername=="FE" ){
          solver_FEM_1D(u_original_solution,u_ini,grid,k,h,T);
      }
      else{
        cout << "No solver for the input" << endl;
      }

      // print the result for the original solution
       caselabel=solvername+"_original";
      print_output(outputfilename, caselabel, grid,u_ini,u_original_solution, h, k, T);
      std::cout<<" from process"<<rank<<"of"<<num_procs<<'\n';

  }


  if(num_procs==2){
    if(rank==1){
      // stability study, give a small disturbulation delta on initial condition
        //update the initial condtion with disturb

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
          else if (solvername=="FE" ){
              solver_FEM_1D(u_delta_plus,u_ini_plus,grid,k,h,T);
              solver_FEM_1D(u_delta_minus,u_ini_minus,grid,k,h,T);
          }
          else{
            cout << "No solver for the input" << endl;
          }
          //print the result with ini+delta

          caselabel=solvername+"_plus";
          print_output( outputfilename, caselabel,grid,u_ini_plus, u_delta_plus, h, k, T);

          //print the result with ini-delta
          caselabel=solvername+"_minus";
          print_output( outputfilename,caselabel,grid, u_ini_minus, u_delta_minus, h,k,T);
          std::cout<<" from process"<<rank<<"of"<<num_procs<<'\n';

    }


  }
  else if(num_procs>2){

    if(rank==1){
      // solver the new problem
      //use different solver for the original solutio
        if (solvername=="BE" ) {
            solver_back_euler_1D(u_delta_plus,u_ini_plus,grid,k,h,T) ;

          }
        else if (solvername=="E" ){
            solver_euler_1D(u_delta_plus,u_ini_plus,grid,k,h,T) ;

        }
        else if (solvername=="CN" ){
            solver_crank_nicolson_1D(u_delta_plus,u_ini_plus,grid,k,h,T);

        }
        else if (solvername=="DF" ){
            solver_DuFort_Frankel_1D(u_delta_plus,u_ini_plus,grid,k,h,T);

        }
        else if (solvername=="FE" ){
            solver_FEM_1D(u_delta_plus,u_ini_plus,grid,k,h,T);
        }
        else{
          cout << "No solver for the input" << endl;
        }
        //print the result with ini+delta

        caselabel=solvername+"_plus";
        print_output( outputfilename, caselabel,grid,u_ini_plus, u_delta_plus, h, k, T);
        std::cout<<" from process"<<rank<<"of"<<num_procs<<'\n';

    }
    if(rank==2){
      // solver the new problem
      //use different solver for the original solutio
        if (solvername=="BE" ) {
            solver_back_euler_1D(u_delta_minus,u_ini_minus,grid,k,h,T) ;

          }
        else if (solvername=="E" ){
            solver_euler_1D(u_delta_minus,u_ini_minus,grid,k,h,T) ;

        }
        else if (solvername=="CN" ){
            solver_crank_nicolson_1D(u_delta_minus,u_ini_minus,grid,k,h,T);

        }
        else if (solvername=="DF" ){
            solver_DuFort_Frankel_1D(u_delta_minus,u_ini_minus,grid,k,h,T);

        }
        else if (solvername=="FE" ){
            solver_FEM_1D(u_delta_minus,u_ini_minus,grid,k,h,T);
        }
        else{
          cout << "No solver for the input" << endl;
        }
        //print the result with ini+delta

        //print the result with ini-delta
        caselabel=solvername+"_minus";
        print_output( outputfilename,caselabel,grid, u_ini_minus, u_delta_minus, h,k,T);
        std::cout<<" from process"<<rank<<"of"<<num_procs<<'\n';
    }


  }
  else{
    // stability study, give a small disturbulation delta on initial condition
      //update the initial condtion with disturb

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
        else if (solvername=="FE" ){
            solver_FEM_1D(u_delta_plus,u_ini_plus,grid,k,h,T);
            solver_FEM_1D(u_delta_minus,u_ini_minus,grid,k,h,T);
        }
        else{
          cout << "No solver for the input" << endl;
        }
        //print the result with ini+delta

        caselabel=solvername+"_plus";
        print_output( outputfilename, caselabel,grid,u_ini_plus, u_delta_plus, h, k, T);

        //print the result with ini-delta
        caselabel=solvername+"_minus";
        print_output( outputfilename,caselabel,grid, u_ini_minus, u_delta_minus, h,k,T);
        std::cout<<" from process"<<rank<<"of"<<num_procs<<'\n';

  }


//  MPI::Finalize();

}
