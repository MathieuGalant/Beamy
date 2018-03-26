
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "definition.h"





List *initializeAlarmList(Alarm *anAlarm)
{
    List *AlarmList=malloc(sizeof(*AlarmList));
    Alarm *newAlarm=malloc(sizeof(*anAlarm));

    if (AlarmList==NULL || anAlarm == NULL)
    {
        exit(EXIT_FAILURE);
    }

    newAlarm->day=anAlarm->day;
    newAlarm->hour=anAlarm->hour;
    newAlarm->min=anAlarm->min;
    strcpy(newAlarm->musicName,anAlarm->musicName);
    newAlarm->state=anAlarm->state;
    newAlarm->delay=anAlarm->delay;
    newAlarm->ID=anAlarm->ID;
    newAlarm->next=NULL;

    AlarmList->first=anAlarm;
    return AlarmList;
}

void displayAlarms(List *AlarmList)
{

    printf("\n Alarms :\n");
    Alarm *current=AlarmList->first;

    while (current != NULL)
    {
                printf("Day : %d \n",current->day);
                printf("Hour : %d \n",current->hour);
                printf("Minutes : %d \n",current->min);
                printf("Music name : %s \n",current->musicName);
                printf("State : %d \n",current->state);
                printf("Delay : %d \n",current->delay);
                printf("ID : %d \n \n",current->ID);

    }

}

void saveAlarm(List *AlarmList, Alarm *anAlarm)
{
        Alarm *newAlarm =malloc(sizeof(*newAlarm));


        newAlarm->day=anAlarm->day;
        newAlarm->hour=anAlarm->hour;
        newAlarm->min=anAlarm->min;
        strcpy(newAlarm->musicName,anAlarm->musicName);
        newAlarm->state=anAlarm->state;
        newAlarm->delay=anAlarm->delay;
        newAlarm->ID=anAlarm->ID;
        //printf("new Alarm added");
        newAlarm->next=AlarmList->first;
        AlarmList->first=newAlarm;


}



void displayAnAlarm(Alarm *anAlarm)
 {

    printf("Day : %d \n",anAlarm->day);
    printf("Hour : %d \n",anAlarm->hour);
    printf("Minutes : %d \n",anAlarm->min);
    printf("Music name : %s \n",anAlarm->musicName);
    printf("State : %d \n",anAlarm->state);
    printf("Delay : %d \n",anAlarm->delay);
    printf("ID : %d \n \n",anAlarm->ID);

 }



struct tm * getTime ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
 // printf ( "The current date/time is: %s", asctime (timeinfo) );

  return timeinfo;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void displayMagic()
{


    pid_t pid=fork();
    if (pid==0)
    { /* child process */
        system("cd ~/MagicMirror/ && DISPLAY=:0 npm start");

        exit(127); /* only if execv fails */
    }
    system("cd ~/Desktop/beamy/button/");
}

