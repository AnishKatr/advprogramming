#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

struct info *heads[3] = {NULL, NULL, NULL};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){

        pthread_t threadID;
        //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

        if(argc == 1){
                printf("The name of the file isn't there\n");
                return 1;
        }
	
	    pthread_mutex_init(&mutex, NULL);
        pthread_create(&threadID, NULL, autosaver,(void*) argv[2]);
        read(argv[1]);
        int option;
        
        while(1){

                printf("MENU \n");
                printf("1 - Add a Task w/ Time \n");
                printf("2 - Shows the List of Tasks \n");
                printf("3 - List Tasks at a Certain Hour \n");
                printf("4 - Delete a Specific task from the Schedule\n");
                printf("5 - List Each Priority List Backwards\n");
                printf("6 - Read From Autosaved File\n");
                printf("0 - To Quit \n");
                
                if (scanf("%d", &option) != 1){
                        printf("error\n");
                        return 0;
                }

                switch(option){

                        case 1:
                            pthread_mutex_lock(&mutex);
                            prompt();
                            pthread_mutex_unlock(&mutex);
                            break;
                        case 2:
                            printf("Tasks for the day\n");
                            list();
                            break;
                        case 3:
                            list_hour();
                            break;
                        case 4:
                            pthread_mutex_lock(&mutex);
                            deleter();
                            pthread_mutex_unlock(&mutex);
                            break;
                        case 5:
                            calllistback();
                            break;
                        case 6:
                            pthread_mutex_lock(&mutex);
                            binread(argv[2]);
                            pthread_mutex_unlock(&mutex);
                            break;
                        case 0:
			    pthread_mutex_lock(&mutex);
                            pthread_cancel(threadID);
			    pthread_mutex_unlock(&mutex);
                            save(argv[1]);
                            callclear();
                            //clear();
                            printf("You Have Quit \n");
                            return 0;
                        default:
                            printf("Wrong Option\n");

                }
        }
}
