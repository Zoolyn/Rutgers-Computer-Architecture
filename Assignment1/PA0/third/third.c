#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	node *next; 
}node;

typedef struct hashtable{
	int bucketsize;
	struct **table;
}hashtable;

void insert(hashtable *table, int key){

}

void search(hashtable *table, int value){

}

int main(int argc, char **argv){
	FILE *fd = fopen(argv[1], "r");
	char c;
	int i,check;
	
	hashtable *table = (hashtable*)malloc(sizeof(hashtable));
	table->bucketsize = 10000;
	table->**table = malloc(sizeof(node*)*10000);
	for(i=0;i<10000;i++){
		table->**table[i] = NULL;
	}
	

	check = fscanf(fd,"%c %d\n",&c, &i);
	while(check == 2){
		if(c == 'i'){
			insert(table,i);	
		}
		else if(c == 's'){
			search(table,i);
		}
		else{
			printf("error\n");
			return 0;
		}	
	}
	return 0;
}
