/*
 * Design module: A module for drawing components on screen
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <public/design.h>
#include <private/design.h>

// Public functions

void changeMainWindowBackgroundColor(int colorID) {
    bkgd(COLOR_PAIR(colorID));
    refresh();
}

void fillClockSegment(WINDOW *clockWindows[], unsigned char numberToDraw, unsigned char windowIndex, ColorID digitBackgroundColor){
    Digit segmentDigits[2];
    ClockPixel (*theDigit)[3];
    ColorID digitColorID;

    _normalizeSegment(numberToDraw, segmentDigits);

    for(short i = 0; i < 2; i++){
        theDigit = getDigitShape(segmentDigits[i]);
        digitColorID = getDigitColor(windowIndex++);

        _drawClockWindow(clockWindows[i], theDigit, digitColorID, digitBackgroundColor);
    }
}

void drawAllClockWindows(struct tm *timeStruct, struct DatetimeScreenManagerDesignerModulesArguments userArguments, ColorID digitBackgroundColor){
    WINDOW *segmentToFill[2];

    fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct->tm_hour, HOURS_INDEX, digitBackgroundColor);
    fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct->tm_min, MINUTES_INDEX, digitBackgroundColor);

    if(userArguments.hideTheSeconds == false && checkIfTheSecondsIsVisible() == true)
        fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct->tm_sec, SECONDS_INDEX, digitBackgroundColor);

    _fillClockColons(userArguments, digitBackgroundColor);

    refreshWindows();
}


// Get the date window and draw the date stored in the program,
// given by the user or by the OS
void drawDate(struct tm *theTime, struct DatetimeModuleArguments datetimeArguments, struct ColorsModuleArguments colorArguments){
    char dateBuffer[MAX_CLOCK_DATE_BUFFER_LEN + 1];
    WINDOW *dateWindow;
    size_t dateStringLen;

    // Asking to the screen-manager module
    // return a reference to the date's window
    dateWindow = getDateWindow();

    // Using the datetime module to stringify the date
    generateDateString(*theTime, datetimeArguments, dateBuffer);
    dateStringLen = strlen(dateBuffer) + 2;

    // Using the screen-manager to configure
    // and move the window to its placeholder.
    // Set the string's length is necessary to
    // align the text to the center of the screen.
    setDateStringLength(dateStringLen);
    moveDateWindowToPlaceholder();
    
    // Configuring and drawing the date
    wattron(dateWindow, COLOR_PAIR(getDateColor()));
    wattron(dateWindow, A_BOLD);

    mvwprintw(dateWindow, 1, 1, dateBuffer);
    
    wattroff(dateWindow, COLOR_PAIR(getDateColor()));
    wattroff(dateWindow, A_BOLD);
    wrefresh(dateWindow);
    refresh();
}

// A callback that draws the program error on screen.
// this procedure is given to the screen-manager module 
// to be possible draw the date without a include, that 
// would generate a circular dependency
void drawProgramErrorCallback(void *arguments){
    struct ErrorUpdateCallbacksArguments *typecastedArguments = (struct ErrorUpdateCallbacksArguments*) arguments;

    clear();
    refresh();

    _writeErrorMessageOnErrorWindow(typecastedArguments->errorMsg, typecastedArguments->windows.measures.errorWindowWidth, typecastedArguments->windows.errorWindow);

    refresh();
}