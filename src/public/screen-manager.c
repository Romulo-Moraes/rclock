/*
 * Screen-manager module: A module for managing screen operations and states
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include "./../../include/public/screen-manager.h"
#include "./../../include/private/screen-manager.h"

static struct Windows programWindows;
static struct WindowSize winSize;
static bool theClocksSecondsIsVisible;
static bool theClocksDateIsVisible;


// Public functions

bool checkIfTerminalHeightIsCritical(){
    return !(winSize.height >= MINIMUM_TERMINAL_HEIGHT);
}

bool checkIfTerminalWidthIsCritical(){
    return !(winSize.width >= MINIMUM_TERMINAL_WIDTH);
}

bool checkIfTheSecondsIsVisible(){
    return theClocksSecondsIsVisible;
}

bool checkIfTheDateIsVisible(){
    return theClocksDateIsVisible;
}

void toggleDatesVisibility(){
    theClocksDateIsVisible ^= 1;
}

void toggleSecondsVisibility(){
    theClocksSecondsIsVisible ^= 1;
}


bool checkIfTheDateShouldBeInvisible(){
    // The default height follows the premise
    // that the date isn't hidden
    return winSize.height < DEFAULT_CLOCK_HEIGHT;
}

bool checkIfTheSecondsShouldBeInvisible(){
    // The default width follows the premise
    // that the seconds isn't hidden
    return winSize.width < DEFAULT_CLOCK_WIDTH;
}

void loadInitialTerminalSize(){
    _getTerminalSize(&winSize.width, &winSize.height);
    
}

void setDateStringLength(size_t newLength){
    programWindows.windowsAttributes.dateStringLength = newLength;
}

// Once called, this function returns the
// pointer of the date window
WINDOW *getDateWindow(){
    return programWindows.dateWindow.window;
}

void destroyRclockWindows(ProgramArguments arguments){
    for(size_t i = 0; i < programWindows.windowsAttributes.clockWindowsCount; i++){
        delwin(programWindows.clockWindows[i].window);
    }

    if(arguments.DatetimeScreenManagerDesigner.hideTheDate == false){
        delwin(programWindows.dateWindow.window);
    }

    wclear(stdscr);
    refresh();
}   

void setValuesForClockStates(ProgramArguments arguments){
    if(checkIfTheSecondsShouldBeInvisible() == true || arguments.DatetimeScreenManagerDesigner.hideTheSeconds == true){
        theClocksSecondsIsVisible = false;
    }else{
        theClocksSecondsIsVisible = true;
    }

    if(checkIfTheDateShouldBeInvisible() == true || arguments.DatetimeScreenManagerDesigner.hideTheDate == true){
        theClocksDateIsVisible = false;
    }else{
        theClocksDateIsVisible = true;
    }
}

// Generates error and exit message windows that will be the place to
// draw the respective messages
struct ErrorWindows generateErrorWindows(float errorWindowWidthFraction, bool enableExitMessage){
    struct ErrorWindows errorWindows;

    _getTerminalSize(&winSize.width, &winSize.height);

    errorWindows.measures = _calculateErrorWindowsMeasures(errorWindowWidthFraction, winSize);

    errorWindows.errorWindow = newwin(ERROR_MESSAGE_WINDOW_HEIGHT, errorWindows.measures.errorWindowWidth, errorWindows.measures.errorWindowTop, errorWindows.measures.errorWindowLeft);
    if(enableExitMessage){
        errorWindows.exitMessageWindow = newwin(EXIT_MESSAGE_WINDOW_HEIGHT, errorWindows.measures.exitMessageWindowWidth, errorWindows.measures.exitMessageWindowTop, 0);
    }

    return errorWindows;
}

void moveTimeWindowsToPlaceholders(){
    size_t windowsLimit = (theClocksSecondsIsVisible == true ? WINDOWS_COUNT_WITH_VISIBLE_SECONDS : WINDOWS_COUNT_WITH_HIDDEN_SECONDS);

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The box of each time window will be clean on each move")
        for(int i = 0; i < windowsLimit; i++){
            wborder(programWindows.clockWindows[i].window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(programWindows.clockWindows[i].window);
        }
    #endif

    for(int i = 0; i < windowsLimit; i++){
        mvwin(programWindows.clockWindows[i].window, programWindows.clockWindows[i].position.y,
                                    programWindows.clockWindows[i].position.x);
    }
}

void moveDateWindowToPlaceholder(){
    int dateWindowXPosition = winSize.width / 2 - programWindows.windowsAttributes.dateStringLength / 2;

    refresh();

    #ifdef DEBUG
    #pragma comment ("DEBUG MODE ON! The box of the date window will be clean on each move")
        wborder(programWindows.dateWindow.window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');   
        wrefresh(programWindows.dateWindow.window);
    #endif

    wresize(programWindows.dateWindow.window, 3, programWindows.windowsAttributes.dateStringLength);
    mvwin(programWindows.dateWindow.window, programWindows.dateWindow.position.y, dateWindowXPosition);
}


bool detectTerminalResizes(){
    int newHeight, newWidth;

    getmaxyx(stdscr, newHeight, newWidth);

    if(winSize.width != newWidth || winSize.height != newHeight){
        return true;
    }

    return false;
}


// Returns the windows that correspond to a clock segment
WINDOW** getClockSegment(unsigned int windowIndex, WINDOW *output[2]){
    if(windowIndex <= 7){
        output[0] = programWindows.clockWindows[windowIndex].window;
        output[1] = programWindows.clockWindows[windowIndex + 1].window;

        return output;
    }else{
        return NULL;
    }
}


void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments){
    programWindows.windowsAttributes.clockWindowsCount = userArguments.hideTheSeconds == true ? WINDOWS_COUNT_WITH_HIDDEN_SECONDS : WINDOWS_COUNT_WITH_VISIBLE_SECONDS;

    for(short i = 0; i < programWindows.windowsAttributes.clockWindowsCount; i++){
        programWindows.clockWindows[i].window = newwin(TIME_WINDOW_HEIGHT, TIME_WINDOW_WIDTH, 0, 0);
    }

    if(userArguments.hideTheDate != true){
        programWindows.dateWindow.window = newwin(0, 0, 0, 0);
    }
}

// This procedure will calculate and create placeholders on screen
// with the goal of align everything to the center. This procedure is aware
// of hidden seconds and date
void setPlaceHolders(ProgramArguments arguments){
    _getTerminalSize(&winSize.width, &winSize.height);
    size_t windowsLimit;

    // Calculating the Y axis that the clock windows will be placed
    int windowsYPosition = winSize.height / 2 - (int)((TIME_WINDOW_HEIGHT / 2));
    int firstWindowXPosition;


    // The first window X-axis position is relative to the count
    // of windows that the clock will have, if we want to align
    // the clock to the center, we need to define different margins
    // for when the seconds are visible and for when the seconds are hidden.
    // The positions of the subsequent windows will be defined by a constant margin that will be 
    // added for each window
    if(theClocksSecondsIsVisible == true){
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_VISIBLE_SECONDS)) / 2 - 3;
        windowsLimit = WINDOWS_COUNT_WITH_VISIBLE_SECONDS;
    }else{
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_HIDDEN_SECONDS)) / 2 - 2;
        windowsLimit = WINDOWS_COUNT_WITH_HIDDEN_SECONDS;
    }

    // For each created window do...
    for(int i = 0; i < windowsLimit; i++){
        // Assign the same Y-axis position for all of them
        programWindows.clockWindows[i].position.y = windowsYPosition;
        // Assign the X axis position
        programWindows.clockWindows[i].position.x = firstWindowXPosition;

        // Increment the current X-axis position by the width of the window + 1
        firstWindowXPosition += TIME_WINDOW_WIDTH + 1;
    }

    if(theClocksDateIsVisible == true && arguments.DatetimeScreenManagerDesigner.hideTheDate == false){
        // The X position of the date can't be calculated now, this value
        // depends of the date string length
        programWindows.dateWindow.position.y = windowsYPosition + TIME_WINDOW_HEIGHT;
    }
    
}

void refreshWindows(){
    size_t windowsLimit = (theClocksSecondsIsVisible == true ? WINDOWS_COUNT_WITH_VISIBLE_SECONDS : WINDOWS_COUNT_WITH_HIDDEN_SECONDS);

    for(int i = 0; i < windowsLimit; i++){
        #ifdef DEBUG
        #pragma message ("DEBUG MODE ON! The clock digits have borders")
            box(programWindows.clockWindows[i].window, 0, 0);
        #endif
        wrefresh(programWindows.clockWindows[i].window);
    }

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The date window has a border")
        box(programWindows.dateWindow.window, 0, 0);
    #endif

    if(theClocksDateIsVisible == true)
        wrefresh(programWindows.dateWindow.window);

    refresh();
}


void updateErrorMessageFrames(struct ErrorWindows windows, float errorWindowWidthFraction, char *errorMessage, void (*drawProgramErrorCallback)(void *arguments), void *drawErrorArguments, bool (*errorVerificationCallback)(), bool enableExitMessage){
    struct ErrorWindowsMeasures measures;

    while(true){

            _getTerminalSize(&winSize.width, &winSize.height);

            measures = _calculateErrorWindowsMeasures(errorWindowWidthFraction, winSize);

            mvwin(windows.errorWindow, measures.errorWindowTop, measures.errorWindowLeft);
            wresize(windows.errorWindow, 5, measures.errorWindowWidth);

            if(enableExitMessage){
                mvwin(windows.exitMessageWindow, measures.exitMessageWindowTop, 0);
                wresize(windows.exitMessageWindow, 3, measures.exitMessageWindowWidth);
            }

            wrefresh(windows.errorWindow);

            if(enableExitMessage)
                wrefresh(windows.exitMessageWindow);

            refresh();

            // Update the measures for each loop
            ((struct ErrorUpdateCallbacksArguments*) drawErrorArguments)->windows.measures = measures;

            drawProgramErrorCallback(drawErrorArguments);

            if(!errorVerificationCallback()){
                delwin(windows.errorWindow);
                if(enableExitMessage)
                    delwin(windows.exitMessageWindow);

                break;
            }


        wrefresh(windows.errorWindow);
        refresh();

        sleepClock(250);

        /*if(getch() != ERR && (extraClearErrorParam != NULL ? extraClearErrorParam() : true)){
            break;
        }*/
    }
}