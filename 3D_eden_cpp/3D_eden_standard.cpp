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


const int xdemes = 100;
const int ydemes = 100;
const int zdemes = 100;
unsigned int n_gens = 3;


long double deme[xdemes][ydemes][zdemes] = {{0}};

int main(){
	using namespace std;




	srand (time(NULL));


	int n_data = 1;
	int record_time = int(n_gens/n_data);

	ofstream fprof;
	time_t time_start;
	clock_t c_init = clock();
	struct tm * timeinfo;
	char buffer [80];
	float ht = 0.5;
	int prof_count = 4;


	time (&time_start);
	timeinfo = localtime (&time_start);
	strftime (buffer,80,"%F-%H-%M-%S",timeinfo);
	ostringstream date_time;
	date_time << buffer;


	for(int i = int(xdemes*.5)-1; i < int(xdemes*.5)+1; i++){
		for(int j = int(ydemes*.5)-1; j < int(ydemes*.5)+1; j++){
			deme[i][j][0] =1;





		}

	}



	int neighb[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};

	for (int dt = 0 ; dt < n_gens; dt++ ){

		
		for(int i = 0; i < xdemes; i++){
			for(int j = 0; j < ydemes; j++){
				for(int k = 0; k < zdemes; k++){
					if (deme[i][j][k] ==1){
						vector <int> empty;
						for(int ne = 0; ne < 6; ne++){
							if(( (i+neighb[ne][0]) >0)&&( (j+neighb[ne][1]) >0)&&( (k+neighb[ne][2]) >0)&&((i+neighb[ne][0]) <xdemes)&&((j+neighb[ne][1]) <ydemes)&&( (k+neighb[ne][2]) <zdemes)){
								//deme[i+neighb[ne][0]][j+neighb[ne][1]][k+neighb[ne][2]]=1;
								empty.push_back(ne);
							

							}


						}
						//cout << i<<", " << j<< ", " <<k << ", "<<empty.size() <<endl;
						if (empty.size()>0){

							int pick = rand() % empty.size() + 0;


							deme[i+neighb[empty[pick]][0]][j+neighb[empty[pick]][1]][k+neighb[empty[pick]][2]]=1;

						}




					}






					


				}
			}
		}

		if (dt % record_time == 0){

			ostringstream strT;
        	strT << dt;
        	string proftName = "prof_T"+ strT.str() + "_" + date_time.str() + ".txt";
        	ofstream fproft;
            fproft.open(proftName);
            for(int i = 0; i <xdemes; i++){
            	for(int j = 0; j <ydemes; j++){
            		for(int k = 0; k <zdemes; k++){
            			fproft << i << ", " << j << ", "<< k<< ", " << deme[i][j][k] <<endl;

    				}
            	}
        	}

        	//fproft.close(proftName);

		}

	}

    clock_t c_fin = clock();
    double run_time = double(c_fin - c_init)/CLOCKS_PER_SEC;

	cout << "Finished!" << "\n";
	cout << "Finished in " << run_time << " seconds \n";
	return 0;



}