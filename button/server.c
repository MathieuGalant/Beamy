#include <time.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>
#include "definition.h"


void getAlarmServer(int ID, char *alarmFile)
{
    char alarmServer[80];
    printf("ok");
    sprintf(alarmServer,"curl -o %s -X GET \"http://localhost:8000/api/alarm/%d/\"",alarmFile,ID);
    printf("%s\n",alarmServer);
    system(alarmServer);

}


void getMusicFilesServer(int ID, char *alarmFile)
{
    char alarmServer[80];
    printf("ok");
    sprintf(alarmServer,"curl -o %s -X GET \"http://localhost:8000/api/alarm/%d/\"",alarmFile,ID);
    printf("%s\n",alarmServer);
    system(alarmServer);

}

void getVideoFilesServer(int ID, char *alarmFile)
{
    char alarmServer[80];
    printf("ok");
    sprintf(alarmServer,"curl -o %s -X GET \"http://localhost:8000/api/alarm/%d/\"",alarmFile,ID);
    printf("%s\n",alarmServer);
    system(alarmServer);

}
