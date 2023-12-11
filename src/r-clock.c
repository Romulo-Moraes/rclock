#include "../include/global-includes.h"
#include "../include/arguments.h"
#include "../include/screen-manager.h"
#include "../include/design.h"
#include "../include/datetime.h"

struct tm *timeStruct;

void signalHandler(int signal);
void redrawTheEntireClock(ProgramArguments arguments, ClockState clocksSizeState){
    wclear(stdscr);
    refresh();
    setPlaceHolders();
    moveTimeWindowsToPlaceholders();
    moveDateWindowToPlaceholder();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, clocksSizeState);

    drawDate(timeStruct, arguments.datetime, arguments.colors);

    printw("sijjfsdijfdsui");
}

int main(int argc, char *argv[]){
    ProgramArguments arguments = fetchProgramArguments();
    timeStruct = generateDateAndTime();
    struct tm timeStructCopy = *timeStruct;
    char errorBuffer[512];
    ClockState clocksSizeState;

    initscr();
    cbreak();
    start_color();
    use_default_colors();
    curs_set(0);

    loadBuiltinColors();

    setComponentsColors(arguments.colors, errorBuffer);

    loadInitialTerminalSize();  

    generateWindows(arguments.DatetimeScreenManagerDesigner);

    hideAndShowSecondsIfTerminalsTooSmall();

    setPlaceHolders();

    showErrorMessageIfTerminalIsExtremelySmall(arguments.DatetimeScreenManagerDesigner);

    drawDate(timeStruct, arguments.datetime, arguments.colors);

    moveTimeWindowsToPlaceholders();
    moveDateWindowToPlaceholder();

    signal(SIGALRM, signalHandler);

    alarm(1);

    if(arguments.DatetimeScreenManagerDesigner.hideTheSeconds == false)
        clocksSizeState = hideAndShowSecondsIfTerminalsTooSmall();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, clocksSizeState);

    while(true){

        if(showErrorMessageIfTerminalIsExtremelySmall(arguments.DatetimeScreenManagerDesigner) == true){
            clocksSizeState = hideAndShowSecondsIfTerminalsTooSmall();;
            redrawTheEntireClock(arguments, clocksSizeState);

            refreshWindows();
        }

        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){

            if(arguments.DatetimeScreenManagerDesigner.hideTheSeconds == false){
                clocksSizeState = hideAndShowSecondsIfTerminalsTooSmall();
            }            

           redrawTheEntireClock(arguments, clocksSizeState);
        }

       

        // The main loop run more than once in a second
        // there's no need of run this everytime
        if(timeStruct->tm_sec != timeStructCopy.tm_sec){

            if(timeStruct->tm_hour != timeStructCopy.tm_hour)
                fillClockSegment(getClockSegment(HOURS_SEGMENT), timeStruct->tm_hour);
        
            if(timeStruct->tm_min != timeStructCopy.tm_min)
                fillClockSegment(getClockSegment(MINUTES_SEGMENT), timeStruct->tm_min);

            if(clocksSizeState != SMALL_CLOCK && arguments.DatetimeScreenManagerDesigner.hideTheSeconds != true)
                fillClockSegment(getClockSegment(SECONDS_SEGMENT), timeStruct->tm_sec);
        }


        refresh();
        refreshWindows();

        timeStructCopy = *timeStruct;

        // Sleeps for SLEEP_TIME_IN_NANOSECONDS nano seconds
        sleepClock();
    }    

    endwin();

    return EXIT_SUCCESS;
}

void signalHandler(int signal){
    switch(signal){
        case SIGALRM:
            incrementClockSecond(timeStruct);
            alarm(1);
            break;
    }
}