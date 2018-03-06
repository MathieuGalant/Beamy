#include <stdlib.h>
#include <stdio.h>

#include <fmod/fmod.h>



char* ReadFile(char *filename);


int main(int argc, char **argv)
{





    FMOD_SYSTEM *system;
    FMOD_CHANNEL *channel = 0;
    FMOD_RESULT resultat;
    void *extradriverdata = 0;
    float volume=0.5;
    int continuer=1;
    int action=0;
    char *filename= "media/command.txt";
    FILE *handler;
    /*
        Create a System object and initialize.
    */



    FMOD_System_Create(&system);


    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, extradriverdata);


    /* Increase the file buffer size a little bit to account for Internet lag. */
    FMOD_System_SetStreamBufferSize(system,64*1024, FMOD_TIMEUNIT_RAWBYTES);



    FMOD_CREATESOUNDEXINFO exinfo;
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.filebuffersize = 1024*16;

    FMOD_SOUND *music;
    resultat=FMOD_System_CreateSound(system, "media/Kalimba.mp3", FMOD_LOOP_NORMAL | FMOD_2D, &exinfo, &music);

    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }

    FMOD_Channel_SetVolume(channel, volume);
    FMOD_System_PlaySound(system,  music, 0, 0, &channel);


        while (continuer)
    {
        char *command =ReadFile(filename);



        if (strcmp(command, "quit") == 0)
            {
                action = 1;
            }

        else if (strcmp(command, "pause") == 0)
            {
                action = 2;
            }

            else if (strcmp(command, "continue") == 0)
                {
                    action = 3;
                }

                else if (strcmp(command, "louder") == 0)
                    {
                        action = 4;
                    }
                    else if (strcmp(command, "quiet") == 0)
                        {
                            action = 5;
                        }
                        else action=99;

        switch(action)
        {
            case 1:
                {
                continuer = 0;
                handler=fopen(filename, "w+");
                fclose(handler);

                break;
                }

            case 2:
                {
                FMOD_Channel_SetPaused(channel, 1);
                handler=fopen(filename, "w+");
                fclose(handler);
                break;
                }

            case 3:
                {
                FMOD_Channel_SetPaused(channel, 0);
                handler=fopen(filename, "w+");
                fclose(handler);
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
                handler=fopen(filename, "w+");
                fclose(handler);
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
                handler=fopen(filename, "w+");
                fclose(handler);
                break;
                }





        }

        }




    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);



 return EXIT_SUCCESS;
}




char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}



