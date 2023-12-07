#include "./../../include/global-includes.h"
#include "./../../include/arguments.h"
#include "./../../include/shapes.h"
#include "./../../include/screen-manager.h"
#include "./../../include/design.h"
#include "./../../include/errors.h"
#include "./../../include/colors.h"
#include "./../../include/datetime.h"

int main(void){
    struct tm *theTime = generateDateAndTime(), timeClone = *theTime;
    struct DatetimeModule customArgs = {.customDate = "01/02/2022", .customTime = "11:11:11", .customHour = UNDEFINED, .customMinute = UNDEFINED, .customSecond = UNDEFINED, .customDay = UNDEFINED, .customMonth = UNDEFINED, .customYear = UNDEFINED};
    char dateBuffer[MAX_CLOCK_DATE_BUFFER_LEN + 1];
    struct TimeStruct t = parseTime(customArgs);


    printf("Printing the time: %s", asctime(theTime));
    printf("parseTime() result: %d %d %d %u\n", t.hours, t.minutes, t.seconds, t.error);

    setNewTime(&timeClone, customArgs);
    printf("setNewTime() with full time: %s", asctime(&timeClone));
    
    timeClone = *theTime;
    customArgs.customTime = NULL;
    customArgs.customHour = 5;

    setNewTime(&timeClone, customArgs);
    printf("setNewTime() with custom hour: %s", asctime(&timeClone));

    customArgs.customMinute = 9;
    setNewTime(&timeClone, customArgs);
    printf("setNewTime() with custom minute: %s", asctime(&timeClone));

    customArgs.customSecond = 2;
    setNewTime(&timeClone, customArgs);
    printf("setNewTime() with custom second: %s", asctime(&timeClone));

    customArgs.customTime = "11:11:11";
    setNewTime(&timeClone, customArgs);
    printf("setNewTime() with custom time and custom segments: %s", asctime(&timeClone));

    printf("checkIfDateAndTimeSegmentsAreDigits() result: %hhu\n", checkIfDateAndTimeSegmentsAreDigits("11:11:11"));
    printf("checkIfDateAndTimeSegmentsAreDigits() result: %hhu\n", checkIfDateAndTimeSegmentsAreDigits("01/02/0300"));
    printf("checkIfDateAndTimeSegmentsAreDigits() result: %hhu\n", checkIfDateAndTimeSegmentsAreDigits("12/0a/1952"));
    printf("checkIfDateAndTimeSegmentsAreDigits() result: %hhu\n", checkIfDateAndTimeSegmentsAreDigits("11:f9:15"));

    struct DateStruct d = parseDate(customArgs);
    printf("parseDate() result: %hhu %hhu %d %hhu\n", d.day, d.month, d.year, d.error);

    setNewDate(&timeClone, customArgs);
    printf("setNewDate() with full date: %s", asctime(&timeClone));

    timeClone = *theTime;
    customArgs.customDate = NULL;
    customArgs.customDay = 3;
    setNewDate(&timeClone, customArgs);
    printf("setNewDate() with custom day: %s", asctime(&timeClone));

    customArgs.customMonth = 8;
    setNewDate(&timeClone, customArgs);
    printf("setNewDate() with custom month: %s", asctime(&timeClone));

    customArgs.customYear = 3;
    setNewDate(&timeClone, customArgs);
    printf("setNewDate() with custom year: %s", asctime(&timeClone));

    printf("generateDateString() result: %s\n", generateDateString(*theTime, customArgs, dateBuffer));

    puts("=-=-=-=-=-=-=Incrementing clock second=-=-=-=-=-=-=");

    timeClone = *theTime;

    for(int i = 0; i < 10; i++){
        incrementClockSecond(&timeClone);
        printf("%s", asctime(&timeClone));
    }

    return 0;
}