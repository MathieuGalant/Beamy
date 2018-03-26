#ifndef ALARM_H_INCLUDED
#define ALARM_H_INCLUDED

#include "definition.h"
void displayAnAlarm(struct alarm *anAlarm);
void displayAlarms(struct alarm alarmCollection[],int numberOfAlarm);
int saveAlarm(int numberOfAlarm, struct alarm alarmCollection[],struct alarm *anAlarm);
struct tm * getTime ();
void delay(unsigned int mseconds);

#endif // ALARM_H_INCLUDED
