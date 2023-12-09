#include "./../include/colors.h"

struct RclockColor availableColors[] = {
    (struct RclockColor){.colorName = "black", .clockID = BLACK_ID, .dateID = DATE_BLACK_ID},
    (struct RclockColor){.colorName = "red", .clockID = RED_ID, .dateID = DATE_RED_ID},
    (struct RclockColor){.colorName = "green", .clockID = GREEN_ID, .dateID = DATE_GREEN_ID},
    (struct RclockColor){.colorName = "yellow", .clockID = YELLOW_ID, .dateID = DATE_YELLOW_ID},
    (struct RclockColor){.colorName = "blue", .clockID = BLUE_ID, .dateID = DATE_BLUE_ID},
    (struct RclockColor){.colorName = "magenta", .clockID = MAGENTA_ID, .dateID = DATE_MAGENTA_ID},
    (struct RclockColor){.colorName = "cyan", .clockID = CYAN_ID, .dateID = DATE_CYAN_ID},
    (struct RclockColor){.colorName = "white", .clockID = WHITE_ID, .dateID = DATE_WHITE_ID}
};

ColorID digitColors[MAX_CLOCK_DIGIT_WINDOWS];
ColorID dateColor;
ColorID colonsColor;

void loadBuiltinColors(){
    // Colors for clock
    init_pair(BLACK_ID, 0, COLOR_BLACK);
    init_pair(RED_ID, 0, COLOR_RED);
    init_pair(GREEN_ID, 0, COLOR_GREEN);
    init_pair(YELLOW_ID, 0, COLOR_YELLOW);
    init_pair(BLUE_ID, 0, COLOR_BLUE);
    init_pair(MAGENTA_ID, 0, COLOR_MAGENTA);
    init_pair(CYAN_ID, 0, COLOR_CYAN);
    init_pair(WHITE_ID, 0, COLOR_WHITE);
    
    // Colors for date
    init_pair(DATE_BLACK_ID, COLOR_BLACK, -1);
    init_pair(DATE_RED_ID, COLOR_RED, -1);
    init_pair(DATE_GREEN_ID, COLOR_GREEN, -1);
    init_pair(DATE_YELLOW_ID, COLOR_YELLOW, -1);
    init_pair(DATE_BLUE_ID, COLOR_BLUE, -1);
    init_pair(DATE_MAGENTA_ID, COLOR_MAGENTA, -1);
    init_pair(DATE_CYAN_ID, COLOR_CYAN, -1);
    init_pair(DATE_WHITE_ID, COLOR_WHITE, -1);
}

void setColorToTheDigits(ColorID newColor){
    for(int i = 0; i < MAX_CLOCK_DIGIT_WINDOWS; i++){
        digitColors[i] = newColor;
    }
}

void setColorToTheClock(ColorID newColor){
    setColorToTheDigits(newColor);

    colonsColor = newColor;
}

struct RclockColor* searchForColor(char *colorName){
    size_t colorsArraySize = sizeof(availableColors) / sizeof(availableColors[0]);


    for(short i = 0; i < colorsArraySize; i++){
        if(strcmp(colorName, availableColors[i].colorName) == 0){
            return &availableColors[i];
        }
    }

    return NULL;
}

void setGlobalDigitsColor(struct ColorsModule userArguments, char *errorOutput){
    struct RclockColor *colorSearchResult;

   if(userArguments.globalDigitsColor != NULL){
        colorSearchResult = searchForColor(userArguments.globalDigitsColor);

        if(colorSearchResult != NULL){
            setColorToTheDigits(colorSearchResult->clockID);
        }else{
            generateErrorMessage(UNKNOWN_DIGITS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void setClockColor(struct ColorsModule userArguments, char *errorOutput){
    struct RclockColor *colorSearchResult;

    if(userArguments.clockColor != NULL){
        colorSearchResult = searchForColor(userArguments.clockColor);

        if(colorSearchResult != NULL){
            setColorToTheClock(colorSearchResult->clockID);
        }else{
            generateErrorMessage(UNKNOWN_CLOCK_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void setDateColor(struct ColorsModule userArguments, char* errorOutput){
    struct RclockColor *colorSearchResult;

    if(userArguments.dateColor != NULL){
        colorSearchResult = searchForColor(userArguments.dateColor);

        if(colorSearchResult != NULL){
            dateColor = colorSearchResult->dateID;
        }else{
            generateErrorMessage(UNKNOWN_DATE_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void setColonColor(struct ColorsModule userArguments, char* errorOutput){
    struct RclockColor *colorSearchResult;

    if(userArguments.colonColor != NULL){
        colorSearchResult = searchForColor(userArguments.colonColor);

        if(colorSearchResult != NULL){
            colonsColor = colorSearchResult->clockID;
        }else{
            generateErrorMessage(UNKNOWN_COLONS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
            return;
        }
    }
}

void setColorForEachClockDigit(struct ColorsModule userArguments, char* errorOutput){
    struct RclockColor *colorSearchResult;

    for(int i = 0; i < MAX_DIGIT_COLORS; i++){
        if(userArguments.digitColor[i] != NULL){
            colorSearchResult = searchForColor(userArguments.digitColor[i]);

            if(colorSearchResult != NULL){
                digitColors[i] = colorSearchResult->clockID;
            }else{
                generateErrorMessage(UNKNOWN_SPECIFIC_DIGIT_COLOR, (struct ErrorMessageArguments){.unknownSpecificDigitColor = i + 1}, errorOutput);
            }
        }
    }
}

ColorID getDigitColor(unsigned char digitIndex){
    if(digitIndex >= 0 && digitIndex <= 5){
        return digitColors[digitIndex];
    }else{
        return DEFAULT_COLOR;
    }
}

ColorID getColonColor(){
    return colonsColor;
}

ColorID getDateColor(){
    return dateColor;
}

void setComponentsColors(struct ColorsModule userArguments, char* errorOutput){

    setGlobalDigitsColor(userArguments, errorOutput);

    setClockColor(userArguments, errorOutput);

    setDateColor(userArguments, errorOutput);

    setColonColor(userArguments, errorOutput);

    setColorForEachClockDigit(userArguments, errorOutput);
}