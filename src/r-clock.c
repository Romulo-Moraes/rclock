#include "../include/global-includes.h"
#include "../include/arguments.h"
#include "../include/screen-manager.h"
#include "../include/design.h"
#include "../include/datetime.h"

struct tm *timeStruct;

void signalHandler(int signal);
void redrawTheEntireClock(ProgramArguments arguments, ClockState clockWidthState, ClockState clockHeightState, bool destroyTheWindows);
void configureNcurses();
void configureRclock();
void checkIfTheClockShouldBeSmaller();
struct TerminalSizeError checkIfTerminalSizeIsCritical(ProgramArguments arguments);
void initializeTheClock();

int main(int argc, char *argv[]){
    ProgramArguments arguments = fetchProgramArguments();
    timeStruct = generateDateAndTime();
    struct tm timeStructCopy = *timeStruct;
    char errorBuffer[512];
    ClockState clockWidthState, clockHeightState;
    struct TerminalSizeError sizeError;
    struct ErrorWindows errorWindows;
    bool terminalSizeErrorFlag;
    struct UpdateErrorFramesCallbackArguments callbackArguments;
    WINDOW *segmentToFill[2];

    configureNcurses();
    configureRclock(arguments, errorBuffer, &clockWidthState, &clockHeightState);

    initializeTheClock(arguments, &clockWidthState, &clockHeightState);

    alarm(1);

    while(true){
        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
        
            terminalSizeErrorFlag = false;

            do{
                sizeError = checkIfTerminalSizeIsCritical(arguments);

                if(sizeError.thereIsAnError == true){
                    errorWindows =  generateErrorWindows(generateErrorMessage(sizeError.errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer), 0.75, false);

                    callbackArguments = (struct UpdateErrorFramesCallbackArguments){.windows = errorWindows, .errorMsg = errorBuffer, .exitErrorMsg = NULL};

                    updateErrorMessageFrames(errorWindows, 0.75, errorBuffer, drawProgramErrorCallback, &callbackArguments, sizeError.validationCallback, false);

                    terminalSizeErrorFlag = true;
                }

                
            }while(sizeError.thereIsAnError == true);

            checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner, &clockWidthState, &clockHeightState);

            redrawTheEntireClock(arguments, clockWidthState, clockHeightState, terminalSizeErrorFlag);
        }else{

            // The main loop run more than once in a second
            // there's no need of run this everytime
            if(timeStruct->tm_sec != timeStructCopy.tm_sec){

                if(timeStruct->tm_hour != timeStructCopy.tm_hour)
                    fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct->tm_hour);
        
                if(timeStruct->tm_min != timeStructCopy.tm_min)
                    fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct->tm_min);

                if(clockWidthState != SMALL_CLOCK && arguments.DatetimeScreenManagerDesigner.hideTheSeconds != true){
                    fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct->tm_sec);
                }
            }
        }

        refreshWindows();
        refresh();
        timeStructCopy = *timeStruct;

        // Sleeps for SLEEP_TIME_IN_NANOSECONDS nano seconds
        sleepClock();
    }    

    endwin();

    return EXIT_SUCCESS;
}

void configureNcurses(){
    initscr();
    cbreak();
    start_color();
    use_default_colors();
    curs_set(0);
}

void configureRclock(ProgramArguments arguments, char *errorBuffer, ClockState *widthState, ClockState *heightState){
    loadBuiltinColors();
    setComponentsColors(arguments.colors, errorBuffer);
    loadInitialTerminalSize();
    setValuesForClockStates(widthState, heightState);
    signal(SIGALRM, signalHandler);
}

void initializeTheClock(ProgramArguments arguments, ClockState *clockWidthState, ClockState *clockHeightState){
    struct TerminalSizeError error;
    struct ErrorWindows errorWindows;
    char errorBuffer[512];
    struct UpdateErrorFramesCallbackArguments callbackArguments;

    generateWindows(arguments.DatetimeScreenManagerDesigner);

    // TODO !!! check if placeholders is affected by the state flags
    setPlaceHolders(arguments);

    checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner, clockWidthState, clockHeightState);

    do{
        error = checkIfTerminalSizeIsCritical(arguments);

        if(error.thereIsAnError == true){
            errorWindows =  generateErrorWindows(generateErrorMessage(error.errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer), 0.75, false);

            callbackArguments = (struct UpdateErrorFramesCallbackArguments){.windows = errorWindows, .errorMsg = errorBuffer, .exitErrorMsg = NULL};

            updateErrorMessageFrames(errorWindows, 0.75, errorBuffer, drawProgramErrorCallback, &callbackArguments, error.validationCallback, false);
        }
    }while(error.thereIsAnError == true);
    

    moveTimeWindowsToPlaceholders();
    

    if(arguments.DatetimeScreenManagerDesigner.hideTheDate == false && *clockHeightState == NORMAL_CLOCK){
        drawDate(timeStruct, arguments.datetime, arguments.colors);
        moveDateWindowToPlaceholder();
    }
    
    refresh();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, *clockWidthState);

}

void signalHandler(int signal){
    switch(signal){
        case SIGALRM:
            incrementClockSecond(timeStruct);
            alarm(1);
            break;
    }
}

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

void checkIfTheClockShouldBeSmaller(struct DatetimeScreenManagerDesignerModules arguments, ClockState *widthState, ClockState *heightState){

    // If the seconds is already not being shown
    // this is useless
    if(arguments.hideTheSeconds == false){
        if(checkIfTheSecondsShouldBeInvisible() == true){
            if(*widthState == NORMAL_CLOCK){
                *widthState = SMALL_CLOCK;
                toggleSecondsVisibility();
            }
        }else{
            if(*widthState == SMALL_CLOCK){
                *widthState = NORMAL_CLOCK;
                toggleSecondsVisibility();
            }
        }
    }

    // If the date is already not being shown
    // this is useless
    if(arguments.hideTheDate == false){
        if(checkIfTheDateShouldBeInvisible() == true){
            if(*heightState == NORMAL_CLOCK){
                *heightState = SMALL_CLOCK;
                toggleDatesVisibility();
            }
        }else{
            if(*heightState == SMALL_CLOCK){
                *heightState = NORMAL_CLOCK;
                toggleDatesVisibility();
            }
        }
    }
}

void redrawTheEntireClock(ProgramArguments arguments, ClockState clockWidthState, ClockState clockHeightState, bool destroyTheWindows){

    wclear(stdscr);
    refresh();

    if(destroyTheWindows){
        destroyRclockWindows(arguments);
        generateWindows(arguments.DatetimeScreenManagerDesigner);
    }
    

    setPlaceHolders(arguments);
    moveTimeWindowsToPlaceholders();

    if(clockHeightState == NORMAL_CLOCK){
        moveDateWindowToPlaceholder();
    }

    refreshWindows();

    drawAllClockWindows(timeStruct, arguments.DatetimeScreenManagerDesigner, clockWidthState);

    if(arguments.DatetimeScreenManagerDesigner.hideTheDate == false && clockHeightState == NORMAL_CLOCK)
        drawDate(timeStruct, arguments.datetime, arguments.colors);

    refreshWindows();
    refresh();
}