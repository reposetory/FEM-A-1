#include "stdafx.h"
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* atoi */


using namespace std;
const double PI = 3.141592653589793238463;

void read_input(string filename, vector<double>& grids, double& h_space, double& k_time, double& T_end) {
	/*
	for the demo code, instead of read the requied information form file,
	we used a standard test input for 1D sample
	*/

	int dim;
	double h, k, T;
	string num_scheme, output_filename;


	int N_space;
	int i = 0;

	///////////////////// read in parameter.txt file
	string filename_full;
	ifstream myReadFile;
	filename_full = "C:\\Users\\Daegyoum\\Documents\\test4_Qt\\" + filename + ".txt";
	myReadFile.open(filename_full);
	char output[100];
	if (myReadFile.is_open()) {
		int ii = 0;
		while (!myReadFile.eof()) {


			myReadFile >> output;
			switch (ii)
			{
			case 0: dim = atoi(output);
			case 1: num_scheme = output;
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

	cout <<"the input parameters are: "<< '\n'<<"dimension of the problem: "<<dim << '\n' << "numerical scheme: "<<num_scheme << '\n' <<"time step size: "<< k << '\n'<<"space step size: " << h << '\n'<<"total time: " << T << '\n'<<"output file name: " << output_filename << endl;

	h_space = h; 
	k_time = k; 
	T_end = T;
	N_space = 2 * PI / h_space - 1; 

	for (i; i <= N_space; i++) {
		grids.push_back(i*h_space);
		//      cout<<grids[i]<<endl;
	}
}