#include <helpers/design.h>
#include <public/design.h>
#include <ncurses.h>

int lastSecondsIsVisibleStateValue = -1;

// This subroutine is always called after a possible program error that is recoverable,
// if necessary, it will destroy the clock windows and recreate again, else it will 
// just update the windows to display the time again
void redrawTheEntireClock(ProgramArguments arguments, bool destroyTheWindows, struct tm *timeStruct){

    wclear(stdscr);
    refresh();

    if(destroyTheWindows){
        destroyRclockWindows(arguments);
        generateWindows(arguments.DatetimeScreenManagerDesigner, arguments.mode);
    }
    
    setPlaceHolders(arguments);
    moveTimeWindowsToPlaceholders();

    if(checkIfTheDateIsVisible() == true){
        moveDateWindowToPlaceholder();
    }

    refreshWindows();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, BACKGROUND_TRANSPARENT_ID);

    if(checkIfTheDateIsVisible() == true){
        drawDate(timeStruct, arguments.datetime, arguments.colors);
    }

    if (arguments.mode == POMODORO_MODE) {
        moveOptionsWindowToPlaceholder();
        movePomodoroStatusWindowToPlaceholder();
        drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    }

    refreshWindows();
    refresh();
}

void updateClock(struct tm timeStruct, struct tm timeStructOldValue, RclockMode mode){
    WINDOW *segmentToFill[2];

    if (lastSecondsIsVisibleStateValue == -1)
        lastSecondsIsVisibleStateValue = checkIfTheSecondsIsVisible();

    if (mode == POMODORO_MODE && checkIfTheSecondsIsVisible() == false) {
        if(timeStruct.tm_min != timeStructOldValue.tm_min || lastSecondsIsVisibleStateValue != checkIfTheSecondsIsVisible())
            fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct.tm_min, HOURS_INDEX, BACKGROUND_TRANSPARENT_ID);
        if(timeStruct.tm_sec != timeStructOldValue.tm_sec)
            fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct.tm_sec, MINUTES_INDEX, BACKGROUND_TRANSPARENT_ID);            
        
//        fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), 0, SECONDS_INDEX, BACKGROUND_TRANSPARENT_ID);
    } else {
        if(timeStruct.tm_hour != timeStructOldValue.tm_hour)
            fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct.tm_hour, HOURS_INDEX, BACKGROUND_TRANSPARENT_ID);
        if(timeStruct.tm_min != timeStructOldValue.tm_min)
            fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct.tm_min, MINUTES_INDEX, BACKGROUND_TRANSPARENT_ID);
        if(checkIfTheSecondsIsVisible() == true)
            fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct.tm_sec, SECONDS_INDEX, BACKGROUND_TRANSPARENT_ID);
    }
    
}