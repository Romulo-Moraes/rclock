/*
 * Datetime module: A module for date/time operations
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef DATETIME_GUARD
#define DATETIME_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "errors.h"

#define MAX_CLOCK_DATE_BUFFER_LEN 512
#define SLEEP_TIME_IN_NANOSECONDS 250000000L

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
void setNewTime(struct tm *datetimeStruct, struct DatetimeModuleArguments dateTimeArguments, char *errorOutput);
void setNewDate(struct tm *datetimeStruct, struct DatetimeModuleArguments datetimeArguments, char *errorOutput);
char* generateDateString(struct tm datetimeStruct, struct DatetimeModuleArguments datetimeArguments, char *outputBuffer);
void incrementClockSecond(struct tm *datetimeStruct);
void decrementClockSecond(struct tm *datetimeStruct);
void sleepClock(unsigned int milliseconds);
void verifyForDateAndTimeErrors(struct tm *datetimeStruct, char *errorOutput);
void saveInitialProgramTime(struct tm *finalDatetime);
void tryToUpdateTheClock(struct tm *timeStruct);

#endif