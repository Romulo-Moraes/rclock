#include <helpers/design.h>
#include <public/design.h>
#include <ncurses.h>

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