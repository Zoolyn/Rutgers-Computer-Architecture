#include <stdio.h>
#include <stdlib.h>


//standard multiply function, returns matrix
double** multiply(double** mat1,double** mat2,int dimR1,int dimC1,int dimR2,int dimC2){
	double **product;
	int i,j,k;
	//memory allocation for product
	product = (double**)malloc(dimR1*sizeof(double*));
	for(i=0;i<dimR1;i++){
		product[i] = (double*)malloc(dimC2*sizeof(double));
	}
	for(i=0;i<dimR1;i++){
		for(j=0;j<dimC2;j++){
			product[i][j] = 0;
			for(k=0;k<dimC1;k++){
				product[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}
	return product;
}
//Creates "augmented matrix" and puieforms Gauss-Jordan elimination, returns a inversed matrix
double** inverse(double** matrix,int size){
	double **aug,**inv;
	int i,j,k,l;
	double temp;
	//memory allocation for aug
	aug = (double**)malloc(size*sizeof(double*));
	for(i=0;i<size;i++){
		aug[i] = (double*)malloc(size*sizeof(double));
	}
	//memory allocation for inv
	inv = (double**)malloc(size*sizeof(double*));
	for(i=0;i<size;i++){
		inv[i] = (double*)malloc(size*sizeof(double));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			aug[i][j] = matrix[i][j]; 
		}
	}
	//instead of creating a augmented matrix 
	//just use two matrix next to each other, to make it easier to extract the inverse
	//creating the identity matrix
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(i == j){
				inv[i][j] = 1.000000;	
			}
			else{
				inv[i][j] = 0.000000;
			}
		}
	}
	//start of the Gauss-Jordan Elimination
	//keep going until all the columns are done
	i=0;
	j=0;
	while(j != size){
		//checking if the diagonal value in that column is 1
		//printf("column: %d\n",j);
		if(aug[j][j] != 1.000000){
			//printf("change the diagonal value\n");
			temp = aug[j][j];
			//divides the rest of the row
			for(k=j;k<size;k++){
				aug[j][k] = aug[j][k]/temp;
			}
			//for the inverse matrix as well
			for(l=0;l<size;l++){
				inv[j][l] = inv[j][l]/temp;
			}
			//printf("diagonal: %lf\n",temp);
			//diagonal value is set
			//make sure the rest of the column is 0
			for(i=0;i<size;i++){
				if(aug[i][j] != 0.000000 && i != j){
					temp = aug[i][j];
					//set the rest of the row to 0
					for(k=j;k<size;k++){
						aug[i][k] = aug[i][k] - temp*aug[j][k];
					}
					//subtract inverse matrix rows
					for(l=0;l<size;l++){
						inv[i][l] = inv[i][l] - temp*inv[j][l];
					}
				}
			}
		}
		//if the diagonal value is already set
		//still need to check if everything else is 0
		else{
			//printf("value is already 1\n");
			for(i=0;i<size;i++){
				if(aug[i][j] != 0.000000 && i != j){
					temp = aug[i][j];
					for(k=j;k<size;k++){
						aug[i][k] = aug[i][k] - temp*aug[j][k];
					}
					for(l=0;l<size;l++){
						inv[i][l] = inv[i][l] - temp*inv[j][l];
					}
				}
			}
		}
		//advance j to the next column
		j++;
	}

//_________________________________________________________________________________
	/*
	printf("augment\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%lf ",aug[i][j]);
		}
		printf("\n");
	}
	printf("inverse\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%lf ",inv[i][j]);
		}
		printf("\n");
	}
	*/
	free(aug);
	return inv;
}

int main(int argc, char *argv[]){

	FILE *train,*test;
	int a,t,i,j,z;
	int counter = 0;
	double **price,**weight,**stuff,**stuff2,**transpose,**product,**product2,**inv,**final;
	train = fopen(argv[1],"r");
	test = fopen(argv[2],"r");
	if(train == NULL){
		printf("train file not found\n");
		return 0;
	}
	if(test == NULL){
		printf("test file not found\n");
		return 0;
	}
	//get the attribute and sizes from the first file
	fscanf(train, "%d",&a);
	//printf("%d\n",a);
	//get the number of examples
	fscanf(train, "%d",&t);
	//printf("%d\n",t);
	//number of rows = t
	//number of columns = (a+1)
	//memory allocation for attributes
	stuff = (double**)malloc(t*sizeof(double*));
	for(i=0;i<t;i++){
		stuff[i] = (double*)malloc((a+1)*sizeof(double));
	}
	//memory allocation for transpose
	transpose = (double**)malloc((a+1)*sizeof(double*));
	for(i=0;i<(a+1);i++){
		transpose[i] = (double*)malloc(t*sizeof(double));
	}
	//memory allocation for prices
	price = (double**)malloc(t*sizeof(double*));
	for(i=0;i<t;i++){
		price[i] = (double*)malloc(sizeof(double));	
	}
	//put values in stuff matrix
	for(i=0;i<t;i++){
		for(j=0;j<(a+1);j++){
			if(j == 0){
				stuff[i][j] = 1.000000;
			}
			else if(j == a){
				fscanf(train,"%lf,",&stuff[i][j]);
				fscanf(train,"%lf, ",&price[counter][0]);
				counter++;
			}
			else{
				fscanf(train,"%lf, ",&stuff[i][j]);
			}
		}
	}
	//transpose the stuff matrix
	for(i=0;i<t;i++){
		for(j=0;j<(a+1);j++){
			if(j != i){
				transpose[j][i] = stuff[i][j];
			}
			else{
				transpose[i][j] = stuff[i][j];
			}
		}
	}
	
	//multiply the transposed matrix by the original matrix
	//allocate memory for the product matrix
	product = (double**)malloc((a+1)*sizeof(double*));
	for(i=0;i<(a+1);i++){
		product[i] = (double*)malloc((a+1)*sizeof(double));
	}
	product = multiply(transpose,stuff,(a+1),t,t,(a+1));
	// you use dimR for both because when you multiply the stuff and transpose it gives you a square matrix
	//now that we have the product we need to apply Gauss-Jordan elimination
	//allocate memory for the inverse matrix
	inv = (double**)malloc((a+1)*sizeof(double*));
	for(i=0;i<(a+1);i++){
		inv[i] = (double*)malloc((a+1)*sizeof(double));
	}
	inv = inverse(product,(a+1));
	//now that we have to inverse we have to multiply inverse by transpose
	//memory allocation for the next product
	product2 = (double**)malloc((a+1)*sizeof(double*));
	for(i=0;i<(a+1);i++){
		product2[i] = (double*)malloc(t*sizeof(double));
	}
	product2 = multiply(inv,transpose,(a+1),(a+1),(a+1),t);
	//multiply the product by the price matrix to get the weight
	weight = (double**)malloc((a+1)*sizeof(double*));
	for(i=0;i<(a+1);i++){
		weight[i] = (double*)malloc(sizeof(double));
	}
	weight = multiply(product2,price,(a+1),t,t,1);
	

	fscanf(test,"%d",&z);
	//printf("number of tests: %d\n",z);
	stuff2 = (double**)malloc(z*sizeof(double*));
	for(i=0;i<z;i++){
		stuff2[i] = (double*)malloc((a+1)*sizeof(double));
	}
	for(i=0;i<z;i++){
		for(j=0;j<(a+1);j++){
			if(j == 0){
				stuff2[i][j] = 1.000000;
			}
			else{
				fscanf(test,"%lf,",&stuff2[i][j]);
			}
		}
	}
	//printf("stuff2 done\n");
	final = (double**)malloc(t*sizeof(double*));
	for(i=0;i<z;i++){
		final[i] = (double*)malloc(sizeof(double));
	}
	final = multiply(stuff2,weight,z,(a+1),(a+1),1);
	//printf("final\n");
	for(i=0;i<z;i++){
		for(j=0;j<1;j++){
			printf("%0.0f\n",final[i][j]);
		}
	}
//_______________________________________________________________________________________________________
	/*
	//print the attributes
	printf("attributes\n");	
	for(i=0;i<t;i++){
		for(j=0;j<(a+1);j++){
			printf("%lf ",stuff[i][j]);
		}
		printf("\n");
	}
	//print transpose matrix
	printf("transpose\n");
	for(i=0;i<(a+1);i++){
		for(j=0;j<t;j++){
			printf("%lf ",transpose[i][j]);
		}
		printf("\n");
	}
	//print first product
	printf("first product\n");
	for(i=0;i<(a+1);i++){
		for(j=0;j<(a+1);j++){
			printf("%lf ",product[i][j]);
		}
		printf("\n");
	}	
	//print the price
	printf("price\n");
	for(i=0;i<t;i++){
		for(j=0;j<1;j++){
			printf("%lf ",price[i][j]);
		}
		printf("\n");
	}
	*/
	free(stuff);
	free(transpose);
	free(product);
	free(product2);
	free(price);
	free(inv);
	free(weight);
	free(stuff2);
	free(final);
	fclose(train);
	fclose(test);
	return 0;
	

}
