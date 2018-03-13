#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Definition.h"
#include "Main.h"
#include "Alarm.h"

#define defaultPath "defaultPath" //TODO




//------------------------------------------------------



int main(int argc, char* argv[])
{
    struct alarm alarm_default = {false,7,00,defaultPath};
    struct alarm alarmCollection[5];


    //      INIT alarmCollection

    for (int i = 0;i<5;i++ ){
        alarmCollection[i] = alarm_default;
    }

    //      END INIT alarmCollection

    char chaine[30] = "";
    bool validCommand = false;

    while (validCommand == false){
        printf("Enter an action : \n");
        fgets(chaine, sizeof(chaine), stdin);
        clean(chaine, stdin);

        if (strcmp(chaine, "add new alarm") == 0){
            bool currentActivated = true;
            int currentAlarm = -1;
            currentActivated = alarmCollection[currentAlarm].activated;

            while (currentActivated && currentAlarm<5){
                currentAlarm++;
                currentActivated = alarmCollection[currentAlarm].activated;

            }
            if(!currentActivated){
                addAlarm(alarmCollection,currentAlarm);
                printf("Une alarme a ete creee \n");
            }
            else printf("No more space for another alarm, please modify an existing alarm");



        }
        else if (strcmp(chaine, "stop")==0){
            validCommand=true;
        }
        else if (strcmp(chaine, "see alarms")==0){

            displayAlarms(alarmCollection);

        }
        else printf("retry \n");
    }


	return 0;
}



void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
        *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}



