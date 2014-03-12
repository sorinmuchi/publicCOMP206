//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Global pointer to file
FILE *input_file;
//Functions
int parse_cmdline(int argc, char* argv[]);
void list();
void reorder();
void deduct(char* element);
void add(char* element, int quantity, int minimum, double price);
void usage();
int mustReorder(char* record);
void printRecord(char* record);
int isOnRecord(char* element);


/************************************************
				MAIN FUNCTION
************************************************/
int main(int argc, char *argv[]){
	input_file = fopen("inventory.csv", "r");
	//Need to test if file exists && is not corrupted
	return parse_cmdline(argc, argv);
	fclose (input_file);

}





/************************************************
			REQUIRED HELPER METHODS
************************************************/

void list(){ //OK
	//Print Header
	printf("\tITEM\tQTY\tREORDER PRICE\n");
	char record[100];
	while(fgets(record, 100, input_file) != NULL){
		printRecord(record);
	}
	printf("\n");
}

void reorder(){ //OK
	//Print Header
	printf("\tMUST PURCHASE THE FOLLOWING ITEMS\n");
	printf("\tITEM\tQTY\tREORDER PRICE\n");
	//Read File
	char record[100];
	char recordCopy[100];
	while(fgets(record, 100, input_file) != NULL){
		strcpy(recordCopy, record);
		if(mustReorder(record)){
			printRecord(recordCopy);
		}
	}
	printf("\n");
}

void deduct(char *element){
	if(isOnRecord(element)){
		input_file = fopen("inventory.csv", "r+");
		char record[100];
		char *field;
		char *newRecord;
		int quantity;
		int minimum;
		double price;

		//Making of command for system call
		//To delete record containing element
		// in case element is found
		char command[100];
		strcpy(command, "sed -i '/");
		strcat(command, element);
		strcat(command, "/d' inventory.csv");

		while(fgets(record, 100, input_file) != NULL){
			if (strstr(record, element) != NULL)
			{
				field = strtok(record, ",");
				quantity = atoi(strtok('\0', ","));
				minimum = atoi(strtok('\0', ","));
				price = strtof(strtok('\0', ","), NULL);
				//Remove Whole Record with system call
				system(command);
				//Add New Record with lower quantity
				add(element, quantity-1, minimum, price);
			}
		}
	}
	else{
		printf("Element %s does not exist in the database.\n", element);
	}
}

void add(char* element, int quantity, int minimum, double price){ //OK
	if(isOnRecord(element)){
		printf("Element %s has already been added to you inventory.\n", element);
	}
	else{
		FILE *pappend;
		pappend = fopen("inventory.csv", "a");
		fprintf(pappend, "%s,%d,%d,%.2f\n", element, quantity, minimum, price);
		fclose(pappend);
	}
}




/************************************************
				OPTIONAL HELPER FUNCTIONS
************************************************/

//Parse User Arguments
//Error Handling
//Call Corresponding Functions
int parse_cmdline(int argc, char* argv[]){ //OK
	if (argc == 1){
		usage();
		return (1);
	}
	//Cases: reading command argument
	if(strcmp(argv[1],"list") == 0){
		list();
	}
	else if(strcmp(argv[1], "reorder") == 0){
		reorder();
	}
	else if(strcmp(argv[1], "deduct") == 0 && argc == 3){
		char *element = argv[2];
		deduct(element);
	}
	else if(strcmp(argv[1], "add") == 0 && argc == 6){
		char *element = argv[2];
		int quantity = atoi(argv[3]);
		int minimum = atoi(argv[4]);
		double price = strtod(argv[5], NULL);
		//Type check arguments, atoi()/atof() returns 0 if input is not a number
		if(quantity == 0 || minimum == 0 || price == 0.0){
			usage();
			return 1;
		}
		//User data is safe, add to file
		add(element, quantity, minimum, price);
		//printf("%s was successfully added to your inventory\n", element);
	}
	else{
		usage();
	}
}


int mustReorder(char* record){
	//Parsing The Record, Storing Info
	char* field = strtok(record, ",");
	int quantity = atoi(strtok('\0', ","));
	int minimum = atoi(strtok('\0', ","));
	int junk = strtof(strtok('\0', ","), NULL);
	//Test if must reorder
	return (quantity <= minimum);
}

void printRecord(char* record){
	char* field = strtok(record, ",");
	while(field != NULL){
		printf("\t%.7s", field); //Truncate string for displaying consistency
		field = strtok('\0', ",");
	}
}

int isOnRecord(char* element){
	char record[100];
	int found = 0;

	while(fgets(record, 100, input_file) != NULL){
		if(strstr(record,element)){
			char *field = strtok(record, ",");
			if(strcmp(field, element) == 0){
				//printf("%s\n", field);
				found = 1;
			}
		}
	}
	return found;
}

//Print Program Usage
void usage(){
	printf("USAGE: ./inv COMMAND [ARGUMENTS]\n");
	printf("COMMANDS: list, reorder, deduct, add\n");
	printf("EXEMPLE:\n");
	printf("\t./inv add product_name quantity_in_stock reorder_limit_number unit_cost \n");
	printf("\t./inv deduct product_name\n");
	printf("\t./inv reorder\n");
	printf("\t./inv list\n");
	printf("ATTENTION: 0 is NOT a valid argument\n");
}