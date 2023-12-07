#include "./../include/design.h"

void normalizeSegment(unsigned char number, Digit segmentDigits[2]){
    if(number < 10){
        segmentDigits[0] = 0;
        segmentDigits[1] = number;
    }else{
        segmentDigits[0] = ((int)(number / 10));
        segmentDigits[1] = (number % 10);
    }
}

void drawSegment(WINDOW *clockWindows[], unsigned short baseSegmentIndex, unsigned char numberToDraw){
    Digit segmentDigits[2];
    ClockPixel **theDigit;
    ColorID digitColorID;

    normalizeSegment(numberToDraw, segmentDigits);

    for(short i = 0; i < 2; i++){
        theDigit = (ClockPixel**) getClockDigit(segmentDigits[i]);

        wmove(clockWindows[baseSegmentIndex + i], 0, 0);
        digitColorID = getDigitColor(baseSegmentIndex + i);

        for(short j = 0; j < 5; j++){
            for(short k = 0; k < 3; k++){
                if(theDigit[j][k] == COLOR){
                    attron(COLOR_PAIR(digitColorID));
                    wprintw(clockWindows[baseSegmentIndex + i], "  ");
                    attroff(COLOR_PAIR(digitColorID));
                }else{
                    wprintw(clockWindows[baseSegmentIndex + i], "  ");
                }
            }
        }
    }
}

void drawDate(struct tm *theTime, struct DatetimeModule datetimeArguments){
    char dateBuffer[MAX_CLOCK_DATE_BUFFER_LEN + 1];
    WINDOW *dateWindow;
    size_t dateStringLen;

    dateWindow = getDateWindow();

    generateDateString(*theTime, datetimeArguments, dateBuffer);
    dateStringLen = strlen(dateBuffer);

    setDateStringLength(dateStringLen);
    moveDateWindowToPlaceholder();
    
    mvwprintw(dateWindow, 1, 0, dateBuffer);
    wrefresh(dateWindow);
    refresh();
}