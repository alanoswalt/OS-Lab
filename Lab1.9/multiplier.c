#include <stdio.h>
//#inclide <sentpf.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>

#define HILERAS 2000
#define COLUMNAS 2000
#define TOTAL 4000000
#define MAX_LINE 80
#define MX_A "matA.dat"
#define MX_B "matB.dat"
#define nchar 255
#define THREADS 20
#define CY 100



long* leer(char*);
long* columna(int, long*);
long* hilera(int, long*);
int locked(void);
int lockedFree(int);
long puntaso(long *vec1, long *vec2);
long * multiply(long *matA, long *matB);
int saveData(long  * result);
pthread_mutex_t * mutexes;
void * scaningMTX(void* row);


typedef struct {
	int id;
	long * mat1;
	long * mat2;
}threads;

//Matrixes
int NUM_BUFFERS;
long **buffers, * matrixRes, * matrixRange, * matrixLenght, * Amatrix, * Bmatrix;
char args[MAX_LINE /2 + 1];

//Running
void *scaningMTX(void *param){	
	int mutex_id,p,h,j,k;
	while(-1==(mutex_id=locked()));
	long *row,*column;
	p=(int) param;
	
	row=malloc(HILERAS*sizeof(long));
	column=malloc(HILERAS*sizeof(long));
	memcpy(row,hilera(p,Amatrix),HILERAS*sizeof(long));
	
	for(h=0;h<HILERAS;h++){
		memcpy(column,columna(h,Bmatrix),HILERAS*sizeof(long));
		
		buffers[mutex_id][h]=puntaso(row,column);
	}
	for(j=0;j<HILERAS;j++){
		matrixRes[HILERAS*p+j]=buffers[mutex_id][j];
	}
	free(row);
	free(column);
	lockedFree(mutex_id);
	pthread_exit(0);
}

long * leer(char *filename){
	int j;
	FILE *fp;
	char buff[nchar];
	fp=fopen(filename, "r");
	for(j=0;j<TOTAL;j++){
		fgets(buff,nchar,(FILE*)fp);
		matrixRange[j]=(long)atoi(buff);    
	}
	fclose(fp);
	return matrixRange;
}

long * multiply(long * matA, long * matB){
	int i;
	int limit,k;
	pthread_t tid [HILERAS]; 	
	pthread_attr_t attr; 		
	pthread_attr_init(&attr);
	memcpy(Amatrix,matA,TOTAL*sizeof(long)); //memcpy
	memcpy(Bmatrix,matB,TOTAL*sizeof(long));
	limit=0;
	k=0;
	do{
		for (i = 0; i<THREADS; i++){ 
			pthread_create(&tid[i],&attr,scaningMTX,(void*)k);
			printf("%d \n",k);
			k++;
		}
		for (i = 0; i <THREADS; i++){ 
			pthread_join(tid[i], NULL);
		}
	}
	while(limit++<(HILERAS/THREADS)-1);
	free(Amatrix);
	free(Bmatrix);
	printf("%ld \n",matrixRes[0]);	
	printf("%ld \n",matrixRes[TOTAL-1]);
	return 0;
}




//Work for column
long * columna(int col, long * matrix){	
	int x;
	for(x=0;x<COLUMNAS;x++)matrixLenght[x]=matrix[x*COLUMNAS+col];
	return(matrixLenght);
}

//Work for row
long * hilera(int row, long * matrix){
	int y;
	for(y=0;y<HILERAS;y++)matrixLenght[y]=matrix[y+row*HILERAS];
	return(matrixLenght);
}




long puntaso(long * vec1, long * vec2){
	int z;
	long proDOT;
	proDOT=0;
	for(z=0;z<HILERAS;z++)proDOT+=vec1[z]*vec2[z];
	return proDOT;
}

int saveData(long *result){
	int s;
	FILE *fp = fopen("result.dat","w");
	for(s=0;s<TOTAL;s++){
		fprintf(fp,"%ld\n",result[s]);
	}
	fclose(fp);
	return 0;
}


int lockedFree(int a){
	if(0==(pthread_mutex_unlock(&mutexes[a]))){
		return 0;
	}	
	else {
		return -1;	
	}
}



int locked(){
	int m;
	for(m=0;m<NUM_BUFFERS;m++){
		if(0==(pthread_mutex_trylock(&mutexes[m]))){
			return m;
		}
	}
	return -1;
}

/*for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;*/


int main (void){
	int i;
	long *matrixA,*matrixB;
	long *matrixtest,*matrixtest2;
	printf("Buffers form 1 to 3 ");
	fgets(args, MAX_LINE ,stdin);
	NUM_BUFFERS=atoi(args);	
	matrixA=malloc(TOTAL*sizeof(long));				
	matrixRange=malloc(TOTAL*sizeof(long));
	matrixB=malloc(TOTAL*sizeof(long));
	Amatrix=malloc(TOTAL*sizeof(long));
	Bmatrix=malloc(TOTAL*sizeof(long));
	matrixRes=malloc(TOTAL*sizeof(long));
	matrixLenght=malloc(HILERAS*sizeof(long));
	matrixtest=malloc(HILERAS*sizeof(long));
	matrixtest2=malloc(HILERAS*sizeof(long));
	buffers=malloc(NUM_BUFFERS*sizeof(long*));
	mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t));

	for(i=0;i<NUM_BUFFERS;i++){
		buffers[i]=malloc(HILERAS*sizeof(long));
	}
	memcpy(matrixA,leer(MX_A),TOTAL*sizeof(long));
	memcpy(matrixB,leer(MX_B),TOTAL*sizeof(long));

	multiply(matrixA,matrixB);
	memcpy(matrixRange,matrixRes,TOTAL*sizeof(long));
	saveData(matrixRange);
	pthread_mutex_destroy(mutexes);
	pthread_mutex_destroy(mutexes);
}
