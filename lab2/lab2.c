//Anish Katragadda
//Monday 2:15
//lab2

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



//global variables
int counter = 0;
char tasks[10][50];
int hours[10];
//functions
void insert(){
	char addtask[50];
    int addhour;
    if(counter == 10){
		printf("Schedule is Full\n");
	}
	else{
		printf("Please Type Your Task: \n");
        __fpurge(stdin);
        scanf ("%[^'\n']", addtask);
        printf("Please Enter The Hour between 0 - 23(24hr format): \n");
        scanf("%d", &addhour);
        while(addhour > 23 || addhour < 0){
            printf("Please Make Sure The Hour is between 0 and 23: \n");
            scanf("%d", &addhour);
        }
        strcpy(tasks[counter], addtask);
        hours[counter] = addhour;
		counter++;
	}
}

void list(){
    int i = 0;
    if (counter == 0)
    {
        printf("there is nothing scheduled");
    }else{
        for(i = 0; i < counter; i++){
		printf("%s, ", tasks[i]);
        printf("%d hrs\n", hours[i]);

        }
    }
    
   
}

void list_hour(){
    int temp;
    int i = 0;
    printf("What hour would you like to look at: \n");
    scanf("%d", &temp);
    for(i = 0; i < 10; i++){
        if (hours[i] == temp)
        {
            printf(" The tasks at %dhrs:  ", temp);
            printf("%s \n", tasks[i]);

        }
        
    }

}
//main
int main(void){

        int option;

        while(1){

                printf("MENU \n");
                printf("1 - Add a Task w/ Time \n");
                printf("2 - Shows the List of Tasks \n");
                printf("3 - List Tasks at a Certain Hour \n");
                printf("4 - To Quit \n");
                
                if (scanf("%d", &option) != 1){
                        printf("error\n");
                        return 0;
                }

                switch(option){

                        case 1:
                            insert();
                            break;
                        case 2:
                            printf("Tasks for the day\n");
                            list();
                            break;
                        case 3:
                            list_hour();
                            break;
                        case 4:
                            printf("You Have Quit \n");
                            return 0;
                        default:
                            printf("Wrong Option\n");

                }
        }
}