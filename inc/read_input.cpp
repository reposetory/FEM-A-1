#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* atoi */
#include <mpi.h>
#include <stdexcept>

using namespace std;
const double PI = 3.141592653589793238463;

void read_input(int argc, char* argv[],string input_filename, string& filename, string& solvername, vector<double>& grids, double& h_space, double& k_time, double& T_end,int & dimension) {

//start concurency

	int num_procs =MPI::COMM_WORLD.Get_size();
	int rank =MPI::COMM_WORLD.Get_rank();


		int dim;
		double h, k, T;
		string num_scheme1, num_scheme, output_filename;


		int N_space;
		int i = 0;
		int flag=0;

		///////////////////// read in parameter.txt file
		string filename_full;
		ifstream myReadFile;
		filename_full =  "QT/"+input_filename + ".txt";
		myReadFile.open(filename_full.c_str());
		char output[100];
		if (myReadFile.is_open()) {
			int ii = 0;
			while (!myReadFile.eof()) {


				myReadFile >> output;
				switch (ii)
				{
				case 0: dim = atoi(output);
				case 1: num_scheme1 = output;
				case 2: k = atof(output);
				case 3: h = atof(output);
				case 4: T = atof(output);
				case 5: output_filename = output;
				default:
					break;
				}
				ii++;
			}
		}
		myReadFile.close();
		////////////////////////////////
	if (num_scheme1 == "Backward-Euler") {
	num_scheme = "BE";
	}
	else if (num_scheme1 == "Euler") {
	num_scheme = "E";
	}
	else if (num_scheme1 == "Crank-Nicolson") {
		num_scheme = "CN";
	}
	else if (num_scheme1 == "DuFort-Frankel") {
	num_scheme = "DF";
	}
	else if (num_scheme1 == "Finite-Element") {
		num_scheme = "FE";
	}
	else{
    cerr<<"undefined solver!"<<endl;
		flag=1;
	}

  if(dim!=1 && dim!=2 && dim!=3){
		cerr<<"wrong dimension defination!"<<endl;
		flag=1;
	}

	if(h<0){
		cerr<<"wrong space step specification!"<<endl;
		flag=1;
	}
	if(k<0){
		cerr<< "wrong time step specification!"<<endl;
		flag=1;
	}

	if(flag==1){
		throw runtime_error("input parameter error!");
	}

	if(k>T){
		cerr<<"wrong total time specification!"<<endl;
		throw ;
	}


  if(rank ==0){
		cout <<"the input parameters are: "<< '\n'<<"dimension of the problem: "<<dim << '\n' << "numerical scheme: "<<num_scheme << '\n' <<"time step size: "<< k << '\n'<<"space step size: " << h << '\n'<<"total time: " << T << '\n'<<"output file name: " << output_filename << endl;
	}
		h_space = h;
		k_time = k;
		T_end = T;
		solvername = num_scheme;
		filename = output_filename;
		N_space = 2 * PI / h_space - 1;
		dimension=dim;
		for (i; i <= N_space; i++) {
			grids.push_back(i*h_space);
			//      cout<<grids[i]<<endl;
		}


}
