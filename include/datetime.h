#ifndef DATETIME_GUARD
#define DATETIME_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "errors.h"

#define MAX_CLOCK_DATE_BUFFER_LEN 512

struct DateStruct{
    unsigned char day;
    unsigned char month;
    unsigned int year;
    bool error;
};

struct TimeStruct{
    unsigned char hours;
    unsigned char minutes;
    unsigned char seconds;
    bool error;
};

struct tm* generateDateAndTime();
void setNewTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments);
void setNewDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments);
void verifyForDateAndTimeErrors(struct tm *datetimeStruct);
struct DateStruct parseDate(struct DatetimeModule datetimeArguments);
struct TimeStruct parseTime(struct DatetimeModule datetimeArguments);
char* generateDateString(struct tm datetimeStruct, struct DatetimeModule datetimeArguments, char *outputBuffer);
void incrementClockSecond(struct tm *datetimeStruct);
bool checkIfDateAndTimeSegmentsAreDigits(char *customTime);

#endif