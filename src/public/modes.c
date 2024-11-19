#include <public/pomodoro.h>
#include <public/arguments.h>
#include <public/design.h>

static void updateClock(struct tm timeStruct, struct tm timeStructOldValue){
    WINDOW *segmentToFill[2];

    if(timeStruct.tm_hour != timeStructOldValue.tm_hour)
        fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct.tm_hour, HOURS_INDEX, BACKGROUND_TRANSPARENT_ID);
    if(timeStruct.tm_min != timeStructOldValue.tm_min)
        fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct.tm_min, MINUTES_INDEX, BACKGROUND_TRANSPARENT_ID);
    if(checkIfTheSecondsIsVisible() == true)
        fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct.tm_sec, SECONDS_INDEX, BACKGROUND_TRANSPARENT_ID);
}

void pomodoroMode(struct tm *timeStruct, struct tm *timeStructOldValue, void (*timeoutHandler)(int)){
    if(timeStruct->tm_sec != timeStructOldValue->tm_sec){
        updateClock(*timeStruct, *timeStructOldValue);
        
        *timeStructOldValue = *timeStruct;

        if (timeStruct->tm_min == 0 && timeStruct->tm_sec == 0) {
            signal(SIGALRM, timeoutHandler);
            setTimeout(POMODORO_TIMEOUT);
            drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
            return;
        }
    }
}

void clockMode(struct DatetimeModuleArguments datetime, struct ColorsModuleArguments colors, struct tm timeStruct, struct tm timeStructOldValue) {

    if(timeStruct.tm_sec != timeStructOldValue.tm_sec){

        updateClock(timeStruct, timeStructOldValue);

        if(timeStruct.tm_hour < timeStructOldValue.tm_hour){
            mktime(&timeStruct);
            drawDate(&timeStruct, datetime, colors);
        }
                
        // Making both have the same value for the next alarm
        timeStructOldValue = timeStruct;
    }

}