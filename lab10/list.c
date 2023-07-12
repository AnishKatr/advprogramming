#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void prompt(){

    struct info data;

    printf("Please Type Your Task: \n");
    fpurge(stdin);
    scanf ("%[^'\n']", data.tasks);
    printf("Please Enter A Priority Level between 1 and 3 \n");
    scanf("%d", &data.priority);
    while(data.priority > 3 || data.priority < 1){
        printf("Please Make Sure The Priority Level is between 1 and 3: \n");
        scanf("%d", &data.priority);
    }
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
        
    }else{
        return;
    }
    insert(data);
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
    int i;
    for( i = 0; i < 3; i++){
        p = heads[i];
        while(p != NULL){
            
            printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
            if(p -> hours > 0 && p -> hours < 12){
                printf("The Budget is: %.2f   The Priority level: %d\n", p->information.budget, i+1);
                
            }
            if(p->hours>=12 && p->hours<=20){
                printf("location is: %s   The Priority level: %d\n", p->information.location, i+1);
                
            }else if(p -> hours >20 && p -> hours < 24){
                printf("The endtime for this task is: %d:%02d   The Priority level: %d\n", p-> information.endtime[0], p-> information.endtime[1], i+1);
                
            }
            p = p->next;
            
        }
    }

    
   
}

void list_hour(){
    struct info *p;
    int i = 0;
    int temp;
    printf("What hour would you like to look at: \n");
    scanf("%d", &temp);
    for( i = 0; i < 3; i++){
        p = heads[i];
        printf("The tasks at %dhrs:  \n", temp);
        while(p != NULL){
            if (p -> hours == temp){
                printf("Task: %s ,and the time scheduled is: %d:%02d \n", p -> tasks, p -> hours, p -> mins);
                if(p -> hours > 0 && p -> hours < 12){
                    printf("The Budget is: %.2f   The Priority level: %d\n", p->information.budget, i+1);
                }
                if(p->hours>=12 && p->hours<=20){
                    printf("location is: %s   The Priority level: %d\n", p->information.location, i+1);
                }else if(p -> hours >20 && p -> hours < 24){
                    printf("The endtime for this task is: %d:%02d   The Priority level: %d\n", p-> information.endtime[0], p-> information.endtime[1], i+1);
                }
            }
            p = p->next;
            
        }
    }


}

void deleter(){
    struct info *p;
    struct info *q;
    struct info a;
    int i = 0;
    int j;
    printf("What Task would you like to remove \n");
    scanf("%s", a.tasks);
    
    for( i = 0; i < 3; i++){
        p = q= heads[i];
        

        while(p != NULL){
            if(strcmp(p->tasks, a.tasks)==0){
                j = i;
                i =3;
                break;
            }
            q = p;
            p = p -> next;
        }
    }
    if (p == NULL) {return;}
    else if(p == heads[j]){
            heads[j] = heads[j] -> next;
            free(p);
    }else{
            q -> next =p -> next;
            free(p);
    }
        
        
    

}

void callclear(){

    int i = 0;
    for(i = 0; i <3; i++){

        clear(heads[i]);

    }   

}

void clear(struct info *p){

    if (p == NULL){
        return;
    }
    clear(p -> next);
    free(p);
}

void calllistback(){
    int i = 0;
    for(i = 0; i <3; i++){

        backlist(heads[i], i);

    }
}

void backlist(struct info *p, int prio){

    if (p == NULL){
        return;
    }

    backlist(p -> next, prio);
    printf("Task: %s ,and the time scheduled is: %d:%02d \n", p->tasks, p->hours, p->mins);
    if(p -> hours > 0 && p -> hours < 12){
        printf("The Budget is: %.2f   The Priority level: %d\n", p->information.budget, prio+1);
        
    }
    if(p->hours>=12 && p->hours<=20){
        printf("location is: %s   The Priority level: %d\n", p->information.location, prio+1);
        
    }else if(p -> hours >20 && p -> hours < 24){
        printf("The endtime for this task is: %d:%02d   The Priority level: %d\n", p-> information.endtime[0], p-> information.endtime[1], prio+1);
        
    }

}
