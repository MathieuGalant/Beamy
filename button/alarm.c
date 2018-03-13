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
                printf("Path : %s \n \n",alarmCollection[i].path);

    }

}
void displayAnAlarm(struct alarm *anAlarm)
 {

    printf("Day : %d \n",anAlarm->day);
    printf("Hour : %d \n",anAlarm->hour);
    printf("Minutes : %d \n",anAlarm->min);
    printf("Music name : %s \n",anAlarm->musicName);
    printf("State : %d \n",anAlarm->state);
    printf("Delay : %d \n",anAlarm->delay);
    printf("Path : %s \n \n",anAlarm->path);


 }

void addAlarm(struct alarm anAlarm, char *alarmFile)
{
    /* Read XLM Alarm file and put the variable into the local alarm array*/
    readAlarmXmlFile(anAlarm,alarmFile);


}


void setDay(struct alarm anAlarm, weekday day)
{

    anAlarm.day=day;

}

void setHour(struct alarm anAlarm, int hour)
{
    if (hour >= 0 && hour < 24 )
    {
        anAlarm.hour=hour;
    }
        else printf("Incorrect alarm's hour. Retry \n");

}

void setMinutes(struct alarm anAlarm, int minutes)
{
    if (minutes >=0 && minutes < 60)
    {
        anAlarm.min=minutes;
    }
    else printf("Incorrect alarm's minutes.\n");

}

void setMusicName(struct alarm anAlarm, char musicName[] )
{

    strcpy(anAlarm.musicName,musicName);

}

void setState(struct alarm anAlarm, bool state)
{

    anAlarm.state=state;

}

void setDelay(struct alarm anAlarm, int delay)
{

    anAlarm.delay=delay;

}

void setPath(struct alarm anAlarm, char path[])
{

    strcpy(anAlarm.path,path);

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
