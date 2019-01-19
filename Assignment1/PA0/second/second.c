#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]){
        int i, k, temp;
        int size=0;
        FILE *fd;

        fd = fopen(argv[1],"r");

        fscanf(fd,"%d",&size);
	int *buffer = malloc(sizeof(int)*size); //allocate memory the size of 4 * size

        for(i=0;i<size;i++){
                fscanf(fd, "%d", buffer+i);
	}
        for(k = 1; k <= (size-1); k++)
        {
                for(i = 0; i <= (size-2); i++)
                {
                        if(*(buffer + i) > *(buffer + i + 1))
                        {
                                temp = *(buffer + i);
                                *(buffer + i) = *(buffer + i + 1);
                                *(buffer + i + 1) = temp;
                        }
                }
        }

        for (i=0; i <= (size-1); i++)
                printf("%d\t", *(buffer+i));


        printf("\n");
	free(buffer);
        fclose(fd);
        return 0;
}

  
