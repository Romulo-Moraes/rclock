/*
 * Rclock: A digital terminal clock for POSIX platforms
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <public/global-includes.h>
#include <public/arguments.h>
#include <public/screen-manager.h>
#include <public/design.h>
#include <public/datetime.h>
#include <helpers/startup.h>
#include <helpers/terminal-size.h>
#include <helpers/datetime.h>
#include <helpers/design.h>
#include <public/pomodoro.h>
#include <public/modes.h>
#include <helpers/modes.h>

struct tm timeStruct;
struct tm timeStructOldValue;
bool backgroundIsRed = false;

void clockSignalHandler(int signal);
void pomodoroSignalHandler(int signal);
void pomodoroTimeoutHandler(int signal);
bool showTerminalSizeErrorIfNecessary(ProgramArguments arguments);

int main(int argc, char *argv[]){
    ProgramArguments arguments;
    anemone_struct anemone;
    timeStruct = *generateDateAndTime();
    char errorBuffer[512];
    bool windowsNeedToBeDestroyed;
    char userInput;

    anemone = createProgramArguments(argc, argv);
    
    arguments = fetchProgramArguments(&anemone, errorBuffer);

    setModeData(&arguments, &timeStruct);
    
    configureNcurses();
    configureRclock(arguments, errorBuffer, arguments.mode == POMODORO_MODE ? pomodoroSignalHandler : clockSignalHandler);

    initializeTheClock(arguments, &timeStruct);

    // alarm that will update the clock value

    alarm(1);

    if (arguments.mode == POMODORO_MODE) {
        drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    }

    while(true){
        userInput = getch();

        if (userInput == 's' && arguments.mode == POMODORO_MODE) {
            startTimer();
            drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
            alarm(1);
        }

        if (userInput == 'p' && arguments.mode == POMODORO_MODE && getPomodoroState().paused == false) {
            togglePauseState();
            drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        }

        if (userInput == 'u' && arguments.mode == POMODORO_MODE && getPomodoroState().paused == true) {
            togglePauseState();
            drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        }

        if (userInput == 'o' && arguments.mode == POMODORO_MODE && getPomodoroState().timeoutStatus.timeout == true) {
            togglePomodoroTurn();
            restartTimer();

            drawOptions(BACKGROUND_TRANSPARENT_ID);
            drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
            signal(SIGALRM, pomodoroSignalHandler);
            struct TimeStruct time;

            if (getPomodoroState().turn == POMODORO) {
                time = getPomodoroTime();
            } else {
                incrementIntervalsCount();
                time = getRestTime();
            }

            timeStruct.tm_min = time.minutes;
            timeStruct.tm_sec = time.seconds;

            bkgd(COLOR_PAIR(BACKGROUND_TRANSPARENT_ID));
            refresh();

            drawAllClockWindows(&timeStruct, arguments.DatetimeScreenManagerDesigner, BACKGROUND_TRANSPARENT_ID);
            drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
            drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        }

        if (userInput == 10) {
            break;
        }

        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
            windowsNeedToBeDestroyed = showTerminalSizeErrorIfNecessary(arguments);

            checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner);

            if (arguments.mode == POMODORO_MODE && checkIfTheSecondsIsVisible() == false) {
                struct tm tmp = (struct tm) {
                    .tm_hour = timeStruct.tm_min,
                    .tm_min = timeStruct.tm_sec
                };

                redrawTheEntireClock(arguments, windowsNeedToBeDestroyed, &tmp);
            } else {
                redrawTheEntireClock(arguments, windowsNeedToBeDestroyed, &timeStruct);
            }
        }else{
            switch(arguments.mode) {
                case CLOCK_MODE:
                    clockMode(arguments.datetime, arguments.colors, timeStruct, timeStructOldValue);
                    break;
                case POMODORO_MODE:
                    pomodoroMode(&timeStruct, &timeStructOldValue, pomodoroTimeoutHandler);
                    break;
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

bool showTerminalSizeErrorIfNecessary(ProgramArguments arguments) {
    struct TerminalSizeError sizeError;
    bool windowsNeedToBeDestroyed = false;

    do{
        sizeError = checkIfTerminalSizeIsCritical(arguments);
        if(sizeError.thereIsAnError == true){
            createTerminalSizeError(sizeError);
            windowsNeedToBeDestroyed = true;
        }
    }while(sizeError.thereIsAnError == true);

    return windowsNeedToBeDestroyed;
}

void pomodoroTimeoutHandler(int signal) {
    if (signal == SIGALRM) {
        switch(backgroundIsRed) {
            case true:
                changeMainWindowBackgroundColor(BACKGROUND_TRANSPARENT_ID);
                drawAllClockWindows(&timeStruct, (struct DatetimeScreenManagerDesignerModulesArguments) {.hideTheSeconds = false}, BACKGROUND_TRANSPARENT_ID);
                drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
                drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
                break;
            case false:
                changeMainWindowBackgroundColor(BACKGROUND_RED_ID);
                drawAllClockWindows(&timeStruct, (struct DatetimeScreenManagerDesignerModulesArguments) {.hideTheSeconds = false}, BACKGROUND_RED_ID);
                drawOptions(OPTIONS_BACKGROUND_RED_ID);
                drawPomodoroStatusWindow(OPTIONS_BACKGROUND_RED_ID);
                break;
        }

        backgroundIsRed = !backgroundIsRed;
        alarm(1);
    }
}

void pomodoroSignalHandler(int signal) {
    if (signal == SIGALRM) {
        struct PomodoroState state = getPomodoroState();

        if (getPomodoroState().paused == false && state.hasStarted == true) {
            decrementClockSecond(&timeStruct);
        }

        alarm(1);
    }
}

void clockSignalHandler(int signal){
    if (signal == SIGALRM) {
        incrementClockSecond(&timeStruct);
            
        if(timeStruct.tm_sec % 5 == 0){
            tryToUpdateTheClock(&timeStruct);
        }

        alarm(1);
    }
}