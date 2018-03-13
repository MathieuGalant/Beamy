#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Alarm.h"
#include "Definition.h"
#include "Main.h"

 //TODO


20





void displayAlarms(struct alarm alarmCollection[]){

                printf("\n Alarms :\n");

    for (int i = 0;i<5;i++ ){ // We don't know the array's size, so we must indicate it (5 here) or give it in parameters

                printf("Activated : %d \n",alarmCollection[i].activated);
                printf("Hour : %d \n",alarmCollection[i].hour);
                printf("Minutes : %d \n",alarmCollection[i].min);
                printf("Path : %s \n \n",alarmCollection[i].path);

    }

}

void addAlarm(struct alarm alarmCollection[], int argAlarmNumber){
    alarmCollection[argAlarmNumber].activated = true;
    setHour(alarmCollection,argAlarmNumber);
    setMinutes(alarmCollection,argAlarmNumber);
    getchar();



}

void setHour (struct alarm alarmCollection[], int argAlarmNumber){
    bool correctHour = false;
    int newHour;
    while (!correctHour){
        printf("Enter the alarm's hour : \n");
        scanf("%d", &newHour);

        if (newHour >= 0 && newHour < 24 ) {
            printf("Alarm's hour setted to %d \n",newHour);
            correctHour = true;
        }
        else printf("Incorrect alarm's hour. Retry \n");
    }
    alarmCollection[argAlarmNumber].hour = newHour;
}

void setMinutes (struct alarm alarmCollection[], int argAlarmNumber) {
    bool correctMinutes = false;
    int newMinutes;

    while (!correctMinutes){
        printf("Enter the alarm's minutes : \n");
        scanf("%d", &newMinutes);

        if (newMinutes >=0 && newMinutes < 60){
            printf("Alarm's minutes setted to %d \n",newMinutes);
            correctMinutes = true;
        }
        else printf("Incorrect alarm's minutes. Retry \n");
    }

    alarmCollection[argAlarmNumber].min = newMinutes;
}

