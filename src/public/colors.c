/*
 * Colors module: A module for color customization
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <public/colors.h>
#include <private/colors.h>

#define PAIR PomodoroLabelColorPair

struct RclockColor availableColors[] = {
    (struct RclockColor){.colorName = "black", .clockID = BLACK_ID, .dateID = DATE_BLACK_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_BLACK_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_BLACK_NORMAL_ID}},
    (struct RclockColor){.colorName = "red", .clockID = RED_ID, .dateID = DATE_RED_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_RED_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_RED_NORMAL_ID}},
    (struct RclockColor){.colorName = "green", .clockID = GREEN_ID, .dateID = DATE_GREEN_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_GREEN_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_GREEN_NORMAL_ID}},
    (struct RclockColor){.colorName = "yellow", .clockID = YELLOW_ID, .dateID = DATE_YELLOW_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_YELLOW_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_YELLOW_NORMAL_ID}},
    (struct RclockColor){.colorName = "blue", .clockID = BLUE_ID, .dateID = DATE_BLUE_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_BLUE_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_BLUE_NORMAL_ID}},
    (struct RclockColor){.colorName = "magenta", .clockID = MAGENTA_ID, .dateID = DATE_MAGENTA_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_MAGENTA_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_MAGENTA_NORMAL_ID}},
    (struct RclockColor){.colorName = "cyan", .clockID = CYAN_ID, .dateID = DATE_CYAN_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_CYAN_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_CYAN_NORMAL_ID}},
    (struct RclockColor){.colorName = "white", .clockID = WHITE_ID, .dateID = DATE_WHITE_ID, .pomodoroLabelIDs = (PAIR) {.pomodoroLabelWarningID = POMODORO_LABEL_WHITE_WARNING_ID, .pomodoroLabelNormalID = POMODORO_LABEL_WHITE_NORMAL_ID}}
};

static ColorID digitsColors[MAX_DIGIT_COLORS] = {BLUE_ID};
static ColorID dateColor;
static ColorID colonsColor;
static PomodoroLabelColorPair pomodoroLabelColorPair = {
    .pomodoroLabelWarningID = POMODORO_LABEL_BLUE_WARNING_ID,
    .pomodoroLabelNormalID = POMODORO_LABEL_BLUE_NORMAL_ID
};


// Public functions

void setComponentsColors(struct ColorsModuleArguments userArguments, char* errorOutput){

    // The color arguments have priority order,
    // from specific to general

    size_t sizeOfAvailableColors = sizeof(availableColors) / sizeof(availableColors[0]);

    _setClockColor(userArguments, errorOutput, &colonsColor, digitsColors, availableColors, sizeOfAvailableColors);

    // For all digit windows
    _setGlobalDigitsColor(userArguments, errorOutput, availableColors, sizeOfAvailableColors, digitsColors);

    // For the date
    _setDateColor(userArguments, errorOutput, &dateColor, availableColors, sizeOfAvailableColors);

    // For the colons
    _setColonColor(userArguments, errorOutput, &colonsColor, availableColors, sizeOfAvailableColors);

    // For each clock digit - High priority order
    _setColorForEachClockDigit(userArguments, errorOutput, digitsColors, availableColors, sizeOfAvailableColors);


    _setPomodoroLabelColorPair(userArguments, &pomodoroLabelColorPair, errorOutput, availableColors, sizeOfAvailableColors);

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

    // System colors
    init_pair(BACKGROUND_RED_ID, COLOR_RED, COLOR_RED);
    init_pair(BACKGROUND_TRANSPARENT_ID, 0, -1);

    init_pair(POMODORO_LABEL_BLACK_WARNING_ID, COLOR_BLACK, COLOR_RED);
    init_pair(POMODORO_LABEL_BLACK_NORMAL_ID, COLOR_BLACK, -1);

    init_pair(POMODORO_LABEL_RED_WARNING_ID, COLOR_RED, COLOR_RED);
    init_pair(POMODORO_LABEL_RED_NORMAL_ID, COLOR_RED, -1);

    init_pair(POMODORO_LABEL_GREEN_WARNING_ID, COLOR_GREEN, COLOR_RED);
    init_pair(POMODORO_LABEL_GREEN_NORMAL_ID, COLOR_GREEN, -1);

    init_pair(POMODORO_LABEL_YELLOW_WARNING_ID, COLOR_YELLOW, COLOR_RED);
    init_pair(POMODORO_LABEL_YELLOW_NORMAL_ID, COLOR_YELLOW, -1);

    init_pair(POMODORO_LABEL_BLUE_WARNING_ID, COLOR_BLUE, COLOR_RED);
    init_pair(POMODORO_LABEL_BLUE_NORMAL_ID, COLOR_BLUE, -1);
    
    init_pair(POMODORO_LABEL_MAGENTA_WARNING_ID, COLOR_MAGENTA, COLOR_RED);
    init_pair(POMODORO_LABEL_MAGENTA_NORMAL_ID, COLOR_MAGENTA, -1);

    init_pair(POMODORO_LABEL_CYAN_WARNING_ID, COLOR_CYAN, COLOR_RED);
    init_pair(POMODORO_LABEL_CYAN_NORMAL_ID, COLOR_CYAN, -1);

    init_pair(POMODORO_LABEL_WHITE_WARNING_ID, COLOR_WHITE, COLOR_RED);
    init_pair(POMODORO_LABEL_WHITE_NORMAL_ID, COLOR_WHITE, -1);

    // Error message
    init_pair(ERROR_MESSAGE_RED_ID, 19, -1);
}

ColorID getDigitColor(unsigned char digitIndex){
    if(digitIndex >= 0 && digitIndex <= 5){
        return digitsColors[digitIndex];
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

PomodoroLabelColorPair getPomodoroLabelColorPair() {
    return pomodoroLabelColorPair;
}
