#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
const double PI =3.141592653589793238463;

void read_input(string filename,vector<double>& grids,double& h_space,double& k_time,double& T_end){
/*
for the demo code, instead of read the requied information form file,
we used a standard test input for 1D sample                             
*/
    int N_space;
    int i=0;
    
    N_space=100;
    h_space=2*PI/(N_space+1);
    k_time=h_space;
    T_end=2* PI;
   for (i;i<=N_space;i++){
       grids.push_back(i*h_space);
 //      cout<<grids[i]<<endl;
   }
}
