#include "../include/global-includes.h"
#include "../include/arguments.h"
#include "../include/screen-manager.h"
#include "../include/design.h"
#include "../include/datetime.h"

#define DATE "Wednesday, 10 Dec 2023"

int main(int argc, char *argv[]){

    ProgramArguments arguments = fetchProgramArguments();
    time_t currentTime = time(NULL);
    struct tm *timeStruct = localtime(&currentTime);
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

    setDateStringLength(sizeof(DATE));
    drawDate(timeStruct, arguments.datetime);

    moveWindowsToPlaceholders();

    for(short i = 0; i < possibleSegmentsLen; i++){
        segment = getClockSegment(possibleSegments[i]);

        switch(possibleSegments[i]){
            case HOURS_SEGMENT:
                fillClockSegment(segment, timeStruct->tm_hour);
                break;
            case MINUTES_SEGMENT:
                fillClockSegment(segment, timeStruct->tm_min);
                break;
            case SECONDS_SEGMENT:
                fillClockSegment(segment, timeStruct->tm_sec);
                break;
        }
    }

    fillClockColons();

    refresh();
    refreshWindows();
    

    getch();

    endwin();

    return EXIT_SUCCESS;
}