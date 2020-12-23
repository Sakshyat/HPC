#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>


/******************************************************************************

  Sakshyat Sharma, 2036886
  
  Task2_C_3:
  Crack an encrypted password that consist only of 3 uppercase letters and a 2 digit integer.

  Compile with:
    cc -o 2036886_Task2_C_3 2036886_Task2_C_3.c -lcrypt

  Run with:
    ./2036886_Task2_C_3 

 ******************************************************************************/

int count=0;     // A counter used to track the number of combinations explored so far
char *enc_password = "$6$AS$DMQzjeV8s7Qz/s51815VR1dNvd.jLHx8D9JKJqGJrLLGR8el/n7L6IR1D.HHyKF6lUwR4EU4QM9l.JuXXtdEb0";

void substr(char *dest, char *src, int start, int length)
{

  memcpy(dest, src + start, length);
  *(dest + length) = '\0';

}

void crack_pass(char *salt_and_encrypted)
{

  int p, x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 
  char plain[7];   // The combination of letters currently being checked 
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(p='A'; p<='Z'; p++)
   for(x='A'; x<='Z'; x++){
     for(y='A'; y<='Z'; y++){
       for(z=0; z<=99; z++){
         sprintf(plain, "%c%c%c%02d", p, x, y, z); 
         enc = (char *) crypt(plain, salt);
         count++;
         if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
         } 
       }
     }
   }
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


int main(int argc,char *argv[])
{

 struct timespec start, finish;
 long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  crack_pass(enc_password);

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

  return 0;
  
}

