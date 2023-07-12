//Anish Katragadda
//Monday 2:15
//lab4

// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//prototypes
int check_duplicate(char addtask[50]);

//global variables

int counter = 0;
char tasks[10][50];
int hours[10];
int mins[10];

//functions
void insert(){
	char addtask[50];
    int addhour;
    int addmin;
    if(counter == 10){
		printf("Schedule is Full\n");
	}
	else{
		printf("Please Type Your Task: \n");
        fpurge(stdin);
        scanf ("%[^'\n']", addtask);
        printf("Please Enter The Hour between 0 - 23(24hr format): \n");
        scanf("%d", &addhour);
        while(addhour > 23 || addhour < 0){
            printf("Please Make Sure The Hour is between 0 and 23: \n");
            scanf("%d", &addhour);
        }
        printf("Please Enter The Minutes between 0 - 59 minutes: \n");
        scanf("%d", &addmin);
        while(addmin > 59 || addmin < 0){
            printf("Please Make Sure The Minutes are between 0 and 59: \n");
            scanf("%d", &addmin);
        }


        if(check_duplicate(addtask) == 1){
            strcpy(tasks[counter], addtask);
            hours[counter] = addhour;
            mins[counter] = addmin;
            counter++;
            int i, j;
            for(i = 1; i < counter; i++){
                int keyHour = hours[i];
                int keyMin = mins[i];
                char keyTask[50];
                strcpy(keyTask, tasks[i]);
                j = i-1;
                while(j >= 0 && (hours[j] > keyHour || (hours[j] == keyHour && mins[j] > keyMin))){
                    hours[j+1] = hours[j];
                    mins[j+1] = mins[j];
                    strcpy(tasks[j+1], tasks[j]);
                    j--;
                }
                hours[j+1] = keyHour;
                mins[j+1] = keyMin;
                strcpy(tasks[j+1], keyTask);
            }

			printf("Your Task Has Been Scheduled\n");
        }
	}
}

int check_duplicate(char addtask[50]){
    int i;
    for(i = 0; i < 10; i++){
					if(strcmp (tasks[i], addtask) == 0){
						printf("Please Ty again the inputted task was already scheduled\n");
                        printf(" \n");
                        return 0;
                    }
        }
        return 1;
    }



void list(){
    int i = 0;
    if (counter == 0)
    {
        printf("there is nothing scheduled\n");
    }else{
        for(i = 0; i < counter; i++){
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", tasks[i], hours[i], mins[i]);
        }
    }
    
   
}

void list_hour(){
    int temp;
    int i = 0;
    printf("What hour would you like to look at: \n");
    scanf("%d", &temp);
    printf("The tasks at %dhrs:  \n", temp);
    for(i = 0; i < 10; i++){
        if (hours[i] == temp)
        {
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", tasks[i], temp, mins[i]);

        }
        
    }

}
void deleter(){
    char temp[50];
    printf("Which task would you like to delete \n");
    fpurge(stdin);
	scanf("%[^'\n']", temp);
	int hold = 0;
    int i, j;
		for (i = 0; i < 10; i++){
			if (strcmp (tasks[i], temp) == 0){
				for(j = i + 1; j < counter; j++){
                    strcpy(tasks[j - 1], tasks[j]);
                    hours[j - 1] = hours[j];
                    mins[j - 1] = mins[j];
				}
                printf("Task Cancelled : %s\n", temp);
				counter--;
				tasks[counter][0] = '\0';
                hours[counter] = '\0';
                mins[counter] = '\0';
				hold++;
				break;
			}
		}		
		if(hold == 0){
			
			printf("Task Not Found \n");
			hold = 0;

		}
}

void delete_hour(){
    int temp;
    printf("Which Hour Would You like to Delete \n");
    fpurge(stdin);
	scanf("%d", &temp);
	int hold = 0;
    int i, j;
		while (hold < counter){
			if (hours[i] == temp){
				for(j = i + 1; j < counter; j++){
                    strcpy(tasks[j - 1], tasks[j]);
                    hours[j - 1] = hours[j];
                    mins[j - 1] = mins[j];
                    break;
				}
                //printf("Task Cancelled : %d\n", temp);
				counter--;
				tasks[counter][0] = '\0';
                hours[counter] = '\0';
                mins[counter] = '\0';
				hold++;
                printf("Tasks at %d, Removed\n", temp);
				//break;
			}else{
            if(hours[i] > temp){
                printf("Task removal at hour %d\n", temp);
                break;
            }
        }
		}		
		if(hold == 0){
			
			printf("No Tasks at that Hour \n");
			hold = 0;

		}
}

//main
int main(void){

        int option;
        counter = 0;
        char task[10][50] = {0};
        while(1){

                printf("MENU \n");
                printf("1 - Add a Task w/ Time \n");
                printf("2 - Shows the List of Tasks \n");
                printf("3 - List Tasks at a Certain Hour \n");
                printf("4 - Type a task you would like to delete from the schedule\n");
                printf("5 - Enter an Hour where you would like to delete tasks\n");
                printf("9 - To Quit \n");
                
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
                            deleter();
                            break;
                        case 5:
                            delete_hour();
                            break;
                        case 9:
                            printf("You Have Quit \n");
                            return 0;
                        default:
                            printf("Wrong Option\n");

                }
        }
}