#include "./../../include/public/datetime.h"
#include "./../../include/private/datetime.h"

// Public functions

struct tm* generateDateAndTime(){
    time_t currentTime = time(NULL);
    
    struct tm *timeStruct = localtime(&currentTime);

    return timeStruct;
}

// Wrapper procedure to set custom time
void setNewTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput){
    
    // The time arguments have priority order, from specific to general

    // Set new time by xx:xx:xx format    
    _setCustomTime(datetimeStruct, dateTimeArguments, errorOutput);

    // Set new time by specifying each clock segment
    _setCustomHourMinuteAndSecond(datetimeStruct, dateTimeArguments);
}

// Wrapper procedure to set custom date
void setNewDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput){
    
    // The date arguments have priority order, from specific to general

    // Set new date by DD/MM/YYY format
    _setCustomDate(datetimeStruct, datetimeArguments, errorOutput);

    // Set new date by specifying the day, month and year
    _setCustomDayMonthAndYear(datetimeStruct, datetimeArguments);
}

// Function that returns the date that will be shown below the clock
// if the user provided a custom date format, the new format will be
// used instead of the default one
char* generateDateString(struct tm datetimeStruct, struct DatetimeModule datetimeArguments, char *outputBuffer){
    if(datetimeArguments.dateFormat != NULL){
        strftime(outputBuffer, MAX_CLOCK_DATE_BUFFER_LEN, datetimeArguments.dateFormat, &datetimeStruct);
    }else{
        strftime(outputBuffer, MAX_CLOCK_DATE_BUFFER_LEN, "%A, %b %d %Y", &datetimeStruct);
    }

    return outputBuffer;
}

void incrementClockSecond(struct tm *datetimeStruct){
    datetimeStruct->tm_sec += 1;

    if(datetimeStruct->tm_sec >= 60){
        mktime(datetimeStruct);
    }
}

void sleepClock(unsigned int milliseconds){
    int sleepStatus;
    struct timespec sleepTime, remainingTime;

    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = milliseconds * 1000000;

    do{
        sleepStatus = nanosleep(&sleepTime, &remainingTime);

        sleepTime.tv_sec = 0;
        sleepTime.tv_nsec = remainingTime.tv_nsec;
    }while(sleepStatus != 0);
}
