
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "definition.h"








void displayAlarms(struct alarm alarmCollection[],int numberOfAlarm)
{

                printf("\n Alarms :\n");

    for (int i = 0;i<numberOfAlarm;i++ ) // We don't know the array's size, so we must indicate it (5 here) or give it in parameters
    {
                printf("Day : %d \n",alarmCollection[i].day);
                printf("Hour : %d \n",alarmCollection[i].hour);
                printf("Minutes : %d \n",alarmCollection[i].min);
                printf("Music name : %s \n",alarmCollection[i].musicName);
                printf("State : %d \n",alarmCollection[i].state);
                printf("Delay : %d \n",alarmCollection[i].delay);
                printf("ID : %d \n \n",alarmCollection[i].ID);

    }

}
void saveAlarm(int numberOfAlarm, struct alarm alarmCollection[],struct alarm *anAlarm)
{



        alarmCollection[anAlarm->ID].day=anAlarm->day;
        alarmCollection[anAlarm->ID].hour=anAlarm->hour;
        alarmCollection[anAlarm->ID].min=anAlarm->min;
        strcpy(alarmCollection[anAlarm->ID].musicName,anAlarm->musicName);
        alarmCollection[anAlarm->ID].state=anAlarm->state;
        alarmCollection[anAlarm->ID].delay=anAlarm->delay;
        alarmCollection[anAlarm->ID].ID=anAlarm->ID;
        //printf("new alarm added");


}



void displayAnAlarm(struct alarm *anAlarm)
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

