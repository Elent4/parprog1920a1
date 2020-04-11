#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double *wct){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	*wct = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

int main(){

	float *array01, *array02;
	float K0 = 0.5, K1 = 0.5, K2 = 0.5, K3 = 0.5, K5 = 0.5, K6 = 0.5, K7 = 0.8, K8 = 0.5, K4 = 5.0 ;
	double ts, te; 
	int i, j;

//Desmeuseis
	array01 = (float*) malloc(N* M* sizeof(float));
	array02 = (float*) malloc(N* M* sizeof(float));

//Arxikopoiisi
	for(i=0; i < N * M; i++){
		array01[i] = ((float) rand()/(float)(RAND_MAX));
		array02[i] = 1;
		
	}

	get_walltime(&ts);
	printf("\n%f", ts);

//Fortio

	for(i = 1; i < N-1; i++){
		for(j = 1; j < M-1; j++){
			array02[j] = (array01[(i-1)+(j-1)] * K0) + (array01[(i-1)+j] * K1) + (array01[(i-1)+(j+1)] * K2) 
				+ (array01[i+(j-1)] * K3) + (array01[i+j] * K4) + (array01[i+(j+1)] * K5) 
				+ (array01[(i+1)+(j-1)] * K6) + (array01[(i+1)+j] * K7) + (array01[(i+1)+(j+1)] * K8);	
		}
	}

	get_walltime(&te);	
	printf("\n%f", te);

//Elegxos
	printf("\n%f\n", te-ts);
	printf("\n%f\n", (2.0*M*N) / ((te-ts)*1e6));

//Apodesmeusi
	free(array01);
	free(array02);
	return 0;
}

