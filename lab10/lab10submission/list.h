#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

typedef union{

float budget;
char location[50];
int endtime[2];

}EXTRA_INFO;


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
void save(char *);
void callclear();
void clear(struct info *p);
void read(char *);
void prompt();
void calllistback();
void backlist(struct info *p, int prio);
void *autosaver(void *argv);
void binread(void *argv);

//array
extern struct info *heads[3];
extern pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;