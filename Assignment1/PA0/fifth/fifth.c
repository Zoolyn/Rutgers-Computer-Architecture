#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int i,j,size,sumD=0,sumR=0,sumC=0,sum,magic=1;//magic = 1 means it is true
	int** matrix;
	FILE *fd;
	
	fd = fopen(argv[1],"r");
	fscanf(fd,"%d",&size);
	
	matrix = (int**)malloc(sizeof(int*));
	for(i=0;i<size;i++){
		matrix[i] = (int*)malloc(size*sizeof(int));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			fscanf(fd,"%d",&matrix[i][j]);
		}
	}
	for(i=0;i<size;i++){
		sum += matrix[0][i];
	}
	for(i=0;i<size;i++){
		sumR = 0;
		for(j=0l;j<size;j++){
				sumR += matrix[i][j];
		}

		if(sumR != sum){
			magic = 0;
			break;
		}
	}
	if(magic == 1){
		for(i=0;i<size;i++){
			sumC = 0;
			for(j=0;j<size;j++){
				sumC += matrix[j][i];
			}
		

			if(sumC != sum){
				magic=0;
				break;
			}
		}
	}

	if(magic ==1){
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				if(i == j){
					sumD += matrix[i][j];
				}
			}
		}

		if(sumD != sum){
			magic = 0;
		}
	}
	if(magic==1){
		printf("magic\n");
	}
	else{
		printf("not-magic\n");
	}	
	
	fclose(fd);
	free(matrix);
	return 0;
}
