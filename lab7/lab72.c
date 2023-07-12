//Anish Katragadda
//Monday 2:15
//lab7

//includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INFO struct info

//prototypes
int check_duplicate(char addtask[50]);

//Creating Union
typedef union{

float budget;
char location[50];
int endtime[2];

}EXTRA_INFO;

//Creating Structs
struct info{

    char tasks[50];
    int hours;
    int mins;
    EXTRA_INFO information;
    INFO *next;
};

INFO *head = NULL;
//INFO *tail = NULL;

//functions
void insert(){

    INFO info;
    INFO *p;
    INFO *q;
    INFO *temp;

		printf("Please Type Your Task: \n");
        fpurge(stdin);
        scanf ("%[^'\n']", info.tasks);
        printf("Please Enter The Hour between 0 - 23(24hr format): \n");
        scanf("%d", &info.hours);
        while(info.hours > 23 || info.hours < 0){
            printf("Please Make Sure The Hour is between 0 and 23: \n");
            scanf("%d", &info.hours);
        }
        printf("Please Enter The Minutes between 0 - 59 minutes: \n");
        scanf("%d", &info.mins);
        while(info.mins > 59 || info.mins < 0){
            printf("Please Make Sure The Minutes are between 0 and 59: \n");
            scanf("%d", &info.mins);
        }

       
        if(check_duplicate(info.tasks) == 1){
            if(info.hours < 12){
                printf("Please Enter Your budget for this task\n");
                scanf("%f", &info.information.budget);
            }else if(info.hours <= 20 && info.hours >= 12){
                printf("Please Enter Your location for this task\n");
                fpurge(stdin);
                scanf ("%[^'\n\']", info.information.location);  
            }else{
                printf("Please Enter the endtime by hours for this task\n");
                scanf("%d", &info.information.endtime[0]);
                printf("Please Enter the endtime by minute for this task\n");
                scanf("%d", &info.information.endtime[1]);
            }
            
            p = (INFO *)malloc(sizeof(INFO));
            *p = info;
            temp = q = head;
            while(q != NULL){
                
                    if (q -> hours == info.hours){
                        if(q-> mins > info.mins){
                            break;
                        }
                
                    }else if(q -> hours > info.hours){
                        break;
                    }
                    temp = q;
                    q = q -> next; 
            }
            if(q == head){
                p -> next = head;
                head = p;
            }else{
                p -> next = q;
                temp -> next = p;
                
            }

			printf("Your Task Has Been Scheduled\n");
        }

}

int check_duplicate(char addtask[50]){
    INFO *p;
    p = head;
    while(p != NULL){
        if(strcmp(p->tasks, addtask)==0){
            printf("Please Ty again the inputted task was already scheduled\n");
            printf(" \n");
            return 0;
        }
        p = p->next;
    }
    return 1;
}

void list(){
    INFO *p;
    p = head;
    if(head == NULL){
        printf("schedule is empty\n");
        return;
    }
    while(p != NULL){
        
        printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
        if(p -> hours > 0 && p -> hours < 12){
            printf("The Budget is: %.2f \n", p->information.budget);
        }
        if(p->hours>=12 && p->hours<=20){
            printf("location is: %s \n", p->information.location);
        }else if(p -> hours >20 && p -> hours < 24){
            printf("The endtime for this task is: %d:%02d\n", p-> information.endtime[0], p-> information.endtime[1]);
        }
         p = p->next;
        
    }
    
   
}

void list_hour(){
    INFO *p;
    p = head;
    if(head == NULL){
        printf("schedule is empty\n");
        return;
    }
    int temp;
    printf("What hour would you like to look at: \n");
    scanf("%d", &temp);
    printf("The tasks at %dhrs:  \n", temp);
    while(p != NULL){
        if (p->hours == temp){
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
            if(p -> hours > 0 && p -> hours < 12){
                printf("The Budget is: %.2f \n", p->information.budget);
            }
            if(p->hours>=12 && p->hours<=20){
                printf("location is: %s \n", p->information.location);
            }else if(p -> hours >20 && p -> hours < 24){
                printf("The endtime for this task is: %d:%02d\n", p-> information.endtime[0], p-> information.endtime[1]);
            }
        }
        p = p->next;
        
    }

}

void deleter(){
    INFO *p;
    INFO *q;
    p = head;
    char temp[50];

    printf("What Task would you like to remove \n");
    scanf("%s", temp);
    
    if(head == NULL){
        printf("The Schedule is empty\n");
        return;
    }

    while(p != NULL){
        if(strcmp(p->tasks, temp)==0){
            break;
        }
        q = p;
        p = p-> next;
    }
    if(p == head){
        head = p-> next;
    }else{
        q -> next =p -> next;
    }
    free(p);
}


void save(){
    FILE *outfp;
    INFO *p;
    p = head;
    outfp = fopen("data.txt", "w");
    if((outfp = fopen("data.txt", "w")) == NULL){
        printf("cannot open the file\n");
    }

    while( p!= NULL){
        if(p -> hours > 0 && p -> hours < 12){
            fprintf(outfp, "%s, %d:%2d, %.2f\n", p->tasks, p->hours ,p->mins, p->information.budget);
        }
        if(p->hours>=12 && p->hours<=20){
            fprintf(outfp, "%s, %d:%2d, %s\n", p->tasks, p->hours ,p->mins, p->information.location);
        }else if(p -> hours >20 && p -> hours < 24){
            fprintf(outfp, "%s, %d:%2d, %d:%2d\n", p->tasks, p->hours ,p->mins, p->information.endtime[0], p->information.endtime[1]);
        }
        p = p -> next;
    }
    fclose(outfp);
    return;

}

void clear(){
    INFO *p;
    INFO *q;
    p = head;
    q = head;
    while(p != NULL){
        q = p;
        p = p -> next;
        free(q);
    }
    return;
}


//main
int main(void){

        int option;
        char task[10][50] = {0};
        while(1){

                printf("MENU \n");
                printf("1 - Add a Task w/ Time \n");
                printf("2 - Shows the List of Tasks \n");
                printf("3 - List Tasks at a Certain Hour \n");
                printf("4 - Delete a Specific task from the Schedule\n");
                printf("0 - To Quit \n");
                
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
                        case 0:
                            save();
                            clear();
                            printf("You Have Quit \n");
                            return 0;
                        default:
                            printf("Wrong Option\n");

                }
        }
}