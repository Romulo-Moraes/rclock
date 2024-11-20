#include <helpers/startup.h>
#include <public/screen-manager.h>
#include <time.h>
#include <helpers/terminal-size.h>
#include <public/colors.h>
#include <public/design.h>
#include <public/signal-handler.h>


// Create and call update routines to show an error screen 
// of a terminal size trouble
void createTerminalSizeError(struct TerminalSizeError sizeError){
    char errorBuffer[512];
    struct ErrorWindows errorWindows;
    struct ErrorUpdateCallbacksArguments callbackArguments;

    errorWindows = generateErrorWindows(0.75, false);

    bkgd(COLOR_PAIR(BACKGROUND_TRANSPARENT_ID));
    refresh();

    generateErrorMessage(sizeError.errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer);

    callbackArguments = (struct ErrorUpdateCallbacksArguments){.windows = errorWindows, .errorMsg = errorBuffer, .exitErrorMsg = NULL};

    updateErrorMessageFrames(errorWindows, 0.75, errorBuffer, drawProgramErrorCallback, &callbackArguments, sizeError.validationCallback, false);
}

// Calls a couple of functions that will load
// default values and populate control variables
void configureRclock(ProgramArguments arguments){
    char errorBuffer[1024] = {0};

    loadBuiltinColors();
    setComponentsColors(arguments.colors, errorBuffer);

    if (strlen(errorBuffer) != 0) {
        endwin();
        
        printf("[ERROR] %s\n", errorBuffer);

        exit(EXIT_FAILURE);
    }

    loadInitialTerminalSize();
    setValuesForClockStates(arguments);
    signal(SIGALRM, arguments.mode == POMODORO_MODE ?  pomodoroSignalHandler : clockSignalHandler);
}

void initializeTheClock(ProgramArguments arguments, struct tm *timeStruct){
    struct TerminalSizeError sizeError;
    
    generateWindows(arguments.DatetimeScreenManagerDesigner, arguments.mode);

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
        drawDate(timeStruct, arguments.datetime, arguments.colors);
        moveDateWindowToPlaceholder();
    }

    if (arguments.mode == POMODORO_MODE) {
        moveOptionsWindowToPlaceholder();
        movePomodoroStatusWindowToPlaceholder();
        drawOptions(false);
        drawPomodoroStatusWindow(false);
    }
    
    refresh();

    if (arguments.mode == POMODORO_MODE && checkIfTheSecondsIsVisible() == false) {
        struct tm tmp = (struct tm) {
            .tm_hour = timeStruct->tm_min,
            .tm_min = timeStruct->tm_sec
        };

        drawAllClockWindows(&tmp, arguments.DatetimeScreenManagerDesigner, false);
    } else {
        drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, false);
    }
    
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