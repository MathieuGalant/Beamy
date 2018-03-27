#include <time.h>
#include <stdlib.h>
#include <stdio.h>s
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
    char *addAlarmFile="XML/addAlarm.xml";
    char *commandFile= "XML/command.xml";
    char *commandMusicFile="XML/commandMusic.xml";
    char *commandAlarmFile="XML/commandAlarm.xml";
    char *commandVideoFile="XML/commandVideo.xml";
    char *alarmFile="XML/alarm.xml";
    char *musicName[20]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
    char *addAlarm[1]={"0","0"};
    char *command[1]={"0","0"};
    char *commandVideo[1]={"0","0"};
    char *commandMusic[1]={"0","0"};
    char *commandAlarm[1]={"0","0"};
    char musicPlaying[50];
    char alarmPlaying[50];
    int continuer=1;



    int numberOfAlarm=0;
    Alarm anAlarm;
    List *alarmList=NULL;
    Alarm *searchAlarm=NULL;
    struct tm * timeinfo;




    readAlarmXmlFile(alarmFile, &anAlarm);
    displayAnAlarm(&anAlarm);






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
    int actionAlarm=0;
    int onetime=0;
    int playingMusic=0;
    int playingVideo=0;
    int playingAlarm=0;
    while (continuer)
    {
        readXmlFile(commandFile,command);
        //printf("%s  %s",command[0],command[1]);

        action=returnAction(command);

        timeinfo=getTime();
        //printf("%d\n",timeinfo->tm_wday);
      //  printf("%d\n",timeinfo->tm_hour);
       // printf("%d\n",timeinfo->tm_min);

        readXmlFile(addAlarmFile, addAlarm); //read the addAlarm XML
        if (strcmp(addAlarm[0],"1")==0) // check if someone is adding an alarm
        {
            readAlarmXmlFile(alarmFile,&anAlarm);
          //  displayAnAlarm(&anAlarm);
            if(numberOfAlarm==0)
            {
                alarmList=initializeAlarmList(&anAlarm);
                numberOfAlarm++;
                modifyXml(addAlarmFile);
              //  displayAlarms(alarmList);
            }
            else
            {
                alarmList=searchAlarmID(alarmList,anAlarm.ID);
                displayAlarms(alarmList);

                alarmList=saveAlarm(alarmList,&anAlarm);
                displayAlarms(alarmList);
                printf("%d\n",numberOfAlarm);
                modifyXml(addAlarmFile);
            }
        }


        if (numberOfAlarm >0)
        {
            Alarm *current=alarmList->first;


            while (current!=NULL)
            {

                if (timeinfo->tm_wday==current->day && timeinfo->tm_hour==current->hour && timeinfo->tm_min==current->min && timeinfo->tm_sec<5 && playingAlarm==0)
                {
                    FMOD_Sound_Release(music);


                    sprintf(alarmPlaying,"%s/%s",musicFolder,current->musicName);
                    printf("%s\n",alarmPlaying);
                    resultat=FMOD_System_CreateStream(syst, alarmPlaying, FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

                    if (resultat != FMOD_OK)
                        {
                        fprintf(stderr, "Cannot read the mp3 file\n");
                        exit(EXIT_FAILURE);
                        }

                        FMOD_Channel_SetVolume(channel, volume);
                        FMOD_System_PlaySound(syst,  music, 0, 0, &channel);

                    playingAlarm=1;
                }
                current =current->next;

            }
        }

        switch(action)
        {


            case 1: //play music
                {
                FMOD_Sound_Release(music);
                sprintf(musicPlaying,"%s/%s",musicFolder,command[1]);
                printf("%s",musicPlaying);
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
                playingVideo=1;
                modifyXml(commandFile);
                break;
                }
        }



    if (playingMusic==1) // check if an music is playing
    {

        readXmlFile(commandMusicFile,commandMusic); // read the command music XML
        printf("%s",commandMusic[0]);

        actionMusic=returnMusicAction(commandMusic); // return an action base on what is on the XML music
        switch(actionMusic)
        {
            case 1: // quit the music
                {
                FMOD_Sound_Release(music);
                playingMusic = 0;
                modifyXml(commandMusicFile);
                break;
                }

            case 2: // pause the music
                {
                resultat=FMOD_Channel_SetPaused(channel, 1);
                if (resultat != FMOD_OK)
                {
                    fprintf(stderr, "Cannot pause file\n");

                }
                modifyXml(commandMusicFile);
                break;
                }

            case 3: // continue the music
                {
                FMOD_Channel_SetPaused(channel, 0);
                modifyXml(commandMusicFile);
                break;
                }

            case 4: // make the music louder
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
            case 5: // make the music quieter
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

    if(playingVideo==1) // check if a video is playing
    {
        readXmlFile(commandVideoFile,commandVideo);
       // printf("%s",command[0]);

        actionVideo=returnVideoAction(commandVideo);
        switch(actionVideo)
        {
            case 1: // quit the video
                {
                stopVideo();
                modifyXml(commandVideoFile);
                playingVideo=0;
                break;
                }

            case 2: // pause the video
                {
                pauseVideo();
                modifyXml(commandVideoFile);
                break;
                }

            case 3: // continue the video
                {
                continueVideo();
                modifyXml(commandVideoFile);
                break;
                }

            case 4: // make the video louder
                {
                upVolumeVideo();
                modifyXml(commandVideoFile);
                break;
                }
            case 5: // make the video quieter
                {
                downVolumeVideo();
                modifyXml(commandVideoFile);
                break;
                }
        }

    }



    if(playingAlarm==1) // check if an alarm is ringing
    {
        readXmlFile(commandAlarmFile,commandAlarm);
       // printf("%s",command[0]);

        actionAlarm=returnAlarmAction(commandAlarm);
        switch(actionAlarm)
        {
            case 1: // stop the alarm
                {
                FMOD_Sound_Release(music);
                displayMagic();
                modifyXml(commandAlarmFile);
                playingAlarm=0;
                break;
                }

            case 2: // snooze the alarm
                {
                FMOD_Sound_Release(music);
                modifyXml(commandAlarmFile);
                playingAlarm=0;
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







