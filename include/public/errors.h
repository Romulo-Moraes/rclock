/*
 * Errors module: A module for generating program errors
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef ERRORS_GUARD
#define ERRORS_GUARD

#include "global-includes.h"

#define MAX_ERROR_BUFFER_SZ 256
#define NO_ERROR -1
#define MONTH_DAY_OUT_OF_RANGE 0
#define MONTH_OUT_OF_RANGE 1
#define CUSTOM_TIME_FORMAT 2
#define CUSTOM_DATE_FORMAT 3
#define CUSTOM_TIME_RANGE 4
#define CUSTOM_DATE_RANGE 5
#define UNKNOWN_CLOCK_COLOR 6
#define UNKNOWN_DIGITS_COLOR 7
#define UNKNOWN_COLONS_COLOR 8
#define UNKNOWN_DATE_COLOR 9 
#define UNKNOWN_SPECIFIC_DIGIT_COLOR 10
#define TERMINAL_WIDTH_TOO_SMALL 11
#define TERMINAL_HEIGHT_TOO_SMALL 12
#define CUSTOM_HOUR_ISNT_NUMERIC 13
#define CUSTOM_MINUTE_ISNT_NUMERIC 14
#define CUSTOM_SECOND_ISNT_NUMERIC 15
#define CUSTOM_DAY_ISNT_NUMERIC 16
#define CUSTOM_MONTH_ISNT_NUMERIC 17
#define CUSTOM_YEAR_ISNT_NUMERIC 18
#define USELESS_ERROR_MESSAGE_ARGUMENTS (struct ErrorMessageArguments){}

typedef short ErrorID;


struct Error{
    char *message;
    ErrorID id;
};

struct ErrorMessageArguments{
    int unknownSpecificDigitColor;
};

char* generateErrorMessage(ErrorID errorID, struct ErrorMessageArguments arguments, char* errorOutput);

#endif