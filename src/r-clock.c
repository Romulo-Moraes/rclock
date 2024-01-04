#include "../include/public/global-includes.h"
#include "../include/public/arguments.h"
#include "../include/public/screen-manager.h"
#include "../include/public/design.h"
#include "../include/public/datetime.h"

struct tm timeStruct;

void signalHandler(int signal);
void redrawTheEntireClock(ProgramArguments arguments, bool destroyTheWindows);
void configureNcurses();
void configureRclock(ProgramArguments arguments, char *errorBuffer);
void checkIfTheClockShouldBeSmaller(struct DatetimeScreenManagerDesignerModules arguments);
struct TerminalSizeError checkIfTerminalSizeIsCritical(ProgramArguments arguments);
void initializeTheClock(ProgramArguments arguments);
void createTerminalSizeError(struct TerminalSizeError sizeError);
void setCustomDateAndTime(ProgramArguments arguments);

int main(int argc, char *argv[]){
    ProgramArguments arguments;
    anemone_struct anemone;
    timeStruct = *generateDateAndTime();
    struct tm timeStructCopy = timeStruct;
    char errorBuffer[512];
    struct TerminalSizeError sizeError;
    bool windowsNeedToBeDestroyed;
    WINDOW *segmentToFill[2];

    anemone = createProgramArguments(argc, argv);
    
    arguments = fetchProgramArguments(&anemone, errorBuffer);

    setCustomDateAndTime(arguments);

    configureNcurses();
    configureRclock(arguments, errorBuffer);

    initializeTheClock(arguments);

    // The seconds aren't updated by a loop, the alarm signal
    // will trigger a procedure for each second, and that
    // procedure will update the time struct
    alarm(1);

    while(getch() != 10){
        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
        
            windowsNeedToBeDestroyed = false;

            // A loop to check if the terminal size is safe to render the clock
            do{
                sizeError = checkIfTerminalSizeIsCritical(arguments);

                if(sizeError.thereIsAnError == true){
                    // Issue an error if the size isn't safe
                    createTerminalSizeError(sizeError);

                    windowsNeedToBeDestroyed = true;
                }

            }while(sizeError.thereIsAnError == true);

            // This procedure will manipulate flags that will tell
            // the screen-manager and designer modules that the
            // clock's date or seconds must be hidden
            checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner);

            // After each error screen, the clock is redraw
            redrawTheEntireClock(arguments, windowsNeedToBeDestroyed);
        }else{

            // Every time that the alarm triggers the procedure 
            // that update the seconds, the timeStruct will be 
            // compared with its older version, the timeStructCopy,
            // if both are different, the clock is updated
            if(timeStruct.tm_sec != timeStructCopy.tm_sec){

                if(timeStruct.tm_hour != timeStructCopy.tm_hour)
                    fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct.tm_hour, HOURS_INDEX);
        
                if(timeStruct.tm_min != timeStructCopy.tm_min)
                    fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct.tm_min, MINUTES_INDEX);

                if(checkIfTheSecondsIsVisible() == true){
                    fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct.tm_sec, SECONDS_INDEX);
                }

                if(timeStruct.tm_hour < timeStructCopy.tm_hour){
                    mktime(&timeStruct);
                    drawDate(&timeStruct, arguments.datetime, arguments.colors);
                }
                
                // Making both have the same value for the next alarm
                timeStructCopy = timeStruct;
            }

        }

        refreshWindows();
        refresh();

        // Sleeps for milliseconds
        sleepClock(50);
    }    

    endwin();

    return EXIT_SUCCESS;
}

// Calls a couple of functions that will load
// all features that the Rclock requires
void configureNcurses(){
    initscr();
    raw();
    noecho();
    start_color();
    use_default_colors();
    curs_set(0);
    timeout(100);
}

// Calls a couple of functions that will load
// default values and populate control variables
void configureRclock(ProgramArguments arguments, char *errorBuffer){
    loadBuiltinColors();
    setComponentsColors(arguments.colors, errorBuffer);
    loadInitialTerminalSize();
    setValuesForClockStates(arguments);
    signal(SIGALRM, signalHandler);
}

void initializeTheClock(ProgramArguments arguments){
    struct TerminalSizeError sizeError;
    
    generateWindows(arguments.DatetimeScreenManagerDesigner);

    setPlaceHolders(arguments);

    checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner);

    do{
        sizeError = checkIfTerminalSizeIsCritical(arguments);

        if(sizeError.thereIsAnError == true){
            createTerminalSizeError(sizeError);
        }
    }while(sizeError.thereIsAnError == true);
    

    moveTimeWindowsToPlaceholders();
    

    if(checkIfTheDateIsVisible() == true){
        drawDate(&timeStruct, arguments.datetime, arguments.colors);
        moveDateWindowToPlaceholder();
    }
    
    refresh();

    drawAllClockWindows(&timeStruct, arguments.DatetimeScreenManagerDesigner);

}


// Create and call update routines to show an error screen 
// of a terminal size trouble
void createTerminalSizeError(struct TerminalSizeError sizeError){
    char errorBuffer[512];
    struct ErrorWindows errorWindows;
    struct ErrorUpdateCallbacksArguments callbackArguments;

    errorWindows =  generateErrorWindows(0.75, false);

    generateErrorMessage(sizeError.errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer);

    callbackArguments = (struct ErrorUpdateCallbacksArguments){.windows = errorWindows, .errorMsg = errorBuffer, .exitErrorMsg = NULL};

    updateErrorMessageFrames(errorWindows, 0.75, errorBuffer, drawProgramErrorCallback, &callbackArguments, sizeError.validationCallback, false);
}

// Procedure that handle all signal that the
// program may receive
void signalHandler(int signal){
    switch(signal){
        // The SIGALRM is the signal that is
        // triggered once in 1 second and
        // update the time struct
        case SIGALRM:
            incrementClockSecond(&timeStruct);
            
            if(timeStruct.tm_sec % 5 == 0){
                tryToUpdateTheClock(&timeStruct);
            }

            alarm(1);
            break;
    }
}

// Function used to generate a terminal size error, it is 
// basically a wrapper that calls two other functions that
// check both width and height. Zero or one error is given by
// a call to this function.
struct TerminalSizeError checkIfTerminalSizeIsCritical(ProgramArguments arguments){
    struct TerminalSizeError errorStruct;

    errorStruct.thereIsAnError = false;

    if(checkIfTerminalWidthIsCritical(NULL) == true){
        errorStruct = (struct TerminalSizeError){.thereIsAnError = true, .errorID = TERMINAL_WIDTH_TOO_SMALL, .validationCallback = checkIfTerminalWidthIsCritical};
    }else if(checkIfTerminalHeightIsCritical(&arguments.DatetimeScreenManagerDesigner) == true){
        errorStruct = (struct TerminalSizeError){.thereIsAnError = true, .errorID = TERMINAL_HEIGHT_TOO_SMALL, .validationCallback = checkIfTerminalHeightIsCritical};
    }

    return errorStruct;
}

// The project's requirements have a item that specifies that
// the clock shall hide the seconds or the date if the 
// terminal dimensions aren't great enough to support them.
// This procedure checks the dimentions and set control variables
void checkIfTheClockShouldBeSmaller(struct DatetimeScreenManagerDesignerModules arguments){

    // If the seconds is already not being shown
    // this is useless
    if(arguments.hideTheSeconds == false){
        if(checkIfTheSecondsShouldBeInvisible() == true){
            if(checkIfTheSecondsIsVisible() == true){
                toggleSecondsVisibility();
            }
        }else{
            if(checkIfTheSecondsIsVisible() == false){
                toggleSecondsVisibility();
            }
        }
    }

    // If the date is already not being shown
    // this is useless
    if(arguments.hideTheDate == false){
        if(checkIfTheDateShouldBeInvisible() == true){
            if(checkIfTheDateIsVisible() == true){
                toggleDatesVisibility();
            }
        }else{
            if(checkIfTheDateIsVisible() == false){
                toggleDatesVisibility();
            }
        }
    }
}

// This subroutine is always called after a possible program error that is recoverable,
// if necessary, it will destroy the clock windows and recreate again, else it will 
// just update the windows to display the time again
void redrawTheEntireClock(ProgramArguments arguments, bool destroyTheWindows){

    wclear(stdscr);
    refresh();

    if(destroyTheWindows){
        destroyRclockWindows(arguments);
        generateWindows(arguments.DatetimeScreenManagerDesigner);
    }
    
    setPlaceHolders(arguments);
    moveTimeWindowsToPlaceholders();

    if(checkIfTheDateIsVisible() == true){
        moveDateWindowToPlaceholder();
    }

    refreshWindows();

    drawAllClockWindows(&timeStruct, arguments.DatetimeScreenManagerDesigner);

    if(checkIfTheDateIsVisible() == true){
        drawDate(&timeStruct, arguments.datetime, arguments.colors);
    }

    refreshWindows();
    refresh();
}

void setCustomDateAndTime(ProgramArguments arguments){
    char errorBuffer[512] = {0};

    setNewTime(&timeStruct, arguments.datetime, errorBuffer);
    setNewDate(&timeStruct, arguments.datetime, errorBuffer);

    verifyForDateAndTimeErrors(&timeStruct, errorBuffer);

    saveInitialProgramTime(&timeStruct);
}