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





// 2d boundaryy condition defination
void boundary_2d_1(vector<double>& u_ini,vector<double> grid,double delta=0.0){



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

                          g1 = 0.5*(1.0 - xi(1,i));
                          g2 = 0.5*(1.0+ xi(1,i));
                          h1 = 0.5*(1.0- xi(2,i));
                          h2 = 0.5*(1.0 + xi(2,i));
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



 void solver_FEM_2D(MatrixXd u_ini, MatrixXd grid, double k, double h, double T){

   int nx,ny,node_all;
   nx=1+(2.0*PI)/h;
   ny=1+(2.0*PI)/h;
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

   if (ele_all != (nx-1)*(ny-1) ){
     cout<<"there is something wrong with element connectivity!"<<endl;
   }

 //create a local 2*node_all matrix contains all node coordinates
   MatrixXd grid_coord=MatrixXd::Zero(2,node_all);
   for (int i=0;i<(nx);i++){
     for(int j=0;j<(ny);j++){
        grid_coord(i+j*nx,0)=double(i)*h;
        grid_coord(i+j*nx,1)=double(j)*h;

     }
   }

  //


//for debug purpose creat a simple initial condition

 MatrixXd u_ini_debug(node_all,1);

 for(int i=0;i<node_all;i++){

u_ini(i)=sin(grid_coord(i,0)*grid_coord(i,1));

 }




  //

   //assemble the local element to global coordinate
   //*************************************************//
   //create the golbal mass matrix and stiffness matrix
   MatrixXd B=MatrixXd::Zero( node_all, node_all), A=MatrixXd::Zero(node_all, node_all);
   // create the local mass matrix and stiffness matrix
   MatrixXd B_ele=MatrixXd::Zero( 4, 4),A_ele=MatrixXd::Zero( 4, 4);//the element mass matrix and stiffness matrix
   MatrixXd x=MatrixXd::Zero( 2, 4);//the coordinates of element points
   int global_x,global_y;

   for (int i=0;i<(ele_all-1);i++){

      //get the coordinates for nodes in the element
       for(int j=0;j<4;j++){
         x(0,j)=grid_coord(element_set(i,j),0);
         x(1,j)=grid_coord(element_set(i,j),1);
       }
       //get local stiffness
       calculate_ele_stiff_2d(B_ele,A_ele,x);

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
       MatrixXd u_t(node_all,1),u_tau( node_all,1);
// a big matrix that stores the results in each time step
       MatrixXd u=MatrixXd::Zero(n_time,node_all);

       u_t=u_ini_debug;

       for(int i=0;i<n_time;i++){

         // solve the equation (B+k*A)*u_tau=B*u_t
           // use the linear solve in Eigen class
           ColPivHouseholderQR< MatrixXd> dec(B+k*A);
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
