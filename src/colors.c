#include "./../include/colors.h"

struct RclockColor availableColors[] = {
    (struct RclockColor){.colorName = "black", .id = BLACK_ID},
    (struct RclockColor){.colorName = "red", .id = RED_ID},
    (struct RclockColor){.colorName = "green", .id = GREEN_ID},
    (struct RclockColor){.colorName = "yellow", .id = YELLOW_ID},
    (struct RclockColor){.colorName = "blue", .id = BLUE_ID},
    (struct RclockColor){.colorName = "magenta", .id = MAGENTA_ID},
    (struct RclockColor){.colorName = "cyan", .id = CYAN_ID},
    (struct RclockColor){.colorName = "white", .id = WHITE_ID}
};

ColorID digitColors[MAX_CLOCK_DIGIT_WINDOWS] = {DEFAULT_COLOR};
ColorID dateColor = DEFAULT_COLOR;
ColorID colonsColor = DEFAULT_COLOR;

void loadBuiltinColors(){
    init_pair(BLACK_ID, COLOR_BLACK, 0);
    init_pair(RED_ID, COLOR_RED, 0);
    init_pair(GREEN_ID, COLOR_GREEN, 0);
    init_pair(YELLOW_ID, COLOR_YELLOW, 0);
    init_pair(BLUE_ID, COLOR_BLUE, 0);
    init_pair(MAGENTA_ID, COLOR_MAGENTA, 0);
    init_pair(CYAN_ID, COLOR_CYAN, 0);
    init_pair(WHITE_ID, COLOR_WHITE, 0);
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
            setColorToTheDigits(colorSearchResult->id);
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
            setColorToTheClock(colorSearchResult->id);
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
            dateColor = colorSearchResult->id;
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
            colonsColor = colorSearchResult->id;
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
                digitColors[i] = colorSearchResult->id;
            }else{
                generateErrorMessage(UNKNOWN_SPECIFIC_DIGIT_COLOR, (struct ErrorMessageArguments){.unknownSpecificDigitColor = i + 1}, errorOutput);
            }
        }
    }
}

void setComponentsColors(struct ColorsModule userArguments, char* errorOutput){

    setGlobalDigitsColor(userArguments, errorOutput);

    setClockColor(userArguments, errorOutput);

    setDateColor(userArguments, errorOutput);

    setColonColor(userArguments, errorOutput);

    setColorForEachClockDigit(userArguments, errorOutput);
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