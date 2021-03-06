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
const int zdemes = 500;
unsigned int n_gens = 50;


long double deme[xdemes][ydemes][zdemes] = {{{0}}};

int main(){
	using namespace std;




	srand (time(NULL));


	int n_data = 5;
	int record_time = int(n_gens/n_data);

	ofstream fprof;
	time_t time_start;
	clock_t c_init = clock();
	struct tm * timeinfo;
	char buffer [80];
	


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


	vector <int> fullx;
	vector <int> fully;
	vector <int> fullz;


	for (int dt = 0 ; dt < n_gens; dt++ ){	
		//ostringstream strT;
		//strT << dt;
		//cout <<	dt <<endl;

		//cout <<	dt <<endl;

		for(int i = 0; i < xdemes; i++){
		

			for(int j = 0; j < ydemes; j++){
			
				for(int k = 0; k < zdemes; k++){
					if (deme[i][j][k]==1){

						if ((count(fullx.begin(),fullx.end(),i)) ==0 && (count(fully.begin(),fully.end(),j)) ==0  &&(count(fullz.begin(),fullz.end(),k)) ==0 ){


							fullx.push_back(i);
							fully.push_back(j);
							fullz.push_back(k);
						}

						

					}

				}
			}
		}

	


		//int pick_deme = rand() % fullx.size() + 0;
		//cout <<pick_deme<<endl;
		//cout <<"hi"<<endl;

		
		//fullx.push_back(i);
		//fully.push_back(j);
		//fullz.push_back(k);


		//int i =fullx[pick_deme];
		//int j =fully[pick_deme];
		//int k =fullz[pick_deme];

		for(int f=0;f <fullx.size();f++){
			int i =fullx[f];
			int j =fully[f];
			int k =fullz[f];
			int pick = rand() % 6 + 0;


			if(pick==0){
				int empty_flag = 0;
				if(i>0){
					for(int x =i-1; x>0; x--){
						if ((deme[x][j][k] ==0) &&  (empty_flag==0)){

							deme[x][j][k] =1;
							empty_flag = 1;
						}
					}
				}

			}

			if(pick==1){
				int empty_flag = 0;
				if (i<xdemes-1){
					for(int x =i+1; x<xdemes; x++){
						if ((deme[x][j][k] ==0) &&  (empty_flag==0)){
							deme[x][j][k] =1;
							empty_flag = 1;
							
						}
					}
				}

			}



			if(pick==2){
				int empty_flag = 0;
				if (j>0){
					for(int y = j-1; y>0; y--){
						if ((deme[i][y][k] ==0) &&  (empty_flag==0)){

							deme[i][y][k] =1;
							empty_flag = 1;
						}
					}
				}

			}

			if(pick==3){
				int empty_flag = 0;
				if (j<ydemes-1){
					for(int y =j+1; y<ydemes; y++){
						if ((deme[i][y][k] ==0) &&  (empty_flag==0)){
							deme[i][y][k] =1;
							empty_flag = 1;
							
						}
					}
				}

			}


			if(pick==4){
				int empty_flag = 0;
				if (k>0){
					for(int z =k-1; z>0; z--){
						if ((deme[i][j][z] ==0) &&  (empty_flag==0)){

							deme[i][j][z] =1;
							empty_flag = 1;
						}
					}
				}
			}

			if(pick==5){
				int empty_flag = 0;
				if(k<zdemes-1){
					for(int z =k+1; z<zdemes; z++){
						if ((deme[i][j][z] ==0) &&  (empty_flag==0)){
							deme[i][j][z] =1;
							empty_flag = 1;
							
						}
					}
				}

			}

		}

		

		









		if (dt % record_time == 0){

			ostringstream strT;
        	strT << dt;
        	string proftName = "prof_T"+ strT.str() + "_" + date_time.str() + ".txt";
        	string profzName = "prof_Z"+ strT.str() + "_" + date_time.str() + ".txt";
        	ofstream fproft,fprofz;
            fproft.open("push_data/"+proftName);
            fprofz.open("push_data/"+profzName);
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

    clock_t c_fin = clock();
    double run_time = double(c_fin - c_init)/CLOCKS_PER_SEC;

	cout << "Finished!" << "\n";
	cout << "Finished in " << run_time << " seconds \n";
	return 0;



}