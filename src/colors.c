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

void setColorToTheClock(ColorID newColor){
    setColorToTheDigits(newColor);

    colonsColor = newColor;
}

void setColorToTheDigits(ColorID newColor){
    for(int i = 0; i < MAX_CLOCK_DIGIT_WINDOWS; i++){
        digitColors[i] = newColor;
    }
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
            issueAnError(UNKNOWN_CLOCK_COLOR);
        }
    }

    if(userArguments.globalDigitsColor != NULL){
        colorSearchResult = searchForColor(userArguments.globalDigitsColor);

        if(colorSearchResult != NULL){
            setColorToTheDigits(colorSearchResult->id);
        }else{
            issueAnError(UNKNOWN_DIGITS_COLOR);
        }
    }

    if(userArguments.dateColor != NULL){
        colorSearchResult = searchForColor(userArguments.dateColor);

        if(colorSearchResult != NULL){
            dateColor = colorSearchResult->id;
        }else{
            issueAnError(UNKNOWN_DATE_COLOR);
        }
    }

    if(userArguments.colonColor != NULL){
        colorSearchResult = searchForColor(userArguments.colonColor);

        if(colorSearchResult != NULL){
            colonsColor = colorSearchResult->id;
        }else{
            issueAnError(UNKNOWN_COLONS_COLOR);
        }
    }
}

ColorID getComponentColor();