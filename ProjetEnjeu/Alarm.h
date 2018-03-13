#ifndef ALARM_H_INCLUDED
#define ALARM_H_INCLUDED
#include "Definition.h"

void displayAlarms(struct alarm alarmCollection[]);
void addAlarm(struct alarm alarmCollection[], int argAlarmNumber);
void setHour (struct alarm alarmCollection[], int argAlarmNumber);
void setMinutes (struct alarm alarmCollection[], int argAlarmNumber);

#endif // ALARM_H_INCLUDED


