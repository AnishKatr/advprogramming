//Anish Katragadda
//Monday 2:15
//lab8

//includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INFO struct info

//Creating Union
typedef union{

float budget;
char location[50];
int endtime[2];

}EXTRA_INFO;

//Creating Structs
struct info{

    char tasks[50];
    int priority;
    int hours;
    int mins;
    EXTRA_INFO information;
    struct info *next;
};

//prototypes
int check_duplicate(char addtask[50]);
void insert(struct info);
void list();
void list_hour();
void deleter();
void save(char argv[]);
void clear();
void read(char argv[]);
void prompt();

//array of heads
struct info *heads[3] = {NULL, NULL, NULL};

//main had to move main to top since it was not compiling otherwise
int main(int argc, char *argv[]){

        if(argc == 1){
                printf("The name of the file isn't there\n");
                return 1;
        }
        read(argv[1]);
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
                            prompt();
                            //insert(INFO);
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
                            save(argv[1]);
                            clear();
                            printf("You Have Quit \n");
                            return 0;
                        default:
                            printf("Wrong Option\n");

                }
        }
}

//INFO *tail = NULL;

void prompt(){

    struct info data;

    printf("Please Type Your Task: \n");
    fpurge(stdin);
    scanf ("%[^'\n']", data.tasks);
    printf("Please Enter The Hour between 0 - 23(24hr format): \n");
    scanf("%d", &data.hours);
    while(data.hours > 23 || data.hours < 0){
        printf("Please Make Sure The Hour is between 0 and 23: \n");
        scanf("%d", &data.hours);
    }
    printf("Please Enter The Minutes between 0 - 59 minutes: \n");
    scanf("%d", &data.mins);
    while(data.mins > 59 || data.mins < 0){
        printf("Please Make Sure The Minutes are between 0 and 59: \n");
        scanf("%d", &data.mins);
    }

    
    if(check_duplicate(data.tasks) == 1){
        if(data.hours < 12){
            printf("Please Enter Your budget for this task\n");
            scanf("%f", &data.information.budget);
        }else if(data.hours <= 20 && data.hours >= 12){
            printf("Please Enter Your location for this task\n");
            fpurge(stdin);
            scanf ("%[^'\n\']", data.information.location);  
        }else{
            printf("Please Enter the endtime by hours for this task\n");
            scanf("%d", &data.information.endtime[0]);
            printf("Please Enter the endtime by minute for this task\n");
            scanf("%d", &data.information.endtime[1]);
        }
        
    }
    insert(data);
}

//functions
void insert(struct info data){

    //INFO info;
    struct info *p;
    struct info *q;
    struct info *temp;
    int pos;      
    pos = data.priority - 1;
    p = (struct info *)malloc(sizeof(struct info));
    *p = data;
    temp = q = heads[pos];
    while(q != NULL){
        
        if(q -> hours == p-> hours){
                if(q -> mins > p -> mins){
                    break;
                }
        }else if(q -> hours > p -> hours){
            break;
        }
        temp = q;
        q = q -> next;

    }

    if ( q == heads[pos]){
        p -> next = heads[pos];
        heads[pos] = p;
    }else{
        p -> next = q;
        temp -> next = p;
    }

    printf("Your Task Has Been Scheduled\n");
 }


int check_duplicate(char addtask[50]){
    struct info *p;
    int i = 0;
    for ( i = 0; i < 3; i++){
        p = heads[i];
        while(p != NULL){
            if(strcmp(p->tasks, addtask)==0){
                printf("Please Ty again the inputted task was already scheduled\n");
                printf(" \n");
                return 0;
            }
            p = p->next;
        }

    }
    
    return 1;
}

void list(){
    struct info *p;
    int i = 0;
    for( i = 0; i < 3; i++){
        p = heads[i];
        if(heads[i] == NULL){
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

    
   
}

void list_hour(){
    struct info *p;
    int i = 0;
    for( i = 0; i < 3; i++){
        p = heads[i];
        if(heads[i] == NULL){
            printf("schedule is empty\n");
            return;
        }
        int temp;
        printf("What hour would you like to look at: \n");
        scanf("%d", &temp);
        printf("The tasks at %dhrs:  \n", temp);
        while(p != NULL){
            if (p -> hours == temp){
                printf("Task: %s ,and the time scheduled is: %d:%02d \n", p -> tasks, p -> hours, p -> mins);
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


}

void deleter(){
    struct info *p;
    struct info *q;
    char temp[50];
    int i = 0;
    printf("What Task would you like to remove \n");
    scanf("%s", temp);
    
    for( i = 0; i < 3; i++){
        p = heads[i];
        if(heads[i] == NULL){
            printf("The Schedule is empty\n");
            return;
        }

        while(p != NULL){
            if(strcmp(p->tasks, temp)==0){
                break;
            }
            q = p;
            p = p -> next;
        }

        if(p == heads[i]){
            heads[i] = p -> next;
        }else{
            q -> next =p -> next;
        }
        free(p);
    }

}


void save(char argv[]){
    FILE *outfp;
    struct info *p;
    int i = 0;
    
    for( i = 0; i < 3; i++){
        outfp = fopen(argv, "w");
        if((outfp = fopen(argv, "w")) == NULL){
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
    }
    fclose(outfp);
    return;

}

void clear(){
    struct info *p;
    struct info *q;
    int i = 0;
    for( i = 0; i < 3; i++){
        while(p != NULL){
            p = heads[i];
            q = heads[i];
            q = p;
            free(q);
            p = p -> next;
        
        }
    }
    
    return;
}

void read(char argv[]){

    FILE *fp;
    struct info data;
    int i = 0;
    fp = fopen(argv, "r");
    if( fp == NULL){
        printf("Couldn't Open File");
        return;
    }
    
    while((fscanf(fp, "%s", data.tasks)) == 1){
            fscanf(fp, "%d", &data.priority);
            fscanf(fp, "%d", &data.hours);
            fscanf(fp, "%d", &data.mins);
            if(data.hours > 0 && data.hours < 12){
                fscanf(fp, "%f", &data.information.budget);
            }
            if(data.hours>=12 && data.hours<=20){
                fscanf(fp, "%s", data.information.location);
            }else if(data.hours >20 && data.hours < 24){
                fscanf(fp, "%d%d", &data.information.endtime[0], &data.information.endtime[1]);
                
            }
            insert(data);
    }
    fclose(fp);
    

}

//main
// int main(int argc, char *argv[]){

//         if(argc == 1){
//                 printf("The name of the file isn't there\n");
//                 return 1;
//         }
//         read(argv[1]);
//         int option;
//         char task[10][50] = {0};
//         while(1){

//                 printf("MENU \n");
//                 printf("1 - Add a Task w/ Time \n");
//                 printf("2 - Shows the List of Tasks \n");
//                 printf("3 - List Tasks at a Certain Hour \n");
//                 printf("4 - Delete a Specific task from the Schedule\n");
//                 printf("0 - To Quit \n");
                
//                 if (scanf("%d", &option) != 1){
//                         printf("error\n");
//                         return 0;
//                 }

//                 switch(option){

//                         case 1:
//                             //prompt();
//                             insert();
//                             break;
//                         case 2:
//                             printf("Tasks for the day\n");
//                             list();
//                             break;
//                         case 3:
//                             list_hour();
//                             break;
//                         case 4:
//                             deleter();
//                             break;
//                         case 0:
//                             save();
//                             clear();
//                             printf("You Have Quit \n");
//                             return 0;
//                         default:
//                             printf("Wrong Option\n");

//                 }
//         }
// }