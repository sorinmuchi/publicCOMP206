#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	//Variables
	char command[100];

	//Loop
	do {
		//Read user cmd line input
		printf(">> ");
		scanf("%[^\n]%*c", command);

		//Exit loop when user enters "done"; do NOT execute
		if(strcmp(command, "done") == 0) break; 
		//if(strcmp(command, "done ") == 0) break; 


		//Else, execute the user input, and display output
		system(command);
	}
	while(1);

	printf("Thank you for using mysh!\n");
}