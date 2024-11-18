/*
 * Datetime module: A module for date/time operations
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <private/datetime.h>

char *_createZerosPaddingForTheYear(int year, char *outputPadding){
    size_t digitsCount = 0;

    year += 1900;

    while(year > 0){
        year /= 10;
        digitsCount++;
    }

    if(digitsCount < 4){
        memset(outputPadding, '0', 4 - digitsCount);
    }

    return outputPadding;
}

// This function will validate the full date and the
// full time given by the user. Both values have a similar
// structure that is xx?xx?xx(xx). Examples: 12:12:12 and 01/01/1970
bool _checkIfDateOrTimesSegmentsAreDigits(char *customDateTime){
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
struct DateStruct _parseDate(struct DatetimeModule datetimeArguments){
    struct DateStruct fetchedDate = {0};
    int parsedDateItems;

    if(strlen(datetimeArguments.customDate) == 10){
        if(_checkIfDateOrTimesSegmentsAreDigits(datetimeArguments.customDate) == true){
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

struct TimeStruct _parseTime(struct DatetimeModule datetimeArguments){
    struct TimeStruct fetchedTime = {0};
    int fetchedTimeItems;

    if(strlen(datetimeArguments.customTime) == 8){
        if(_checkIfDateOrTimesSegmentsAreDigits(datetimeArguments.customTime) == true){
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

void _setCustomTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput){
    struct TimeStruct parsedTime;

    if(dateTimeArguments.customTime != NULL){
        parsedTime = _parseTime(dateTimeArguments);

        if(parsedTime.error != true){
            datetimeStruct->tm_hour = parsedTime.hours;
            datetimeStruct->tm_min = parsedTime.minutes;
            datetimeStruct->tm_sec = parsedTime.seconds;
        }else{
            generateErrorMessage(CUSTOM_TIME_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void _setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments){
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

void _setCustomDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput){
    struct DateStruct parsedDate;

    if(datetimeArguments.customDate != NULL){
        parsedDate = _parseDate(datetimeArguments);

        if(parsedDate.error != true){
            datetimeStruct->tm_mday = parsedDate.day;
            datetimeStruct->tm_mon = parsedDate.month - 1;
            datetimeStruct->tm_year = parsedDate.year - 1900;
        }else{
            generateErrorMessage(CUSTOM_DATE_FORMAT, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void _setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments){

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