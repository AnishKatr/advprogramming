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
struct info{

    char tasks[50];
    int hours;
    int mins;

};
int counter = 0;

struct info infoholder[10];

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
            strcpy(infoholder[counter].tasks, addtask);
            infoholder[counter].hours = addhour;
            infoholder[counter].mins = addmin;
            counter++;
            int i, j;
            for(i = 1; i < counter; i++){
                int keyHour = infoholder[i].hours;
                int keyMin = infoholder[i].mins;
                char keyTask[50];
                strcpy(keyTask, infoholder[i].tasks);
                j = i-1;
                while(j >= 0 && (infoholder[j].hours > keyHour || (infoholder[j].hours == keyHour && infoholder[j].mins > keyMin))){
                    infoholder[j+1].hours = infoholder[j].hours;
                    infoholder[j+1].mins = infoholder[j].mins;
                    strcpy(infoholder[j+1].tasks, infoholder[j].tasks);
                    j--;
                }
                infoholder[j+1].hours = keyHour;
                infoholder[j+1].mins = keyMin;
                strcpy(infoholder[j+1].tasks, keyTask);
            }

			printf("Your Task Has Been Scheduled\n");
        }
	}
}

int check_duplicate(char addtask[50]){
    int i;
    for(i = 0; i < 10; i++){
					if(strcmp (infoholder[i].tasks, addtask) == 0){
						printf("Please Ty again the inputted task was already scheduled\n");
                        printf(" \n");
                        return 0;
                    }
        }
        return 1;
    }

void list(){
    int i = 0;
    //struct info *p = NULL;
    //p = infoholder;
    struct info *p= infoholder;
    if (counter == 0)
    {
        printf("there is nothing scheduled\n");
    }else{
        for(i = 0; i < counter; i++){
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
            p++;
        }
    }
    
   
}

void list_hour(){
    int temp;
    int i = 0;
    struct info *p= infoholder;
    printf("What hour would you like to look at: \n");
    scanf("%d", &temp);
    printf("The tasks at %dhrs:  \n", temp);
    for(i = 0; i < 10; i++){
        if (p->hours == temp)
        {
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
            p++;
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
			if (strcmp (infoholder[i].tasks, temp) == 0){
				for(j = i + 1; j < counter; j++){
                    strcpy(infoholder[j-1].tasks, infoholder[j].tasks);
                    infoholder[j-1].hours = infoholder[j].hours;
                    infoholder[j-1].mins = infoholder[j].mins;
				}
                printf("Task Cancelled : %s\n", temp);
				counter--;
				//infoholder[counter].tasks = '\0';
                //infoholder[counter].hours = '\0';
                //infoholder[counter].mins = '\0';
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
    struct info *p= infoholder;
    int i=0, j;
		for (i=0;i < counter && p->hours <= temp; i++, p++){
			if (p->hours == temp){
				for(j = i + 1; j < counter; j++){
                    //strcpy(infoholder[j-1].tasks, infoholder[j].tasks);
                    //infoholder[j-1].hours = infoholder[j].hours;
                    //infoholder[j-1].mins = infoholder[j].mins;
                    //break;
                    infoholder[j-1] = infoholder[j];
				}
                //printf("Task Cancelled : %d\n", temp);
				counter--;
                i--;
                p--;
				//infoholder[counter].tasks = '\0';
                //infoholder[counter].hours = '\0';
                //infoholder[counter].mins = '\0';
				hold++;
                printf("Tasks at %d, Removed\n", temp);
				//break;
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