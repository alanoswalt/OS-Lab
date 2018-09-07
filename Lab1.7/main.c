#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int n=10,bt[10],wt[10],rt[10]avwt=0,i,j,total=0,pos,temp, count,time,remain,flag=0,time_quantum; 
wt[0]=0;    //El WT en el numero 1 es 0

void FCFS (void){
 
    printf("\nDar el Burst Time para cada proceso\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
 
 
    //Calcular WT
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("\nProcess\t\tBurst Time);
 
 
    avwt/=i;
    printf("\n\nAverage Waiting Time:%d",avwt);
 
    return 0;
}

void PSA (void){
	printf("\nMeter el Burst time y la prioridad\n");
	    for(i=0;i<n;i++)
	    {
	        printf("\nP[%d]\n",i+1);
	        printf("Burst Time:");
	        scanf("%d",&bt[i]);
	        printf("Priority:");
	        scanf("%d",&pr[i]);
	        p[i]=i+1;        
	    }
 
	//Ordenar valores usando selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        tem=pr[i];
        pr[i]=pr[pos];
        pr[pos]=tem;
 
        tem=bt[i];
        bt[i]=bt[pos];
        bt[pos]=tem;
 
        tem=p[i];
        p[i]=p[pos];
        p[pos]=tem;
    }
    //WT
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
    avwt/=i;
    printf("\n\nAverage Waiting Time=%d",avwt);
}


void SJF (void){
	 printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;           
    }
 
    //selection sort para prdenar
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
 
        tem=bt[i];
        bt[i]=bt[pos];
        bt[pos]=tem;
 
        tem=p[i];
        p[i]=p[pos];
        p[pos]=tem;
    }
 
    //WT
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        
    }
 
   avwt/=i;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time");

    printf("\n\nAverage Waiting Time=%f",avwt);
  
}

//RR con problemas
/*
void RR (void){
 
  for(i=0;i<n;i++) 
  { 
    printf("Meter AV, BT Y PN %d :",count+1); 
    scanf("%d",&at[count]); 
    scanf("%d",&bt[count]); 
    rt[count]=bt[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&qu); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=qu && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=qu; 
      time+=qu; 
    }   
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  
  return 0; 

}
*/


int main(void){
	srand(time(NULL));
	unsigned char x=1;
	while(x){
		char select;
		printf("Seleccionar:\n1) FCFS\n2) SJF\n3) PSA\n4) RR\n> ");
		scanf("%c",&num);
		
		if(num==1){
			FCFS();
		}
		else if (num==2){
			SJF();
		}
		else if (num==3){
			PSA();
		}
		else if (num==4){
			RR();
		}
	}
	return 0;
}
