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