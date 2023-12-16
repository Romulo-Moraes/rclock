#include "./../../include/public/colors.h"
#include "./../../include/private/colors.h"

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

ColorID digitColors[MAX_DIGIT_COLORS];
ColorID dateColor;
ColorID colonsColor;


// Public functions


void setComponentsColors(struct ColorsModule userArguments, char* errorOutput){

    // The color arguments have priority order,
    // from specific to general

    // For the digits and colons - Low priority order
    _setClockColor(userArguments, errorOutput, &colonsColor, digitColors, availableColors, sizeof(availableColors));

    // For all digit windows
    _setGlobalDigitsColor(userArguments, errorOutput, availableColors, sizeof(availableColors), digitColors);

    // For the date
    _setDateColor(userArguments, errorOutput, &dateColor, availableColors, sizeof(availableColors));

    // For the colons
    _setColonColor(userArguments, errorOutput, &colonsColor, availableColors, sizeof(availableColors));

    // For each clock digit - High priority order
    _setColorForEachClockDigit(userArguments, errorOutput, digitColors, availableColors, sizeof(availableColors));
}

void loadBuiltinColors(){
    init_color(19, 850, 0, 0);

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

    // Error message
    init_pair(ERROR_MESSAGE_RED_ID, 19, -1);
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
