#include "./../include/datetime.h"

// Forward declarations
bool checkIfDateOrTimesSegmentsAreDigits(char *customDateTime);
struct DateStruct parseDate(struct DatetimeModule datetimeArguments);
struct TimeStruct parseTime(struct DatetimeModule datetimeArguments);
void setCustomTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput);
void setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments);
void setCustomDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput);
void setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments);
void verifyForDateAndTimeErrors(struct tm *datetimeStruct, char *errorOutput);

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
    setCustomTime(datetimeStruct, dateTimeArguments, errorOutput);

    // Set new time by specifying each clock segment
    setCustomHourMinuteAndSecond(datetimeStruct, dateTimeArguments);
}

// Wrapper procedure to set custom date
void setNewDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput){
    
    // The date arguments have priority order, from specific to general

    // Set new date by DD/MM/YYY format
    setCustomDate(datetimeStruct, datetimeArguments, errorOutput);

    // Set new date by specifying the day, month and year
    setCustomDayMonthAndYear(datetimeStruct, datetimeArguments);
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

void sleepClock(){
    struct timespec sleepTime, t;

    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = SLEEP_TIME_IN_NANOSECONDS;

    nanosleep(&sleepTime, &t);
}

// Private functions

// This function will validate the full date and the
// full time given by the user. Both values have a similar
// structure that is xx?xx?xx(xx). Examples: 12:12:12 and 01/01/1970
bool checkIfDateOrTimesSegmentsAreDigits(char *customDateTime){
    size_t dateTimeLen = strlen(customDateTime);

    for(int i = 0; i < dateTimeLen; i++){
        if(i != 2 && i != 5){
            if(!isdigit(customDateTime[i])){
                return false;
            }
        }
    }
    
    return true;
}

// This function parses the date given with the DD/MM/YYYY format.
// string length and digits checking are used to make sure that it is
// a valid value
struct DateStruct parseDate(struct DatetimeModule datetimeArguments){
    struct DateStruct fetchedDate = {0};
    int parsedDateItems;

    if(strlen(datetimeArguments.customDate) == 10){
        if(checkIfDateOrTimesSegmentsAreDigits(datetimeArguments.customDate) == true){
            parsedDateItems = sscanf(datetimeArguments.customDate, "%hhu/%hhu/%u", &fetchedDate.day, &fetchedDate.month, &fetchedDate.year);

            if(parsedDateItems != 3){
                fetchedDate.error = true;
            }
        }else{
            fetchedDate.error = true;
        }
    }else{
        fetchedDate.error = true;
    }

    return fetchedDate;
}

struct TimeStruct parseTime(struct DatetimeModule datetimeArguments){
    struct TimeStruct fetchedTime = {0};
    int fetchedTimeItems;

    if(strlen(datetimeArguments.customTime) == 8){
        if(checkIfDateAndTimeSegmentsAreDigits(datetimeArguments.customTime) == true){
            fetchedTimeItems = sscanf(datetimeArguments.customTime, "%hhu:%hhu:%hhu", &fetchedTime.hours, &fetchedTime.minutes, &fetchedTime.seconds);

            if(fetchedTimeItems != 3){
                fetchedTime.error = true;
            }
        }else{
            fetchedTime.error = true;
        }
    }else{
        fetchedTime.error = true;
    }

    return fetchedTime;
}

void setCustomTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput){
    struct TimeStruct parsedTime;

    if(dateTimeArguments.customTime != NULL){
        parsedTime = parseTime(dateTimeArguments);

        if(parsedTime.error != true){
            datetimeStruct->tm_hour = parsedTime.hours;
            datetimeStruct->tm_min = parsedTime.minutes;
            datetimeStruct->tm_sec = parsedTime.seconds;
        }else{
            generateErrorMessage(CUSTOM_TIME_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments){
    if(dateTimeArguments.customHour != UNDEFINED){
        datetimeStruct->tm_hour = dateTimeArguments.customHour;
    }

    if(dateTimeArguments.customMinute != UNDEFINED){
        datetimeStruct->tm_min = dateTimeArguments.customMinute;
    }

    if(dateTimeArguments.customSecond != UNDEFINED){
        datetimeStruct->tm_sec = dateTimeArguments.customSecond;
    }
}

void setCustomDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput){
    struct DateStruct parsedDate;

    if(datetimeArguments.customDate != NULL){
        parsedDate = parseDate(datetimeArguments);

        if(parsedDate.error != true){
            datetimeStruct->tm_mday = parsedDate.day;
            datetimeStruct->tm_mon = parsedDate.month - 1;
            datetimeStruct->tm_year = parsedDate.year - 1900;
        }else{
            generateErrorMessage(CUSTOM_DATE_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments){

    if(datetimeArguments.customDay != UNDEFINED){
        datetimeStruct->tm_mday = datetimeArguments.customDay;
    }

    if(datetimeArguments.customMonth != UNDEFINED){
        datetimeStruct->tm_mon = datetimeArguments.customMonth - 1;
    }

    if(datetimeArguments.customYear != UNDEFINED){
        datetimeStruct->tm_year = datetimeArguments.customYear - 1900;
    }
}

// Normalize a copy of the datetime struct and check if both are equal,
// if they aren't equal, the new date/time given by the user is out of range
void verifyForDateAndTimeErrors(struct tm *datetimeStruct, char *errorOutput){
    struct tm datetimeStructCopy = *datetimeStruct;

    mktime(datetimeStruct);

    if(datetimeStruct->tm_mday != datetimeStructCopy.tm_mday || datetimeStruct->tm_mon != datetimeStructCopy.tm_mon || datetimeStruct->tm_year != datetimeStructCopy.tm_year){
        generateErrorMessage(CUSTOM_DATE_RANGE, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
    }

    if(datetimeStruct->tm_hour != datetimeStructCopy.tm_hour || datetimeStruct->tm_min != datetimeStructCopy.tm_min || datetimeStruct->tm_sec != datetimeStructCopy.tm_sec){
        generateErrorMessage(CUSTOM_TIME_RANGE, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
    }
}