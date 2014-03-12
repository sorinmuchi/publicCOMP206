#include <string.h>
#include <stdio.h>


//Global Variable
int numExperiments = 0;
void displayAll(char *experiments[20], int data[10][20]);
double individualAverage(char *selectedExperiment, char *experiments[20], int data[10][20]);
double allAverage(int data[10][20]);


int main(){
    /************************************************
                    Read Redirected Input
    ************************************************/
    char *experiments[20];
    int data[10][20];
    char line[100];
    int i = 0; //Used in production code, do not remove.


    do{
        //Read first line -- Experiment Name
        scanf("%[^\n]\n", line);
        //Test for ***END***
        if(strstr(line, "*** END ***") != NULL) break; 
        //Store experiment name in experiments array
        experiments[numExperiments] = strdup(line);



        //Read second line -- Experiment Results
        scanf("%[^\n]\n", line);
        //Tokenize each element of the Results line, chnage to integer and store in data array;
        char *p = strtok(line, " ");
        for(i=0; i < 10; i++){
            data[i][numExperiments]=atoi(p);
            p = strtok(NULL, " ");

            //Error handling if no of datapoints <10
            if (p == NULL && i <9){ 
                printf("\nERROR: Incorrect Data, in experiment no. %d: %s\n",numExperiments+1, experiments[numExperiments]);
                printf("Please Retry\n");
                return 1;
            } 

            //If no of datapoints > 10, only first 10 will be read
        }

        //counting
        numExperiments++; 
    }
    while (numExperiments<=20);
    //All redirected content has been read and stored.
    //Reset stdin < keyboard input
    freopen("/dev/tty", "rw", stdin);
   


/************************************************
=========>>>>>>      MENU    <<<<<<============
************************************************/
    //Display menu
    printf("DATA SET ANALYSIS\n");
    printf("1. Show all the data\n");
    printf("2. Calculate the average for an experiment\n");
    printf("3. Calculate the average across all experiments\n");
    printf("4. Quit\n\n");

    //Read user choice
    int choice = 0;
    printf("Selection:");
    scanf("%d", &choice);

    //Loop to display the menu until user quits
    while(choice != 4){
        switch (choice){
            case 1:
                displayAll(experiments, data);
                break;
            case 2:
                printf("Please Select The Experiment You Want\n");
                char junk = getchar(); //Fush stdin
                printf(">> ");
                char selectedExperiment[100] = "\0";
                scanf("%[^\n]%*c", selectedExperiment);
                double average = individualAverage(selectedExperiment, experiments, data);
                if (average==0.000000) {printf("Incorrect Experiment Name. or Avg=0"); break;} //Error Handling
                printf("Experiment average = ");
                printf("%f\n", average);
                break;
            case 3:
                printf("Overall average = %f\n", allAverage(data));
                break;
            default:
                printf("Please Select a Valid Option 1-4\n");
        }

        printf("\nSelection:");
        scanf("%d", &choice);
    }
     

    return 0;
}













/************************************************
            Required Helper Methods
************************************************/

void displayAll(char *experiments[20], int data[10][20]){
    int i = 0; //Line Counter
    int j = 0; //Column Counter for Data
    for(i = 0; i < numExperiments; i++){
        printf("%s\n", experiments[i]);
        for(j=0; j<10;j++){
            printf("%d ", data[j][i]);
        }
        printf("\n");
    }
}

double individualAverage(char *selectedExperiment, char *experiments[20], int data[10][20]){
    int i = 0;
    int j = 0;
    int sum = 0;
    for (i=0; i<numExperiments; i++){
        if (strcmp(experiments[i], selectedExperiment) == 0) {
            for (j = 0; j < 10; ++j)
            {
                sum += data[j][i];
            }
            break;
        }
    }
    return (double)sum / 10; //Return individualAverage of the specified experiment
}

double allAverage(int data[10][20]){
    int i = 0; //Line Counter
    int j = 0; //Column Counter for Data
    int sum = 0;
    double average;
    for(i = 0; i < numExperiments; i++){
        for(j=0; j<10;j++){
            sum += data[j][i];
        }
    }
    return average = (double)sum / (double)(numExperiments * 10);
}