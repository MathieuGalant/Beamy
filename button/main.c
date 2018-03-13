#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>
#include "xml.h"
#include "command.h"
#include "alarm.h"

void getFolderFiles(char *foldername,char *musicName[]);




int main(int argc, char **argv)
{

    int musicNumber=20;
    char *musicFolder="media/music";
    char *alarmFolder="alarm";
    char *commandFile= "XML/command.xml";
    char *alarmFile="XML/alarm.xml";
    char *musicName[musicNumber];
    char *command[10];
    char musicPlaying[100];
    int continuer=1;


    struct alarm alarm_default = {MONDAY,7,0,"Kalimba.mp3",false,0,alarmFolder};
    struct alarm alarmCollection[5];
    struct alarm alarmTest;


    for (int i = 0;i<5;i++ )
    {
        alarmCollection[i] = alarm_default;
    }

  //  displayAlarms(alarm_default,1);
    displayAnAlarm(alarm_default);



    readAlarmXmlFile(alarmFile,alarmTest);

    displayAnAlarm(alarmTest);





    getFolderFiles(musicFolder,musicName);
  //  printf("%s\n",musicName[0]);
    sprintf(musicPlaying,"%s/%s",musicFolder,musicName[0]);
//    printf("%s\n",musicPlaying);

    FMOD_SYSTEM *system;
    FMOD_CHANNEL *channel = 0;
    FMOD_RESULT resultat;
    void *extradriverdata = 0;
    FMOD_CREATESOUNDEXINFO exinfo;

           /* Create a System object and initialize.*/

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, extradriverdata);

        /* Increase the file buffer size a little bit to account for Internet lag. */

    FMOD_System_SetStreamBufferSize(system,64*1024, FMOD_TIMEUNIT_RAWBYTES);

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.filebuffersize = 1024*16;


    float volume=0.5;
    FMOD_SOUND *music;





    int action=0;

    while (continuer)
    {
        readXmlFile(commandFile,command);
       // printf("%s",command[0]);

        action=returnAction(command);



        switch(action)
        {
            case 1:
                {
                continuer = 0;
                modifyXml(commandFile);
                break;
                }

            case 2:
                {
                resultat=FMOD_Channel_SetPaused(channel, 1);
                if (resultat != FMOD_OK)
                {
                    fprintf(stderr, "Cannot pause file\n");

                }
                modifyXml(commandFile);
                break;
                }

            case 3:
                {
                FMOD_Channel_SetPaused(channel, 0);
                modifyXml(commandFile);
                break;
                }

            case 4:
                {
                volume=volume +0.01;
                resultat=FMOD_Channel_SetVolume(channel, volume);
                if (resultat != FMOD_OK)
                    {
                        printf( "pas de changement de volume");
                    }
                else
                    {
                        printf("plus fort");
                    }
                modifyXml(commandFile);
                break;
                }
            case 5:
                {
                volume=volume -0.01;
                resultat=FMOD_Channel_SetVolume(channel, volume);
                if (resultat != FMOD_OK)
                    {
                        printf( "pas de changement de volume");
                    }
                else
                    {
                        printf("moins fort");
                    }
                modifyXml(commandFile);
                break;
                }

            case 6:
                {
                FMOD_Sound_Release(music);
                resultat=FMOD_System_CreateStream(system, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                if (resultat != FMOD_OK)
                {
                fprintf(stderr, "Cannot read the mp3 file\n");
                exit(EXIT_FAILURE);
                }

                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(system,  music, 0, 0, &channel);
                modifyXml(commandFile);
                break;
                }

            case 7:
                {
                FMOD_Sound_Release(music);
                char musicPlaying[100];
                srand(time(NULL));
                int r = rand()%musicNumber;

                getFolderFiles(musicFolder,musicName);

                sprintf(musicPlaying,"%s/%s",musicFolder,musicName[r]);
                resultat=FMOD_System_CreateStream(system, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                if (resultat != FMOD_OK)
                {
                fprintf(stderr, "Cannot read the mp3 file\n");
                exit(EXIT_FAILURE);
                }

                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(system,  music, 0, 0, &channel);
                modifyXml(commandFile);
                break;
                }



        }

    }




    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);



 return EXIT_SUCCESS;



}





void getFolderFiles(char *folderName, char *musicName[10])
{
int i=0;
DIR *dir;
struct dirent *ent;
if ((dir = opendir (folderName)) != NULL) {
  /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL) {
   // printf ("%s\n", ent->d_name);
    musicName[i]=ent->d_name;
    i++;

  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
  return EXIT_FAILURE;
}

}







