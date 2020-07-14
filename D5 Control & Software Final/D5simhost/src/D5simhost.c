/*
 ============================================================================
 Name        : D5simhost.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>



int main(void) {
	int n,i;
	float *ptr,v1,v2,*ptr2;
	char x[50];
	char y[50];
	srand(0);
	printf("Enter number of elements: ");
	n=10;
	ptr=(float*)malloc(n*sizeof(float));
	ptr2=(float*)malloc(n*sizeof(float));//memory allocated using malloc
	if(ptr==NULL)
	{
		printf("Sorry! unable to allocate memory");
		exit(0);
	}
	printf("Enter elements of array: ");
	for(i=0;i<n;++i)
	{
		*ptr=(rand()/(int)(RAND_MAX/10.00))*1000;
		*ptr2=rand()/(float)(RAND_MAX/10.00);
		v1=*(ptr);
		v2=*(ptr2);
		sprintf(x,"%.2f",v1);
		sprintf(y,"%.2f",v2);
		printf("value= %s\n",x);
		printf("value= %s\n",y);
	}

	free(ptr);
	free(ptr2);
	return 0;

}

