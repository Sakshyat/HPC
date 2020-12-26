#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/******************************************************************************

  Sakshyat Sharma, 2036886
  
  Task2_A_1:
  SIngle Thread matrix

  Compile with:
    cc -o 2036886_Task2_A 2036886_Task2_A.c
  
  Run with:
    ./2036886_Task2_A

******************************************************************************/

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
{

  long long int ds = finish->tv_sec - start->tv_sec;
  long long int dn = finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ){
   ds--;
   dn += 1000000000;
  }
  
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(){

    int S,A,K;
    printf("\nEnter row of matrix 1\n");
    scanf("%d",&S);
    printf("\nEnter column of matrix 1\n");
    scanf("%d",&A);
    printf("Number of rows for matrix 2 : %d\n",A);
    printf("\nEnter column of matrix 2\n");
    scanf("%d",&K);
    
    struct timespec start, finish;
    long long int time_elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    int a[S][A],b[A][K], c[S][K];
    int i,j,k;
    
    for (i=0;i<S;i++){
        for(j=0;j<A;j++){

            a[i][j]=rand()%50;
        }
    }

    for(i=0;i<A;i++){
        for(j=0;j<K;j++){

            b[i][j]=rand()%50;
        }
    }
    
    for(i=0;i<A;i++){
        for(k=0;k<K;k++){
            for(j=0;j<S;j++){

                c[i][j]=c[i][j]+a[i][k]*b[k][j];
            }
        }
    }
    printf("\nThe results is\n");
	for(i=0; i<A; i++) {
	 for(j=0; j<K; j++) {
	   printf("%d  ", c[i][j]);
	  }
	printf("\n");
	}


	clock_gettime(CLOCK_MONOTONIC, &finish);
        time_difference(&start, &finish, &time_elapsed);
        printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

	return 0;
}
