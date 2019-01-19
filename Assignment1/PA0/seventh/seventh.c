#include <stdlib.h>
#include <stdio.h>


int main (int argc, char *argv[]){
	int i,j;
	for(i=1; argv[i]!='\0';i++){
		for(j = 0; argv[i][j]!='\0';j++){
			if(argv[i][j+1] == '\0'){
				printf("%c",argv[i][j]);
			}
		} 
	}
	printf("\n");
	return 0;
}
