#include <stdio.h>
#include <stdlib.h>


int main (int argc, char * argv[]){
	
	int i, counter= 1,total=0,total2=0;

	char c = argv[1][0];
	if(isalpha(c)==0){
		printf("error");
		return 0;
	}
	for(i = 1; argv[1][i] != '\0'; i++){
		if(c == argv[1][i]){
			counter++;
		}
		else{
			total2++;
		}
		total++;
	}
	if(total2>=total){
		printf("%s\n",argv[1]);
		return 0;
	}
	else{
		char c = argv[1][0];
		for(i = 1; argv[1][i] != '\0'; i++){
			if(c == argv[1][i]){
				counter++;
			}
			else{
				printf("%c%d",c,counter);
				counter =1;
				c = argv[1][i];
			}
		}
		printf("%c%d\n",c,counter);		
		return 0;
	}
}
