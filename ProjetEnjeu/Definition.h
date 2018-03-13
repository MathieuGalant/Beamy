#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED
#define defaultPath "defaultPath"

typedef int bool;
#define true 1
#define false 0

struct alarm {
    bool activated ;
    int hour ;
    int min ;
    char path[80];
};





#endif // DEFINITION_H_INCLUDED
