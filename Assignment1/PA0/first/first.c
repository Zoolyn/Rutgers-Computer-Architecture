
//	Create Linked Listthat maintains a list of integers in sorted order
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node* next;
}node;

void insert(node** front, node* newNode){
	node *ptr;
	ptr = *front;
	if(*front == NULL){
		newNode->next = *front;
		*front = newNode;
	}
	else if(newNode->data == ptr->data){
		free(newNode);
	}
	else if((*front)->data > newNode->data){
		newNode->next = *front;
		*front = newNode;
	}
	else{
		while(ptr->next!=NULL && ptr->next->data < newNode->data){
			ptr = ptr->next;
		}
		newNode->next = ptr->next;
		ptr->next = newNode;
	}
}
	
void delete(node* front, int data){
	
	node* ptr = front;
	node* temp;
	if(front == NULL){
		return;
	}
	if(front->data == data){
		front->data = front->next->data;
		temp = front->next;
		front->next = front->next->next;
		free(temp);
		return;
	}
        while(ptr->next!=NULL && ptr->next->data != data){
                ptr = ptr->next;
        }
	if(ptr->next == NULL){
		return ;
	}
	else{
		temp = ptr->next;
		ptr->next = ptr->next->next;
		free(temp);
		return;
	}
	

}

void freeLL(node* front){
	
	node* ptr;
	while(front!=NULL){
		ptr = front;
		front = front->next;
		free(ptr);		
	}
	return;
}

int main (int argc, char *argv[]){
	
	int i, counter=0;
	char c;
	node *front;
	FILE *fd;
	fd = fopen(argv[1], "r");
	if(fd == NULL){
		printf("error\n");
		return 0;
	}
	int a = fscanf(fd,"%c %d\n",&c, &i);
	while(a == 2){
		if(c == 'i'){
			node *newNode = (node*) malloc(sizeof(node));
			newNode->data = i;
			newNode->next = NULL;
			insert(&front,newNode);	
		}
		else if(c == 'd'){
			delete(front,i);
		}
		else{
			printf("error\n");
			break;
		}
		a = fscanf(fd, "%c %d\n", &c, &i);
	}
	
	node* ptr = front;
	while(ptr!=NULL){
		counter++;
		ptr = ptr->next;
	}
	printf("%d\n",counter);
	ptr = front;
	while(ptr!=NULL){
		printf("%d\t",ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	freeLL(front);
	fclose(fd);
	return 0;
	
}
