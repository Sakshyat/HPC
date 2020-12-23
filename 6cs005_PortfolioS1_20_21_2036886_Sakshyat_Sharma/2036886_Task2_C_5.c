#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

/******************************************************************************

   Sakshyat Sharma, 2036886
   
   Task2_C_5:
   Crack an encrypted password that consist only of 2 uppercase letters and a 2 digit integer using multithread.

  Compile with:
	cc -o 2036886_Task2_C_5 2036886_Task2_C_5.c -lcrypt -pthread 

  Run with:
    	./2036886_Task2_C_5

******************************************************************************/


char *enc_password= "$6$AS$v3aoGpYBSLWN3oLWkWXyVcjOgbCDTjqig1h0Rl8TOsYs.Jtbksd/tw4jMNmpaUouWg9LJRQdJtu4ZJBEQAwA11";  
pthread_mutex_t mutex;


void substr(char *dest, char *src, int start, int length)
{

  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
  
}

void thread_def()
{

  pthread_mutex_init(&mutex, NULL);	
  pthread_t pthread1,pthread2;
  void *kernel_function_1();
  void *kernel_function_2();
  
  pthread_create(&pthread1, NULL,(void*)kernel_function_1, enc_password); 
  pthread_create(&pthread2, NULL,(void*)kernel_function_2, enc_password);
  
  pthread_join(pthread1, NULL);
  pthread_join(pthread2, NULL);

}

void *kernel_function_1(char *salt_and_encrypted)
{

  int s,a,k;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 
  char plain[7];   // The combination of letters currently being checked 
  char *enc;  
  int count = 0;     // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  
  pthread_mutex_lock(&mutex);
  
   for(s='A'; s<='M'; s++){
    for(a='A'; a<='Z'; a++){
      for(k=0; k<=99; k++){
        sprintf(plain, "%c%c%02d", s, a, k); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
        } 
      }
    }
  }
    pthread_mutex_unlock(&mutex);
    
  }
  
 void *kernel_function_2(char *salt_and_encrypted)
 {
 
  int s,a,k;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 
  char plain[7];   // The combination of letters currently being checked
  char *enc;  
  int count = 0;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  
  pthread_mutex_lock(&mutex);

   for(s='N'; s<='Z'; s++){
    for(a='A'; a<='Z'; a++){
      for(k=0; k<=99; k++){
        sprintf(plain, "%c%c%02d", s, a, k); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
        } 
      }
    }
  }
    pthread_mutex_unlock(&mutex);
    
  }

int time_difference(struct timespec *start, struct timespec *finish,long long int *difference) 
{

  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  
  *difference = ds * 1000000000 + dn;
  
  return !(*difference > 0);
  
}

int main(int argc, char *argv[])
{

  struct timespec start, finish;
  long long int time_elapsed;  
   
  clock_gettime(CLOCK_MONOTONIC, &start);
  
  thread_def();
  
  clock_gettime(CLOCK_MONOTONIC, &finish); 
  time_difference(&start, &finish, &time_elapsed);
  
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,(time_elapsed/1.0e9)); 

  return 0;
  
}




