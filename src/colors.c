#include "./../include/colors.h"

struct RclockColor availableColors[] = {
    (struct RclockColor){.colorName = "black", .id = COLOR_BLACK},
    (struct RclockColor){.colorName = "red", .id = COLOR_RED},
    (struct RclockColor){.colorName = "green", .id = COLOR_GREEN},
    (struct RclockColor){.colorName = "yellow", .id = COLOR_YELLOW},
    (struct RclockColor){.colorName = "blue", .id = COLOR_BLUE},
    (struct RclockColor){.colorName = "magenta", .id = COLOR_MAGENTA},
    (struct RclockColor){.colorName = "cyan", .id = COLOR_CYAN},
    (struct RclockColor){.colorName = "white", .id = COLOR_WHITE}
};

ColorID digitColors[MAX_CLOCK_DIGIT_WINDOWS] = {DEFAULT_COLOR};
ColorID dateColor = DEFAULT_COLOR;
ColorID colonsColor = DEFAULT_COLOR;

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

void setComponentsColors(struct ColorsModule userArguments){
    struct RclockColor *colorSearchResult;

    if(userArguments.clockColor != NULL){
        colorSearchResult = searchForColor(userArguments.clockColor);

        if(colorSearchResult != NULL){
            setColorToTheClock(colorSearchResult->id);
        }else{
            generateErrorMessage(UNKNOWN_CLOCK_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

    if(userArguments.globalDigitsColor != NULL){
        colorSearchResult = searchForColor(userArguments.globalDigitsColor);

        if(colorSearchResult != NULL){
            setColorToTheDigits(colorSearchResult->id);
        }else{
            generateErrorMessage(UNKNOWN_DIGITS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

    if(userArguments.dateColor != NULL){
        colorSearchResult = searchForColor(userArguments.dateColor);

        if(colorSearchResult != NULL){
            dateColor = colorSearchResult->id;
        }else{
            generateErrorMessage(UNKNOWN_DATE_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

    if(userArguments.colonColor != NULL){
        colorSearchResult = searchForColor(userArguments.colonColor);

        if(colorSearchResult != NULL){
            colonsColor = colorSearchResult->id;
        }else{
            generateErrorMessage(UNKNOWN_COLONS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS);
        }
    }

    for(int i = 0; i < MAX_DIGIT_COLORS; i++){
        if(userArguments.digitColor[i] != NULL){
            colorSearchResult = searchForColor(userArguments.digitColor[i]);

            if(colorSearchResult != NULL){
                digitColors[i] = colorSearchResult->id;
            }else{
                generateErrorMessage(UNKNOWN_SPECIFIC_DIGIT_COLOR, (struct ErrorMessageArguments){.unknownSpecificDigitColor = i + 1});
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