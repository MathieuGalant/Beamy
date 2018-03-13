#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

typedef int bool;
#define true 1
#define false 0

typedef enum {MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY} weekday;

struct alarm {
    weekday day;
    int hour ;
    int min ;
    char musicName[30];
    bool state;
    int delay;
    char path[80];
};


#endif // DEFINITION_H_INCLUDED
