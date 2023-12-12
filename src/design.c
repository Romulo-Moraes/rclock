#include "./../include/design.h"

// Forward declarations
void normalizeSegment(unsigned char number, Digit segmentDigits[2]);
void drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID);
void fillClockColons(struct DatetimeScreenManagerDesignerModules userArguments, ClockState state);

// Public functions

void drawAllClockWindows(struct tm *timeStruct, struct DatetimeScreenManagerDesignerModules userArguments, ClockState state){
    WINDOW *segmentToFill[2];

    fillClockSegment(getClockSegment(HOURS_SEGMENT, segmentToFill), timeStruct->tm_hour);
    fillClockSegment(getClockSegment(MINUTES_SEGMENT, segmentToFill), timeStruct->tm_min);

    if(userArguments.hideTheSeconds == false && state == NORMAL_CLOCK)
        fillClockSegment(getClockSegment(SECONDS_SEGMENT, segmentToFill), timeStruct->tm_sec);

    fillClockColons(userArguments, state);

    refreshWindows();
}

void fillClockSegment(WINDOW *clockWindows[], unsigned char numberToDraw){
    Digit segmentDigits[2];
    ClockPixel (*theDigit)[3];
    ColorID digitColorID;

    normalizeSegment(numberToDraw, segmentDigits);

    for(short i = 0; i < 2; i++){
        theDigit = getDigitShape(segmentDigits[i]);
        digitColorID = getDigitColor(0);

        drawClockWindow(clockWindows[i], theDigit, digitColorID);
    }
}

void drawDate(struct tm *theTime, struct DatetimeModule datetimeArguments, struct ColorsModule colorArguments){
    char dateBuffer[MAX_CLOCK_DATE_BUFFER_LEN + 1];
    WINDOW *dateWindow;
    size_t dateStringLen;

    dateWindow = getDateWindow();

    generateDateString(*theTime, datetimeArguments, dateBuffer);
    dateStringLen = strlen(dateBuffer) + 2;

    setDateStringLength(dateStringLen);
    moveDateWindowToPlaceholder();
    
    wattron(dateWindow, COLOR_PAIR(getDateColor()));
    mvwprintw(dateWindow, 1, 1, dateBuffer);
    wattroff(dateWindow, COLOR_PAIR(getDateColor()));
    wrefresh(dateWindow);
    refresh();
}

// Private functions

void normalizeSegment(unsigned char number, Digit segmentDigits[2]){
    if(number < 10){
        segmentDigits[0] = 0;
        segmentDigits[1] = number;
    }else{
        segmentDigits[0] = ((int)(number / 10));
        segmentDigits[1] = (number % 10);
    }
}

void drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID){
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

void fillClockColons(struct DatetimeScreenManagerDesignerModules userArguments, ClockState state){
    ClockPixel (*colonShape)[3] = getColonShape();
    ColorID colonColor = getColonColor();
    WINDOW *segmentToFill[2];

    drawClockWindow(getClockSegment(FIRST_CLOCK_COLON, segmentToFill)[0], colonShape, colonColor);

    if(userArguments.hideTheSeconds == false && state == NORMAL_CLOCK)
        drawClockWindow(getClockSegment(SECOND_CLOCK_COLON, segmentToFill)[0], colonShape, colonColor);
}