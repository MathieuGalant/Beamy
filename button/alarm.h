#ifndef ALARM_H_INCLUDED
#define ALARM_H_INCLUDED

#include "definition.h"
void displayAnAlarm(struct alarm anAlarm);
void displayAlarms(struct alarm alarmCollection[],int numberOfAlarm);
void addAlarm(struct alarm anAlarm, char *alarmFile);
void setDay(struct alarm anAlarm, weekday day);
void setHour(struct alarm anAlarm, int hour);
void setMinutes(struct alarm anAlarm, int minutes);
void setMusicName(struct alarm anAlarm,char musicName[]);
void setState(struct alarm anAlarm, bool state);
void setDelay(struct alarm anAlarm, int delay);
void setPath(struct alarm anAlarm, char path[]);

#endif // ALARM_H_INCLUDED
