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

struct tm timeStruct;

void signalHandler(int signal);

int main(int argc, char *argv[]){
    ProgramArguments arguments;
    anemone_struct anemone;
    timeStruct = *generateDateAndTime();
    struct tm timeStructOldValue = timeStruct;
    char errorBuffer[512];
    struct TerminalSizeError sizeError;
    bool windowsNeedToBeDestroyed;
    WINDOW *segmentToFill[2];

    anemone = createProgramArguments(argc, argv);
    
    arguments = fetchProgramArguments(&anemone, errorBuffer);

    setCustomDateAndTime(arguments, &timeStruct);

    configureNcurses();
    configureRclock(arguments, errorBuffer, signalHandler);

    initializeTheClock(arguments, &timeStruct);

    // alarm that will update the clock value
    alarm(1);

    while(getch() != 10){
        // For each terminal resize, the clock is redrawn
        if(detectTerminalResizes()){
        
            windowsNeedToBeDestroyed = false;

            // A loop to check if the terminal size is safe to render the clock
            do{
                sizeError = checkIfTerminalSizeIsCritical(arguments);

                if(sizeError.thereIsAnError == true){
                    // Issue an error if the size is not safe
                    createTerminalSizeError(sizeError);

                    windowsNeedToBeDestroyed = true;
                }

            }while(sizeError.thereIsAnError == true);

            checkIfTheClockShouldBeSmaller(arguments.DatetimeScreenManagerDesigner);

            redrawTheEntireClock(arguments, windowsNeedToBeDestroyed, &timeStruct);
        }else{

            if(timeStruct.tm_sec != timeStructOldValue.tm_sec){

                if(timeStruct.tm_hour != timeStructOldValue.tm_hour)
                    fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct.tm_hour, HOURS_INDEX);
        
                if(timeStruct.tm_min != timeStructOldValue.tm_min)
                    fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct.tm_min, MINUTES_INDEX);

                if(checkIfTheSecondsIsVisible() == true){
                    fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct.tm_sec, SECONDS_INDEX);
                }

                if(timeStruct.tm_hour < timeStructOldValue.tm_hour){
                    mktime(&timeStruct);
                    drawDate(&timeStruct, arguments.datetime, arguments.colors);
                }
                
                // Making both have the same value for the next alarm
                timeStructOldValue = timeStruct;
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

void signalHandler(int signal){
    if (signal == SIGALRM) {
        incrementClockSecond(&timeStruct);
            
        if(timeStruct.tm_sec % 5 == 0){
            tryToUpdateTheClock(&timeStruct);
        }

        alarm(1);
    }
}