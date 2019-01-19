#include <stdlib.h>
#include <stdio.h>

typedef struct node{
	int data;
	struct node* left; //left child
	struct node* right; //right child
}node;
void insert(node **root, int data){
	int height = 1;
	
	if(*root == NULL){//this is for the first node being entered

		node* newNode = (node*)malloc(sizeof(node));
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		*root = newNode;
		printf("inserted: %d\n",height);
		return;
	}
	else{
		node* ptr = *root;
		node* prev = NULL;
		while(ptr!=NULL){
			prev = ptr;
			if(ptr->data == data){//case of duplicate
				printf("duplicate\n");
				return;
				
			}
			else if(ptr->data > data){
				ptr = ptr->left;
				height++;
				if(ptr == NULL){//there is no node
					node* newNode = (node*)malloc(sizeof(node));
					newNode->data = data;
					newNode->left = NULL;
					newNode->right = NULL;
					prev->left = newNode;
					printf("inserted: %d\n",height);
					return;
					//node is inserted
				}
			}
			else{//ptr->data < newNode->data
				ptr = ptr->right;
				height++;
				if(ptr == NULL){
					node* newNode = (node*)malloc(sizeof(node));
					newNode->data = data;
					newNode->left = NULL;
					newNode->right = NULL;
					prev->right = newNode;
					printf("inserted: %d\n",height);
					height++;
					return;
					//node is inserted
				}
			}
			
		}
	}
	
}
void search(node **root, int data){
	int height = 1;
	node *ptr = *root;
	while(ptr!=NULL){
		if(ptr->data==data){
			printf("present: %d\n",height);
			return;
		}
		else if(ptr->data<data){
			ptr = ptr->right;
			height++;
		}
		else{
			ptr = ptr->left;
			height++;
		}
	}
	//if the node is not in the tree
	printf("absent\n");
}
void freeAll(node* root){
	if(root != NULL){
	freeAll(root->left);
	freeAll(root->right);
	free(root);
	}
}
int main(int argc, char **argv){


	node* root = NULL;
	FILE *fd;
	char c, mode;
	int i;
	

	fd = fopen(argv[1], "r");
	mode = fscanf(fd, "%c %d\n",&c, &i);
	while(mode == 2){// returns the correct number of arguments
		if(c == 'i'){
			//creating the new node
			insert(&root, i);
			
		}
		else if(c == 's'){
			search(&root, i);
		}
		else{
			printf("error\n");
		}
		mode = fscanf(fd, "%c %d\n", &c, &i);
	}
	freeAll(root);
	fclose(fd);
	return 0;	
}



