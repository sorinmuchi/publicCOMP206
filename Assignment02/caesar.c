#include <stdio.h>
#include <ctype.h>

main(){ //Declaring variables
	int i=0;
	int shift;
	int diff;
	//Taking input
	printf("Sentence: ");

	char string[101];
	fgets( string, sizeof string, stdin );
	string[100]='\n';
	
	printf("Number: ");
	scanf("%d", &shift);

	//Operating on imput
	//Loop through character array, until end of string ('\0') is reached
	while (string[i]!='\0')
	{
		//Ignore all non alphabetical values
		if (!isalpha(string[i])){ 
			i++;	
			continue;
		}
		//Take care of lowercase
		if(islower(string[i])){ 
			diff = string[i] - 'a' + shift;
			if(diff >= 0){
				string[i]= diff %26 + 'a';
			}
			else {
				diff = 26 - (-1*diff)%26;
				string[i]= diff %26 + 'a';
			}
		}
		//Take care of uppercase
		if(isupper(string[i])){
			diff = string[i] - 'A' + shift;
			if(diff >= 0){
				string[i]= diff %26 + 'A';
			}
			else {
				diff = 26 - (-1*diff)%26;
				string[i]= diff %26 + 'A';
			}
	
		}
		i++;	
	}

	printf("Cipher: %s\n", string);
	printf("Done.");

}
