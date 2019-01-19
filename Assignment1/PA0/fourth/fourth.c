#include <stdlib.h>
#include <stdio.h>

int** multiply(int** matrix,int** matrix2,int size){
	int** product;
	int i,j,k;
	product = (int**)malloc(sizeof(int*));
	for(i=0;i<size;i++){
		product[i] = (int*)malloc(size*sizeof(int));
	}	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			product[i][j]=0;
			for(k=0;k<size;k++){
				product[i][j] += matrix[i][k]*matrix2[k][j];
			}
		}
	}
	return product;
}

int main(int argc, char *argv[]){
	int i,j,times,size;
	int **matrix,**product;
	FILE *fd;
	fd = fopen(argv[1],"r");
	fscanf(fd,"%d",&size);
	matrix = (int**)malloc(size*sizeof(int*));
        for(i=0;i<size;i++){
                matrix[i] = (int*)malloc(size*sizeof(int));
        }
        product = (int**)malloc(size*sizeof(int*));
        for(i=0;i<size;i++){
		product[i] = (int*)malloc(size*sizeof(int));
        }
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			fscanf(fd,"%d",&matrix[i][j]);	
		}
	}
	fscanf(fd,"%d",&times);
	product = multiply(matrix,matrix,size);
	while((times-2!=0)){
		product = multiply(matrix,product,size);
		times--;
	}			
	for(i=0;i<size;i++){
        	for(j=0;j<size;j++){
                        printf("%d\t",product[i][j]);
                }
		printf("\n");
        }
	printf("\n");
	free(matrix);
	free(product);
	fclose(fd);
	return 0;	
}
