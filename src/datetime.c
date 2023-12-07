#include "./../include/datetime.h"

struct tm* generateDateAndTime(){
    time_t currentTime = time(NULL);
    
    struct tm *timeStruct = localtime(&currentTime);

    return timeStruct;
}

void setNewTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments){
    struct TimeStruct parsedTime;

    if(dateTimeArguments.customTime != NULL){
        parsedTime = parseTime(dateTimeArguments);

        if(parsedTime.error != true){
            datetimeStruct->tm_hour = parsedTime.hours;
            datetimeStruct->tm_min = parsedTime.minutes;
            datetimeStruct->tm_sec = parsedTime.seconds;
        }else{
            generateErrorMessage(CUSTOM_TIME_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

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

void setNewDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments){
    struct DateStruct parsedDate;

    if(datetimeArguments.customDate != NULL){
        parsedDate = parseDate(datetimeArguments);

        if(parsedDate.error != true){
            datetimeStruct->tm_mday = parsedDate.day;
            datetimeStruct->tm_mon = parsedDate.month - 1;
            datetimeStruct->tm_year = parsedDate.year - 1900;
        }else{
            generateErrorMessage(CUSTOM_DATE_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

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

bool verifyForDateAndTimeErrors(struct tm *datetimeStruct){
    struct tm datetimeStructCopy = *datetimeStruct;

    mktime(datetimeStruct);

    if(datetimeStruct->tm_mday != datetimeStructCopy.tm_mday || datetimeStruct->tm_mon != datetimeStructCopy.tm_mon || datetimeStruct->tm_year != datetimeStructCopy.tm_year){
        generateErrorMessage(CUSTOM_DATE_RANGE, USELESS_ERROR_MESSAGE_ARGUMENTS);
    }

    if(datetimeStruct->tm_hour != datetimeStructCopy.tm_hour || datetimeStruct->tm_min != datetimeStructCopy.tm_min || datetimeStruct->tm_sec != datetimeStructCopy.tm_sec){
        generateErrorMessage(CUSTOM_TIME_RANGE, USELESS_ERROR_MESSAGE_ARGUMENTS);
    }
}

bool checkIfDateAndTimeSegmentsAreDigits(char *customDateTime){
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

struct DateStruct parseDate(struct DatetimeModule datetimeArguments){
    struct DateStruct fetchedDate = {0};
    int parsedDateItems;

    if(strlen(datetimeArguments.customDate) == 10){
        if(checkIfDateAndTimeSegmentsAreDigits(datetimeArguments.customDate) == true){
            parsedDateItems = sscanf(datetimeArguments.customDate, "%d/%d/%d", &fetchedDate.day, &fetchedDate.month, &fetchedDate.year);

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