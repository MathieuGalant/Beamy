#ifndef Alarm_H_INCLUDED
#define Alarm_H_INCLUDED

#include "definition.h"
List *initializeAlarmList(Alarm *anAlarm);
void displayAnAlarm(Alarm *anAlarm);
void displayAlarms(List *AlarmList);
int saveAlarm(List *AlarmList, Alarm *anAlarm);
struct tm * getTime ();
void delay(unsigned int mseconds);

#endif // Alarm_H_INCLUDED
