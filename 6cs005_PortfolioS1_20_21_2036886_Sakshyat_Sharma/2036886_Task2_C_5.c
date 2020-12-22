#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer.

  Compile with:
	cc -o 2036886_Task2_C_5 2036886_Task2_C_5.c -lcrypt -pthread 

  If you want to analyse the output then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:
    	./2036886_Task2_C_5

  Dr Kevan Buckley, University of Wolverhampton, 2018 Modified by Dr. Ali Safaa 2019
******************************************************************************/


char *encrypted= "$6$AS$3tO1nv6UTBEiADlwQasACiyiFj4dZIhd/hkyeBXiYaBMgrHx4HzSiDMhDzqM/C1dtGFfvqNSCEasynunym83T/";  
pthread_mutex_t mutex;


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void threads()
{
pthread_mutex_init(&mutex, NULL);	
  pthread_t thread_1,thread_2;
  void *kernel_function_1();
  void *kernel_function_2();
  
  pthread_create(&thread_1, NULL,(void*)kernel_function_1, encrypted); 
  pthread_create(&thread_2, NULL,(void*)kernel_function_2, encrypted);
  
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/





void *kernel_function_1(char *salt_and_encrypted){
  int x,y,z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;  
   int count = 0;     // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  pthread_mutex_lock(&mutex);
  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
        for(z=0; z<=99; z++){
          sprintf(plain, "%c%c%02d", x, y, z); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
            printf("#%-8d%s %s\n", count, plain, enc);
              //return; //uncomment this line if you want to speed-up the running time, program will find you the cracked password only without exploring all possibilites
          } 
        } 
      }
    }
    pthread_mutex_unlock(&mutex);
  }
  void *kernel_function_2(char *salt_and_encrypted){
  int x,y,z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;  
  int count = 0;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  pthread_mutex_lock(&mutex);

  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
        for(z=0; z<=99; z++){
          sprintf(plain, "%c%c%02d", x, y, z); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		        //return;	//uncomment this line if you want to speed-up the running time, program will find you the cracked password only without exploring all possibilites
          } 
        } 
      }
    }
    pthread_mutex_unlock(&mutex);
  }

int time_difference(struct timespec *start, struct timespec *finish, 
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
  struct timespec start, finish;
  long long int time_elapsed;   
  clock_gettime(CLOCK_MONOTONIC, &start);
  threads();
  clock_gettime(CLOCK_MONOTONIC, &finish); 
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}




