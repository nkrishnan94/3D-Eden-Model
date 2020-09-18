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


const int xdemes = 20;
const int ydemes = 1600;
const int zdemes = 200;
unsigned int n_gens = 100;
unsigned int deatht= 150;
int CDP_flag = 1;
double K_cell= .5 * pow(10,3);
float Temp = 300;
float e_thresh =20;




long double deme[xdemes][ydemes][zdemes] = {{{0}}};

double energy(long double arr[xdemes][ydemes][zdemes], int x, int y, int z){

	int xp = -1;
	int xcnt=1;
	while (xp==-1){
		if(x+xcnt<xdemes){
			if (deme[x+xcnt][y][z] == 1){
				xp=xcnt;
			} else{

				xcnt+=1;
			}

		} else{

			xp=0;
		}

	}
	int xn=-1;

	while (xn==-1){
		if(x-xcnt>=0){

			if (deme[x-xcnt][y][z] == 1){
				xn=xcnt;
			} else{

				xcnt+=1;
			}

		} else{

			xn=0;
		}


	}


	int yp = -1;
	int ycnt=1;
	while (yp==-1){
		if(y+ycnt<ydemes){
			if (deme[x][y+ycnt][z] == 1){
				yp=ycnt;
			} else{

				ycnt+=1;
			}

		} else{


			yp=0;
		}

	}
	int yn=-1;
	ycnt=1;
	while (yn==-1){
		if(y-ycnt>=0){
			if (deme[x][y-ycnt][z] == 1){
				yn=ycnt;
			} else{

				ycnt+=1;
			}
		} else{

			yn=0;
		}

	}
	int zp = -1;
	int zcnt=1;
	while (zp==-1){
		if(z+zcnt<zdemes){
			if (deme[x][y][z+zcnt] == 1){
				zp=zcnt;
			} else{

				zcnt+=1;
			}

		} else{

			zp=0;
		}

	}

	int zn=-1;
	zcnt=1;
	while (zn==-1){
		if(z-zcnt>=0){
			if (deme[x][y][z-zcnt] == 1){
				zn=zcnt;
			} else{

				zcnt+=1;
			}

		} else{
			zn=0;
		}

	}





	return pow(pow(zp,2)+pow(zn,2)+pow(xp,2)+pow(xn,2)+pow(yp,2)+pow(yn,2),.5);

}



int main(){
	using namespace std;





	srand( unsigned(time(NULL)));


	int n_data = 25;
	int record_time = int(n_gens/n_data);
	//int record_time = 1;

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

	


	for(int i =1; i < xdemes; i+=2){
		for(int j =1; j < ydemes; j+=2){
			for(int k = 1; k < 50; k+=2){

				deme[i][j][k] =1;
				//ßagents+=1;

			}
			
		}

	}



	int neighb[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};

	
	int randx[xdemes] ={0};
	int randy[ydemes] ={0};
	int randz[zdemes] ={0};
	for(int i = 0; i < xdemes; i++){
		randx[i]=i;
	}

	for(int j= 0; j < ydemes; j++){
		randy[j]=j;
	}

	for(int k = 0; k < zdemes; k++){
		randz[k]=k;
	}

	/*if (empty.size()>0){
							nottrappedx.push_back(i)
							nottrappedy.push_back(j)
							nottrappedz.push_back(k)


						}*/
	//cout<<agents<<endl;
	
	for (int dt = 0 ; dt < n_gens; dt++ ){	
		//cout<<agents<<endl;



		random_shuffle(randx,randx+xdemes);
		random_shuffle(randy,randy+ydemes);
		random_shuffle(randz,randz+zdemes);

		
		

		

		for(int i = 0; i < xdemes; i++){
			for(int j = 0; j < ydemes; j++){
				for(int k = 0; k < zdemes; k++){


					int x=randx[i];
					int y=randy[j];
					int z=randz[k];
					//cout<<i<<", "<<j<<", "<<k<<", ""hi"<<endl;
					//spaces+=1;

					if (deme[x][y][z] ==1){

						//agents+=1;

						//cout<<agents<<endl;

						
						vector <int> empty;


						for(int ne = 0; ne < 6; ne++){
							if(( (x+neighb[ne][0]) >0)&&( (y+neighb[ne][1]) >0)&&( (z+neighb[ne][2]) >0)&&((x+neighb[ne][0]) <xdemes)&&((y+neighb[ne][1]) <ydemes)&&( (z+neighb[ne][2]) <zdemes)){
								//

								if (deme[x+neighb[ne][0]][y+neighb[ne][1]][z+neighb[ne][2]]==0){

									empty.push_back(ne);
								}
								

							}

						}

						
						if (empty.size()>0){
							int pick = rand() % empty.size() + 0;
						

							double energy0 = energy(deme,x,y,z);
							//cout<<deme[x][y][z]<<endl;
							deme[x][y][z]=0;
							
							//cout<<deme[x+neighb[empty[pick]][0]][y+neighb[empty[pick]] [1]][z+neighb[empty[pick]] [2]]<<endl;

							deme[x+neighb[empty[pick]][0]][y+neighb[empty[pick]] [1]][z+neighb[empty[pick]] [2]]=1;
							//cout <<x<<","<<y<<", "<<z<<", "<<deme[x][y][z]<<endl;
							
							double energy1 = energy(deme,x+neighb[empty[pick]][0],y+neighb[empty[pick]][1],z+neighb[empty[pick]][2]);
							
							double u;
							cout<<energy0<<endl;
							//cout<<i<<", "<<j<<", "<<k<<", "<<endl;
							if (energy1==energy0){

								cout<<"flag"<<endl;
							}


							if ((energy1<energy0) && (u>exp ( - (.5*K_cell * pow(abs(energy1-energy0) ,2))/Temp ) )||(energy0>e_thresh) ){
								
								
								//cout<< exp ( - (.5*K_cell * pow(abs(energy1-energy0) ,2))/Temp )<<endl;

								deme[x][y][z]=1;
								deme[x+neighb[empty[pick]] [0]][y+neighb[empty[pick]] [1]][z+neighb[empty[pick]] [2]]=0;


							}




						}
						
						


					}

				}
			}
		}



		//cout<<agents<<endl;
		if ((dt==deatht)&&(CDP_flag==1)){


			for(int i = 0; i < xdemes; i++){
				for(int j = int(ydemes*.5)-200; j < int(ydemes*.5)+200; j++){
					for(int k = 0; k < 41; k++){
						deme[i][j][k] =0;
					}
				}

			}



		}

		/*for(int i = 0; i < xdemes; i++){
			for(int j = 0; j < ydemes; j++){
				for(int k = 0; k < zdemes; k++){
					agents+=deme[i][j][k]

				}
			}
		}
		cout<<agents<<endl;*/



	
		if (( dt % record_time) == 0){



			ostringstream strT;
        	strT << dt;
        	string proftName = "prof_T"+ strT.str() + "_" + date_time.str() + ".txt";
        	string profzName = "prof_Z"+ strT.str() + "_" + date_time.str() + ".txt";
        	ofstream fproft,fprofz;
            fproft.open("CPD/"+proftName);
            fprofz.open("CPD/"+profzName);
            for(int i = 0; i <xdemes; i++){
            	for(int j = 0; j <ydemes; j++){
            		for(int k = 0; k <zdemes; k++){
	          			if (deme[i][j][k]==1){
            				fproft << i << ", " << j << ", "<< k <<endl;

            			}

    				}
            	}
        	}
        	//cout<<"hi"<<endl;
        	
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
		//cout<<"hi"<<endl;

	}


	
    clock_t c_fin = clock();
    double run_time = double(c_fin - c_init)/CLOCKS_PER_SEC;

	cout << "Finished!" << "\n";
	cout << "Finished in " << run_time << " seconds \n";
	return 0;
}




