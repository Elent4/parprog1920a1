#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h> 

void get_walltime(double *wct){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	*wct = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

int main(){

	float *array01, *array02; //XXXX
	float K0 = 0.5, K1 = 0.5, K2 = 0.5, K3 = 0.5, K5 = 0.5, K6 = 0.5, K7 = 0.8, K8 = 0.5, K4 = 5.0 ;
	float arrayS[] = {0,0,0,0,0,0,0,0,0};
	double ts, te;
	int i, j;
	__m128 *varray01, *varray02;
	__m128 calcm0, calcm1, calcm2, calcm3, calcm4, calcm5, calcm6, calcm7, calcm8;
	__m128 sum1, sum2, sum3, sum4, sum5, sum6, sum7, sumres;

//Desmeuseis
	i = posix_memalign((void**)&array01, 16, N * M * sizeof(float));
	if(i!=0){
		exit(1);
	}

	i = posix_memalign((void**)&array02, 16, N * M *sizeof(float));
	if(i!=0){
		free(array01);
		exit(1);
	}

//Arxikopoiisi
	for(i=0; i < N * M; i++){
		array01[i] = ((float) rand()/(float)(RAND_MAX));
		array02[i] = 1;
		
	}

	get_walltime(&ts);
	printf("\n%f", ts);

//Fortio
	for(i = 1; i < N-1; i++){
		varray01 = (__m128*)array01;
		varray02 = (__m128*)array02;
		for(j = 1; j < M-1; j++){
			arrayS[0] = array01[(i-1)+(j-1)] * K0;
			calcm1 = _mm_load_pd(array01[(i-1)+(j-1)] * K0);
			
			arrayS[1] = array01[(i-1)+j] * K1;
			calcm2 = _mm_load_pd(&arrayS[1]);
			
			arrayS[2] = array01[(i-1)+(j+1)] * K2;
			calcm3 = _mm_load_pd(&arrayS[2]);
			
			arrayS[3] = array01[i+(j-1)] * K3;
			calcm4 = _mm_load_pd(&arrayS[3]);

			arrayS[4] = array01[i+j] * K4;
			calcm5 = _mm_load_pd(&arrayS[4]);

			arrayS[5] = array01[i+(j+1)] * K5;
			calcm6 = _mm_load_pd(&arrayS[5]);

			arrayS[6] = array01[(i+1)+(j-1)] * K6;
			calcm7 = _mm_load_pd(&arrayS[6]);						

			arrayS[7] = array01[(i+1)+j] * K7;
			calcm8 = _mm_load_pd(&arrayS[7]);

			arrayS[8] = array01[(i+1)+(j+1)] * K8;
			calcm9 = _mm_load_pd(&arrayS[8]);

			sum1 = _mm_add_pd(calcm0, calcm1);
			sum2 = _mm_add_pd(calcm2, calcm3;
			sum3 = _mm_add_pd(calcm4, calcm5);
			sum4 = _mm_add_pd(calcm6, calcm7);

			sum5 = _mm_add_pd(sum1, sum2);
			sum6 = _mm_add_pd(sum3, sum4);
			sum7 = _mm_add_pd(sum5, sum6);
			sumres = _mm_add_pd(sum7, calcm8);

			*varray02 = sumres;
		
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

