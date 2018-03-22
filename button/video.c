#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>
#include <fmod.h>
#include <dirent.h>
#include "definition.h"



playVideo(char *videoFolder,char *command[])
{
    char *videoPlaying;
    sprintf(videoPlaying,"omxplayer --win \"1000 500 1920 1080\" %s/%s",videoFolder,command[1]);
    system(videoPlaying);

}

stopVideo()
{
system("./media/dbuscontrol.sh exit");
}


pauseVideo()
{
system("./media/dbuscontrol.sh pause");
}


continueVideo()
{
system("./media/dbuscontrol.sh pause");
}


upVolumeVideo()
{
system("./media/dbuscontrol.sh volumeup");
}


downVolumeVideo()
{
system("./media/dbuscontrol.sh volumedown");
}
