#include <helpers/startup.h>
#include <public/screen-manager.h>
#include <time.h>
#include <helpers/terminal-size.h>
#include <public/colors.h>
#include <public/design.h>


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

// Calls a couple of functions that will load
// default values and populate control variables
void configureRclock(ProgramArguments arguments, char *errorBuffer, void (*signalHandler)(int signal)){
    loadBuiltinColors();
    setComponentsColors(arguments.colors, errorBuffer);
    loadInitialTerminalSize();
    setValuesForClockStates(arguments);
    signal(SIGALRM, signalHandler);
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
    }
    
    refresh();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, BACKGROUND_TRANSPARENT_ID);

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