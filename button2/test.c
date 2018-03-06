/*
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <fmod/fmod.h>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

char* ReadFile(char *filename);


int main(int argc, char **argv)
{
    SDL_Surface *ecran = NULL, *pochette = NULL;
    SDL_Event event;
 //   SDL_Rect position;




    FMOD_SYSTEM *system;
    FMOD_CHANNEL *channel = 0;
    FMOD_RESULT resultat;
    void *extradriverdata = 0;
    int continuer=1;

    char *string =ReadFile("media/command.txt");
    printf("%s", string);
    /*
        Create a System object and initialize.


    FMOD_System_Create(&system);


    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, extradriverdata);


    /* Increase the file buffer size a little bit to account for Internet lag.
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


    FMOD_System_PlaySound(system,  music, 0, 0, &channel);

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du son avec FMOD", NULL);
  //  pochette = IMG_Load("media/player.png");
//    position.x = 0;
 //   position.y = 0;

        while (continuer)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_p) //Si on appuie sur P
            {
                FMOD_CHANNELGROUP *canal;
                FMOD_BOOL etat;
                FMOD_System_GetMasterChannelGroup(system, &canal);
                FMOD_ChannelGroup_GetPaused(canal, &etat);

                if (etat) // Si la chanson est en pause
                    FMOD_ChannelGroup_SetPaused(canal, 0); // On enlève la pause
                else // Sinon, elle est en cours de lecture
                    FMOD_ChannelGroup_SetPaused(canal, 1); // On active la pause
            }
            break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      //  SDL_BlitSurface(pochette, NULL, ecran, &position);
        SDL_Flip(ecran);
    }

    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);


    SDL_FreeSurface(pochette);
    SDL_Quit();
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

*/
