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
    WINDOW **segment;
    SegmentIndex possibleSegments[] = {HOURS_SEGMENT, MINUTES_SEGMENT, SECONDS_SEGMENT};
    char errorBuffer[512];
    size_t possibleSegmentsLen = sizeof(possibleSegments) / sizeof(possibleSegments[0]);

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

    drawAllClockWindows(timeStruct);

    signal(SIGALRM, signalHandler);

    alarm(1);

    while(true){
        if(detectTerminalResizes()){
            wclear(stdscr);
            refresh();
            setPlaceHolders();
            moveTimeWindowsToPlaceholders();
            moveDateWindowToPlaceholder();

            drawAllClockWindows(timeStruct);

            drawDate(timeStruct, arguments.datetime, arguments.colors);
        }


        if(timeStruct->tm_sec != timeStructCopy.tm_sec){
            for(short i = 0; i < possibleSegmentsLen; i++){
                segment = getClockSegment(possibleSegments[i]);

                switch(possibleSegments[i]){
                    case HOURS_SEGMENT:
                        if(timeStruct->tm_hour != timeStructCopy.tm_hour)
                            fillClockSegment(segment, timeStruct->tm_hour);
                        break;
                    case MINUTES_SEGMENT:
                        if(timeStruct->tm_min != timeStructCopy.tm_min)
                            fillClockSegment(segment, timeStruct->tm_min);
                        break;
                    case SECONDS_SEGMENT:
                            fillClockSegment(segment, timeStruct->tm_sec);
                        break;
                }
            }
        }


        refresh();
        refreshWindows();

        timeStructCopy = *timeStruct;
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