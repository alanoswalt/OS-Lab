#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
  
#define COMIENDO 0 
#define HAMBRIENTO 1 
#define ESPERA 2 
#define N 5 

#define IZQ (phyid + 4) % N 
#define DERE (phyid + 1) % N 

//compilar usando gcc diner.c -o diner.o -l pthread

int phmode[N]; 
int phil[N] = {0,1,2,3,4}; 
  
sem_t mutex; 
sem_t S[N]; 

//Checar el estado del filosofo y sus vecinos
void checking(int phyid) 
{ 
	if (phmode[phyid] == HAMBRIENTO && phmode[IZQ] != COMIENDO && phmode[DERE] != COMIENDO)
	{ 
		phmode[phyid] = COMIENDO;
		printf("Filosofo %d toma palillos %d y %d\n",phyid+1,IZQ+1,phyid+1);
		printf("Filosofo %d esta COMIENDO\n",phyid+1);
		sem_post(&S[phyid]);
	}
} 

//Filosofo deja palillos que ya uso
void dejar_palillos(int phyid)
{
	sem_wait(&mutex);
	phmode[phyid] = ESPERA;
	printf("Filosofo %d dejar palillo %d y %d en mesa\n",phyid+1,IZQ+1,phyid+1);
	printf("Filosofo %d esta en ESPERA\n",phyid+1);
	checking(IZQ);
	checking(DERE);
	sem_post(&mutex);
}

//Filosofo toma palillos que esten desocupados
void tomar_palillos(int phyid)
{
	sem_wait(&mutex);
	phmode[phyid] = HAMBRIENTO;
	printf("Filosofo %d esta HAMBRIENTO\n",phyid+1);
	checking(phyid); 
	sem_post(&mutex);
	sem_wait(&S[phyid]);
}



//Filosofos
void* philospher(void* num)
{
	while(1){
		int* i = num;
		sleep((rand()%(3+1)));
		tomar_palillos(*i);
		sleep((rand()%(3+1)));
		dejar_palillos(*i);
	}
}




int main()
{
	int i;
	pthread_t thread_id[N];
	sem_init(&mutex, 0, 1);
	for (i = 0; i < N; i++)
	{
		sem_init(&S[i], 0, 0);
	}
	for (i = 0; i < N; i++)
	{
        	pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
        	printf("Filosofo %d esta en ESPERA\n", i + 1);
	}
	for (i = 0; i < N; i++)
	{
		pthread_join(thread_id[i], NULL);
	}
}
