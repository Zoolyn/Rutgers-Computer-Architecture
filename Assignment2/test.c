#include <stdlib.h>
#include <stdio.h>
#include "testHeader.h"

int main (int argc, char *argv[]){
	FILE *a,*b;
	int size,num;
	double x;
	a = fopen(argv[1],"r");
	b = fopen(argv[2],"r");

	if(a == NULL){
		printf("file 'a' not found\n");
		return 0;
	}
	if(b == NULL){
		printf("file 'b' not found\n");
		return 0;
	}
	fscanf(a,"%d",&size);
	printf("%d\n",size);
	fscanf(a,"%d",&num);
	printf("%d\n",num);
	int i=0,c=0;
	while(i!=((size)*num)){
		fscanf(a,"%lf,",&x);
		if(c ==4){
			printf("price: %lf\n",x);
			c=0;
		}
		else{
		printf("%lf ",x);
		c++;
		i++;
		}
	}
	fscanf(a,"%lf,",&x);
	printf("price: %lf\n",x);
	
}

