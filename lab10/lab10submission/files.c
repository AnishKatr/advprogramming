#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void insert(struct info data){

    struct info *p;
    struct info *q;
    struct info *temp;
    int pos;      
    
    p = (struct info *)malloc(sizeof(struct info));
    *p = data;
    pos = p->priority - 1;
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

void read(char argv[]){

    FILE *fp;
    struct info data;
    int i = 0;
    fp = fopen(argv, "r");
    char c;
    if( fp == NULL){
        return;
    }
    
    while((fscanf(fp, "%s", data.tasks)) == 1){
            fscanf(fp, "%d", &data.priority);
            fscanf(fp, "%d", &data.hours);
            fscanf(fp,"%c",&c);
            fscanf(fp, "%d", &data.mins);
            if(data.hours > 0 && data.hours < 12){
                fscanf(fp, "%f", &data.information.budget);
            }
            else if(data.hours>=12 && data.hours<=20){
                fscanf(fp, "%[^\n]", data.information.location);
            }else if(data.hours >20 && data.hours < 24){
                fscanf(fp, "%d%c%d", &data.information.endtime[0],&c, &data.information.endtime[1]);
                
            }

            insert(data);
    }
    fclose(fp);
    

}

void save(char argv[]){
    FILE *outfp;
    struct info *p;

    int i = 0;
    if((outfp = fopen(argv, "w")) == NULL){
        printf("cannot open the file\n");
        return;
    }
    for( i = 0; i < 3; i++){

        p = heads[i];
        while( p!= NULL){
            if(p -> hours > 0 && p -> hours < 12){
                fprintf(outfp, "%s %d %d:%02d %.2f\n", p -> tasks, p->priority, p->hours ,p->mins, p->information.budget);
            }
            if(p->hours>=12 && p->hours<=20){
                fprintf(outfp, "%s %d %d:%02d %s\n",p -> tasks, p->priority, p->hours ,p->mins, p->information.location);
            }else if(p -> hours >20 && p -> hours < 24){
                fprintf(outfp, "%s %d %d:%02d %d:%02d\n", p -> tasks, p->priority, p->hours ,p->mins, p->information.endtime[0], p->information.endtime[1]);
            }
            p = p -> next;
        }
    }
    fclose(outfp);
    return;

}

void *autosaver(void *argv){

    FILE *fp;
    struct info *p;
    //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int i = 0;
    while(1){
        
        //pthread_mutex_lock(&mutex);
        fp = fopen(argv, "wb");
        for(i=0; i<3; i++){
            p = heads[i];
            while(p!=NULL){
                fwrite(p,sizeof(struct info *),1,fp);
                p = p -> next;
            }

        }
        fclose(fp);
        sleep(15);
        //pthread_mutex_unlock(&mutex);
    }

    return NULL;

}

void binread(void *argv){
    FILE *fp;
    fp = fopen(argv, "rb");
    int i = 0;
    struct info *p = (struct info *)malloc(sizeof(struct info));
    while(fread(p,sizeof(struct info *), 1, fp) == 1){
            if(p -> hours > 0 && p -> hours < 12){
                printf("%s %d %d:%02d %.2f\n", p -> tasks, p->priority, p->hours ,p->mins, p->information.budget);
            }
            if(p->hours>=12 && p->hours<=20){
                printf("%s %d %d:%02d %s\n",p -> tasks, p->priority, p->hours ,p->mins, p->information.location);
            }else if(p -> hours >20 && p -> hours < 24){
                printf("%s %d %d:%02d %d:%02d\n", p -> tasks, p->priority, p->hours ,p->mins, p->information.endtime[0], p->information.endtime[1]);
            }
    }
}