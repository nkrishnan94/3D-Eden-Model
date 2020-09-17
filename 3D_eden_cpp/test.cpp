#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <array>
#include <vector>
#include <random>
#include <ctime> 
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>



int main(){


	int neighb[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};;


	srand (time(NULL));
	int pick = rand() % 3 + 0;
	//std::cout <<rand() << "\n";

	double u;
	srand( unsigned(time(NULL)));

	u=(double)rand()/(RAND_MAX + 1)+1+(rand()%1);
	std::cout<<u <<"\n";











	return 0;
}