#include "../include/global-includes.h"
#include "../include/arguments.h"
#include "../include/screen-manager.h"
#include "../include/design.h"
#include "../include/datetime.h"

struct tm *timeStruct;

void signalHandler(int signal);

int main(int argc, char *argv[]){
    ProgramArguments arguments = fetchProgramArguments();
    timeStruct = generateDateAndTime();
    struct tm timeStructCopy = *timeStruct;
    char errorBuffer[512];

    initscr();
    cbreak();
    start_color();
    use_default_colors();
    curs_set(0);

    loadBuiltinColors();

    setComponentsColors(arguments.colors, errorBuffer);

    generateWindows(arguments.DatetimeScreenManagerDesigner);
    setPlaceHolders();

    drawDate(timeStruct, arguments.datetime, arguments.colors);

    moveTimeWindowsToPlaceholders();
    moveDateWindowToPlaceholder();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner);

    signal(SIGALRM, signalHandler);

    alarm(1);

    while(true){
        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
            wclear(stdscr);
            refresh();
            setPlaceHolders();
            moveTimeWindowsToPlaceholders();
            moveDateWindowToPlaceholder();

            drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner);

            drawDate(timeStruct, arguments.datetime, arguments.colors);
        }



        // The main loop run more than once in a second
        // there's no need of run this everytime
        if(timeStruct->tm_sec != timeStructCopy.tm_sec){

            if(timeStruct->tm_hour != timeStructCopy.tm_hour)
                fillClockSegment(getClockSegment(HOURS_SEGMENT), timeStruct->tm_hour);
        
            if(timeStruct->tm_min != timeStructCopy.tm_min)
                fillClockSegment(getClockSegment(MINUTES_SEGMENT), timeStruct->tm_min);

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