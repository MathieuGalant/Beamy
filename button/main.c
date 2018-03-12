#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>


char* ReadXmlFile(char *filename,char *attribut[]);
void getXml(xmlNode * node, int i,char *attribut[]);
int is_leaf(xmlNode * node);
void modifyXml(char * filename);
void getFolderFiles(char *foldername,char *musicName[]);
FMOD_RESULT  playMusic(FMOD_SYSTEM *system, char musicName[100], FMOD_CREATESOUNDEXINFO exinfo, FMOD_SOUND *music, FMOD_CHANNEL *channel, float volume);
FMOD_RESULT  playRamdomMusic(FMOD_SYSTEM *system, char *musicName[], FMOD_CREATESOUNDEXINFO exinfo, FMOD_SOUND *music, FMOD_CHANNEL *channel, float volume,char*musicFolder,int musicNumber);
int returnAction(char *command[]);



int main(int argc, char **argv)
{

    int musicNumber=20;
    char *musicFolder="media/music";
    char *commandFile= "XML/command.xml";
    char *musicName[musicNumber];
    char *command[10];
    char musicPlaying[100];
    int continuer=1;
    int action=0;




    getFolderFiles(musicFolder,musicName);
    printf("%s\n",musicName[0]);
    sprintf(musicPlaying,"%s/%s",musicFolder,musicName[0]);
    printf("%s\n",musicPlaying);

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


void readXmlFile(char *filename,  char * attribut[])
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;


    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL)
        {
        printf("Could not parse the XML file");
        }

    root_element = xmlDocGetRootElement(doc);

    getXml(root_element,0,attribut);

    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlCleanupParser();
    return attribut;
}

void getXml(xmlNode * node,int i,  char *attribut[])
{


    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
      //    printf("%c%s:%s\n", '-', node->name, is_leaf(node)?xmlNodeGetContent(node):xmlGetProp(node, "id"));
          if (is_leaf(node))
          {
            attribut[i]=xmlNodeGetContent(node);
            i++;
          }
        }
        getXml(node->children,i, attribut);
        node = node->next;


    }

}

int is_leaf(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;

    child = child->next;
  }

  return 1;
}



void modifyXml(char * filename)
{
    xmlDoc *doc = xmlParseFile(filename);
    xmlNode *root_element = NULL;
    xmlNode * node=NULL;
    root_element = xmlDocGetRootElement(doc);
    node=root_element->children;
    node=node->next;
  //  printf("%s",xmlNodeGetContent(node));
    xmlNodeSetContent(node, (xmlChar*)"0");


    xmlSaveFileEnc(filename, doc, "UTF-8");
}

void getFolderFiles(char *folderName, char *musicName[10])
{
int i=0;
DIR *dir;
struct dirent *ent;
if ((dir = opendir (folderName)) != NULL) {
  /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL) {
    printf ("%s\n", ent->d_name);
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




int returnAction(char * command[])

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

                else if (strcmp(command[0], "louder") == 0)
                    {
                        action = 4;
                    }
                    else if (strcmp(command[0], "quiet") == 0)
                        {
                            action = 5;
                        }
                        else if(strcmp(command[0],"play") == 0)
                            {
                                action=6;
                            }
                            else if(strcmp(command[0],"play random")==0)
                                {
                                    action=7;
                                }
                                else action=99;
    return action;
}
