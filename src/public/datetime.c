#include "./../../include/public/datetime.h"
#include "./../../include/private/datetime.h"

static struct tm initialOfficialTime;
static struct tm initialProgramTime;
static bool customDatetimeGiven = false;

// Public functions

struct tm* generateDateAndTime(){
    time_t currentTime = time(NULL);
    
    struct tm *timeStruct = localtime(&currentTime);

    return timeStruct;
}


void saveInitialProgramTime(struct tm *finalDatetime){
    time_t tm;

    tm = mktime(finalDatetime);
    initialProgramTime = *localtime(&tm);
}

// Wrapper procedure to set custom time
void setNewTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput){
    
    time_t now;

    // The time arguments have priority order, from specific to general

    // Set new time by xx:xx:xx format    
    _setCustomTime(datetimeStruct, dateTimeArguments, errorOutput);

    // Set new time by specifying each clock segment
    _setCustomHourMinuteAndSecond(datetimeStruct, dateTimeArguments);
    
    // Saving the initial time
    if(memcmp(&initialOfficialTime, &(struct tm){0}, sizeof(struct tm)) == 0 && (dateTimeArguments.customTime != NULL || dateTimeArguments.customHour != UNDEFINED || dateTimeArguments.customMinute != UNDEFINED || dateTimeArguments.customSecond != UNDEFINED)){
        now = time(NULL);
        initialOfficialTime = *localtime(&now);
        customDatetimeGiven = true;
    }
}

// Wrapper procedure to set custom date
void setNewDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput){
    time_t now;

    // The date arguments have priority order, from specific to general

    // Set new date by DD/MM/YYY format
    _setCustomDate(datetimeStruct, datetimeArguments, errorOutput);

    // Set new date by specifying the day, month and year
    _setCustomDayMonthAndYear(datetimeStruct, datetimeArguments);

    // Saving the initial time
    if(memcmp(&initialOfficialTime, &(struct tm){0}, sizeof(struct tm)) == 0 && (datetimeArguments.customDate != NULL || datetimeArguments.customDay != UNDEFINED || datetimeArguments.customMonth != UNDEFINED || datetimeArguments.customYear != UNDEFINED)){
        now = time(NULL);
        initialOfficialTime = *localtime(&now);
        customDatetimeGiven = true;
    }
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

void tryToUpdateTheClock(struct tm *timeStruct){
    time_t programTime;
    time_t officialTime;
    time_t now;
    double diff;
    double diff2;


    now = time(NULL);

    if(customDatetimeGiven == true){

        programTime = mktime(&initialProgramTime);
        officialTime = mktime(&initialOfficialTime);
        diff = difftime(now, officialTime);
        diff2 = difftime(mktime(timeStruct), programTime);
    
    
        if(diff > diff2 + 5){
            timeStruct->tm_sec += difftime(diff, diff2);

            mktime(timeStruct);
        }
    }else{
        *timeStruct = *localtime(&now);
    }
    
}