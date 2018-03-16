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
#include "definition.h"
#include "video.h"




void getFolderFiles(char *foldername,char *musicName[]);




int main(int argc, char **argv)
{

    int musicNumber=20;
    char *musicFolder="media/music";
    char *videoFolder="media/video";
    char *alarmFolder="alarm";
    char *commandFile= "XML/command.xml";
    char *commandMusicFile="XML/commandMusic.xml";
    char *commandAlarmFile="XML/commandAlarm.xml";
    char *alarmFile="XML/alarm.xml";
    char *musicName[20];
    char *command[1];
    char *commandVideo[0];
    char *commandMusic[0];
    char musicPlaying[100];
    int continuer=1;



    struct alarm anAlarm;


    struct tm * timeinfo;
    timeinfo=getTime();
    //printf("%d\n",timeinfo->tm_wday);
    //printf("%d\n",timeinfo->tm_hour);
    //printf("%d\n",timeinfo->tm_min);



  //  displayAlarms(alarm_default,1);
    displayAnAlarm(&alarm_default);



    readAlarmXmlFile(alarmFile, &anAlarm);

    displayAnAlarm(&anAlarm);





  //  getFolderFiles(musicFolder,musicName);
  //  printf("%s\n",musicName[0]);
  //  sprintf(musicPlaying,"%s/%s",musicFolder,musicName[0]);
//    printf("%s\n",musicPlaying);

    FMOD_SYSTEM *syst;
    FMOD_CHANNEL *channel = 0;
    FMOD_RESULT resultat;
    void *extradriverdata = 0;
    FMOD_CREATESOUNDEXINFO exinfo;

           /* Create a System object and initialize.*/

    FMOD_System_Create(&syst);
    FMOD_System_Init(syst, 32, FMOD_INIT_NORMAL, extradriverdata);

        /* Increase the file buffer size a little bit to account for Internet lag. */

    FMOD_System_SetStreamBufferSize(syst,64*1024, FMOD_TIMEUNIT_RAWBYTES);

    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.filebuffersize = 1024*16;


    float volume=0.5;
    FMOD_SOUND *music;





    int action=0;
    int actionMusic=0;
    int actionVideo=0;
    int actionAlarm=0
    int onetime=0;
    int playingMusic=0;
    int playingVideo=0;
    int playingAlarm=0;
    while (continuer)
    {
        readXmlFile(commandFile,command);
       // printf("%s",command[0]);

        action=returnAction(command);

        timeinfo=getTime();
     //   printf("%d\n",timeinfo->tm_wday);
      //  printf("%d\n",timeinfo->tm_hour);
       // printf("%d\n",timeinfo->tm_min);

        if (timeinfo->tm_wday==anAlarm.day && timeinfo->tm_hour==anAlarm.hour && timeinfo->tm_min==anAlarm.min && onetime==0)
        {
                FMOD_Sound_Release(music);
                sprintf(musicPlaying,"%s/%s",musicFolder,anAlarm.musicName);
                printf("%s\n",musicPlaying);
                resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                if (resultat != FMOD_OK)
                {
                fprintf(stderr, "Cannot read the mp3 file\n");
                exit(EXIT_FAILURE);
                }

                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(system,  music, 0, 0, &channel);
                onetime=1;
                playingAlarm=1;
        }

        switch(action)
        {


            case 1: //play music
                {
                FMOD_Sound_Release(music);
                sprintf(musicPlaying,"%s/%s",musicFolder,command[1]);
                resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                if (resultat != FMOD_OK)
                    {
                    fprintf(stderr, "Cannot read the mp3 file\n");
                    exit(EXIT_FAILURE);
                    }

                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                modifyXml(commandFile);
                playingMusic=1;
                break;
                }

            case 2: //play random music
                {
                FMOD_Sound_Release(music);

                srand(time(NULL));
                int r = rand()%musicNumber;

                getFolderFiles(musicFolder,musicName);

                sprintf(musicPlaying,"%s/%s",musicFolder,musicName[r]);
                resultat=FMOD_System_CreateStream(syst, musicPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                if (resultat != FMOD_OK)
                {
                fprintf(stderr, "Cannot read the mp3 file\n");
                exit(EXIT_FAILURE);
                }

                FMOD_Channel_SetVolume(channel, volume);
                FMOD_System_PlaySound(syst,  music, 0, 0, &channel);
                modifyXml(commandFile);
                playingMusic=1;
                break;
                }
            case 3 : //play video
                {
                playVideo(videoFolder,command);
                break;
                }
        }



    if (playingMusic==1)
    {

        readXmlFile(commandMusicFile,commandMusic);
       // printf("%s",command[0]);

        actionMusic=returnAction(commandMusic);
        switch(actionMusic)
        {
            case 1:
                {
                playingMusic = 0;
                modifyXml(commandMusicFile);
                break;
                }

            case 2:
                {
                resultat=FMOD_Channel_SetPaused(channel, 1);
                if (resultat != FMOD_OK)
                {
                    fprintf(stderr, "Cannot pause file\n");

                }
                modifyXml(commandMusicFile);
                break;
                }

            case 3:
                {
                FMOD_Channel_SetPaused(channel, 0);
                modifyXml(commandMusicFile);
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
                modifyXml(commandMusicFile);
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
                modifyXml(commandMusicFile);
                break;
                }
        }
    }

    if(playingVideo==1)
    {
        readXmlFile(commandVideoFile,commandVideo);
       // printf("%s",command[0]);

        actionVideo=returnAction(commandVideo);
        switch(actionVideo)
        {
            case 1:
                {
                stopVideo();
                modifyXml(commandVideoFile);
                videoPlaying=0;
                break;
                }

            case 2:
                {
                pauseVideo();
                modifyXml(commandVideoFile);
                break;
                }

            case 3:
                {
                continueVideo();
                modifyXml(commandVideoFile);
                break;
                }

            case 4:
                {
                upVolumeVideo();
                modifyXml(commandVideoFile);
                break;
                }
            case 5:
                {
                downVolumeVideo();
                modifyXml(commandVideoFile);
                break;
                }
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







