#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	//Declaring Variables
	int c = 0;
	int i = 0;
	int j = 0;
	int rubbish = 0;


	//If Console Input
	printf("Welcome to ASCII\n");
	if(argc > 1){
			for (i = 1; i < argc; i ++)
			{
		  		printf("----> %c\n", argv[i][0]);   
		  		printf("ascii: %d\n", argv[i][0]);   
			}
		printf("Done.\n");
		return 0;
	}


	//Without Console Input
	c = getchar();

	while(c != '0')
		{
		printf("ascii: %d\n", c);
                rubbish = getchar();
		c = getchar();
		}

	printf("Done.\n");
	return 0;

}
