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


const int xdemes = 500;
const int ydemes = 500;
const int zdemes = 100;
unsigned int n_gens = 100;
unsigned int deatht = 40;
const float liftp = 0.1;




long double deme[xdemes][ydemes][zdemes] = {{{0}}};

int main(){
	using namespace std;




	srand (time(NULL));


	int n_data = 25;
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

	int init_rad =25;


	for(int i = int(xdemes*.5)-init_rad; i < int(xdemes*.5)+init_rad; i++){
		for(int j = int(ydemes*.5)-init_rad; j < int(ydemes*.5)+init_rad; j++){
			if (pow(abs(int(xdemes*.5) -i )* abs(int(xdemes*.5) - i ) + abs(int(ydemes*.5) - j) * abs(int(ydemes*.5) - j) ,.5)<init_rad ){
				deme[i][j][0] =1;
			}
		}

	}



	int neighb[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};
	vector <int> fullx;
	vector <int> fully;
	vector <int> fullz;
	vector <int> nottrappedx;
	vector <int> nottrappedy;
	vector <int> nottrappedz;

	for (int dt = 0 ; dt < n_gens; dt++ ){		
		vector <int> nottrappedx;
		vector <int> nottrappedy;
		vector <int> nottrappedz;


		
		for(int i = 0; i < xdemes; i++){
			for(int j = 0; j < ydemes; j++){
				for(int k = 0; k < zdemes; k++){
					if (deme[i][j][k] ==1){
						
						//fullx.push_back(i);
						//fully.push_back(j);
						//fullz.push_back(k);

						vector <int> empty;
						for(int ne = 0; ne < 6; ne++){
							if(( (i+neighb[ne][0]) >0)&&( (j+neighb[ne][1]) >0)&&( (k+neighb[ne][2]) >0)&&((i+neighb[ne][0]) <xdemes)&&((j+neighb[ne][1]) <ydemes)&&( (k+neighb[ne][2]) <zdemes)){
								//deme[i+neighb[ne][0]][j+neighb[ne][1]][k+neighb[ne][2]]=1;
								empty.push_back(ne);

							}

						}

						if (empty.size()>0){
							nottrappedx.push_back(i);
							nottrappedy.push_back(j);
							nottrappedz.push_back(k);
						}
						else{


						}

						


					}


				}
			}
		}


		for(int f=0; f<nottrappedx.size(); f++){
			int x = nottrappedx[f];
			int y = nottrappedy[f];
			int z = nottrappedz[f];

			vector <int> empty;
			for(int ne = 0; ne < 6; ne++){
				if(( (x+neighb[ne][0]) >0)&&( (y+neighb[ne][1]) >0)&&( (z+neighb[ne][2]) >0)&&((x+neighb[ne][0]) <xdemes)&&((y+neighb[ne][1]) <ydemes)&&( (z+neighb[ne][2]) <zdemes)){
					//deme[i+neighb[ne][0]][j+neighb[ne][1]][k+neighb[ne][2]]=1;
					empty.push_back(ne);

				}

			}

			int pick = rand() % empty.size() + 0;
			deme[x+neighb[empty[pick]] [0]][y+neighb[empty[pick]] [1]][z+neighb[empty[pick]] [2]]=1;


			//deme[x+neighb[empty[pick]] [0]][y+neighb[empty[pick]] [1]][z+neighb[empty[pick]] [2]]=1;

			





		}




		if (dt==deatht){

			for(int i = int(xdemes*.5)-2; i < int(xdemes*.5)+2; i++){
				for(int j = int(ydemes*.5)-10; j < int(ydemes*.5)+10; j++){
					
					deme[i][j][2] =0;
					deme[i][j][1] =0;
					deme[i][j][0] =0;
					
				}

			}



		}



		if (dt % record_time == 0){

			ostringstream strT;
        	strT << dt;
        	string proftName = "prof_T"+ strT.str() + "_" + date_time.str() + ".txt";
        	string profzName = "prof_Z"+ strT.str() + "_" + date_time.str() + ".txt";
        	ofstream fproft,fprofz;
            fproft.open("standard_data/"+proftName);
            fprofz.open("standard_data/"+profzName);
            for(int i = 0; i <xdemes; i++){
            	for(int j = 0; j <ydemes; j++){
            		for(int k = 0; k <zdemes; k++){
	          			if (deme[i][j][k]==1){
            				fproft << i << ", " << j << ", "<< k <<endl;

            			}

    				}
            	}
        	}
            for(int i = 0; i <xdemes; i++){
            	for(int j = 0; j <ydemes; j++){
            		int zmax=0;
            		for(int k = 0; k <zdemes; k++){
	          			if (deme[i][j][k]==1){
            				zmax = k;

            			}

    				}
    				fprofz << i << ", " << j << ", "<< zmax <<endl;
            	}
        	}

        	//fproft.close(proftName);

		}

	}

	ostringstream strT;
	strT << n_gens;
	string proftName = "prof_T"+ strT.str() + "_" + date_time.str() + ".txt";
	string profzName = "prof_Z"+ strT.str() + "_" + date_time.str() + ".txt";
	ofstream fproft,fprofz;
    fproft.open("standard_data/"+proftName);
    fprofz.open("standard_data/"+profzName);
    for(int i = 0; i <xdemes; i++){
    	for(int j = 0; j <ydemes; j++){
    		for(int k = 0; k <zdemes; k++){
      			if (deme[i][j][k]==1){
    				fproft << i << ", " << j << ", "<< k <<endl;

    			}

			}
    	}
	}
    for(int i = 0; i <xdemes; i++){
    	for(int j = 0; j <ydemes; j++){
    		int zmax=0;
    		for(int k = 0; k <zdemes; k++){
      			if (deme[i][j][k]==1){
    				zmax = k;

    			}

			}
			fprofz << i << ", " << j << ", "<< zmax <<endl;
    	}
	}

    clock_t c_fin = clock();
    double run_time = double(c_fin - c_init)/CLOCKS_PER_SEC;

	cout << "Finished!" << "\n";
	cout << "Finished in " << run_time << " seconds \n";
	return 0;



}