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
#include <public/signal-handler.h>
#include <public/user-input.h>

struct tm timeStruct;
struct tm timeStructOldValue;

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
    bool keepRunningProgram = true;
    char input;
    struct tm timeStructBasedOnClockMode;

    anemone = createProgramArguments(argc, argv);
    arguments = fetchProgramArguments(&anemone, errorBuffer);

    configureSignalHandlerModule(&timeStruct);
    setModeData(&arguments, &timeStruct);
    configureNcurses();
    configureRclock(arguments, errorBuffer, arguments.mode == POMODORO_MODE ? pomodoroSignalHandler : clockSignalHandler);

    initializeTheClock(arguments, &timeStruct);

    // alarm that will update the clock value
    alarm(1);

    while(keepRunningProgram){
        input = getch();

        handleUserInput(input, arguments, &timeStruct, &timeStructOldValue, pomodoroSignalHandler, &keepRunningProgram);

        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
            windowsNeedToBeDestroyed = showTerminalSizeErrorIfNecessary(arguments);

            checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner);

            timeStructBasedOnClockMode = generateTimeStructToBeRenderedBasedOnClockMode(arguments.mode, timeStruct);

            redrawTheEntireClock(arguments, windowsNeedToBeDestroyed, &timeStructBasedOnClockMode);
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

