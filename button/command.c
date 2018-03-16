#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>



int returnAction(char * command[])

{
    int action;
  //  printf("hello");
      if (strcmp(command[0], "play music") == 0)
            {
                action = 1;
            }

        else if (strcmp(command[0], "play random music") == 0)
            {
                action = 2;
            }

            else if (strcmp(command[0], "play video") == 0)
                {
                    action = 99;
                }


    return action;
}


int returnMusicAction(char * command[])

{
    int action;
  //  printf("hello");
      if (strcmp(command[0], "quit") == 0)
            {
                action = 1;
            }

        else if (strcmp(command[0], "pause") == 0)
            {
                action = 2;
            }

            else if (strcmp(command[0], "continue") == 0)
                {
                    action = 3;
                }

                else if (strcmp(command[0], "volume up") == 0)
                    {
                        action = 4;
                    }
                    else if (strcmp(command[0], "volume down") == 0)
                        {
                            action = 5;
                        }

                        else action=99;
    return action;
}

int returnVideoAction(char * command[])

{
    int action;
  //  printf("hello");
      if (strcmp(command[0], "quit") == 0)
            {
                action = 1;
            }

        else if (strcmp(command[0], "pause") == 0)
            {
                action = 2;
            }

            else if (strcmp(command[0], "continue") == 0)
                {
                    action = 3;
                }

                else if (strcmp(command[0], "volume down") == 0)
                    {
                        action = 4;
                    }
                    else if (strcmp(command[0], "volume down") == 0)
                        {
                            action = 5;
                        }

                        else action=99;
    return action;
}
