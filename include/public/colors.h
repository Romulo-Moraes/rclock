/*
 * Colors module: A module for color customization
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef COLORS_GUARD
#define COLORS_GUARD

#include "global-includes.h"
#include "errors.h"
#include "arguments.h"

#define BLACK_ID 1
#define RED_ID 2
#define GREEN_ID 3
#define YELLOW_ID 4
#define BLUE_ID 5
#define MAGENTA_ID 6 
#define CYAN_ID 7
#define WHITE_ID 8
#define DATE_BLACK_ID 9
#define DATE_RED_ID 10
#define DATE_GREEN_ID 11
#define DATE_YELLOW_ID 12
#define DATE_BLUE_ID 13
#define DATE_MAGENTA_ID 14
#define DATE_CYAN_ID 15
#define DATE_WHITE_ID 16
#define ERROR_MESSAGE_RED_ID 17
#define DEFAULT_COLOR BLUE_ID
#define DEFAULT_DATE_COLOR DATE_BLUE_ID
#define MAX_DIGIT_COLORS 6
#define HOURS_INDEX 0
#define MINUTES_INDEX 2
#define SECONDS_INDEX 4

typedef int ColorID;

struct RclockColor{
    char *colorName;
    ColorID clockID;
    ColorID dateID;
};

void setComponentsColors(struct ColorsModule userArguments, char* errorOutput);
void loadBuiltinColors();
ColorID getDigitColor(unsigned char digitIndex);
ColorID getColonColor();
ColorID getDateColor();


#endif