
#include <stdio.h>
#include <stdlib.h>

int a = 1;
int b;
int c = 3;
int d = 4;      


int main(){
	printf("A:1, C: 3, D: 4\n");
	printf("Given Statements: \n\n");
	printf("b = a + c\n");
	printf("b = c + d\n");
	printf("c = b + d\n");
	b = a + c;
	b = c + d;
	c = b + d;
	printf("\nFinal value of C: %d\n",c);
	printf("Final value of b: %d\n",b);

    return 0;
}


