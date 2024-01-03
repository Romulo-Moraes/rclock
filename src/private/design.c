#include "./../../include/private/design.h"

// Procedure that split a number into two digits, if the number is smaller than 10
// a zero will placed before the number. For instance: 9 -> 09, 4 -> 04
void _normalizeSegment(unsigned char number, Digit segmentDigits[2]){
    if(number < 10){
        segmentDigits[0] = 0;
        segmentDigits[1] = number;
    }else{
        segmentDigits[0] = ((int)(number / 10));
        segmentDigits[1] = (number % 10);
    }
}

// Draws the given digit shape to the given window
void _drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID){
    wmove(targetWindow, 0, 0);

    for(short j = 0; j < 5; j++){
        for(short k = 0; k < 3; k++){
            if(shapeToBeDrawn[j][k] == COLOR){
                wattron(targetWindow, COLOR_PAIR(digitColorID));
                wprintw(targetWindow, "  ");
                wattroff(targetWindow, COLOR_PAIR(digitColorID));
                wrefresh(targetWindow);
            }else{
                wprintw(targetWindow, "  ");
                wrefresh(targetWindow);
            }
        }
    }
}

// Draws the colons of the clock
void _fillClockColons(struct DatetimeScreenManagerDesignerModules userArguments){
    ClockPixel (*colonShape)[3] = getColonShape();
    ColorID colonColor = getColonColor();
    WINDOW *segmentToFill[2];

    _drawClockWindow(getClockSegment(FIRST_CLOCK_COLON, segmentToFill)[0], colonShape, colonColor);

    // The last colon is drawn only if the seconds is visible
    if(userArguments.hideTheSeconds == false && checkIfTheSecondsIsVisible() == true)
        _drawClockWindow(getClockSegment(SECOND_CLOCK_COLON, segmentToFill)[0], colonShape, colonColor);
}

void _writeErrorMessageOnErrorWindow(char *msg, size_t windowWidth, WINDOW *errorWindow){
    size_t msgLen = strlen(msg);
    size_t requiredLines;
    size_t remainder;
    short i;
    

    wclear(errorWindow);
    wrefresh(errorWindow);

    requiredLines = msgLen / (float) windowWidth;
    remainder = msgLen % windowWidth;

    wattron(errorWindow, COLOR_PAIR(ERROR_MESSAGE_RED_ID));

    // Write chunks of the error message with the     
    // max length that each line support
    for(i = 1; i <= requiredLines; i++){
        mvwaddnstr(errorWindow, i, 0, msg, windowWidth);

        msg += windowWidth;
    }

    // Write the rest of the message that doesn't
    // fill the whole line aligned to the center
    mvwaddnstr(errorWindow, i, windowWidth / 2 - remainder / 2, msg, remainder);

    wattroff(errorWindow, COLOR_PAIR(ERROR_MESSAGE_RED_ID));

    wrefresh(errorWindow);
    refresh();
}