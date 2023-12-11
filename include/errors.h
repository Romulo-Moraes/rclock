#ifndef ERRORS_GUARD
#define ERRORS_GUARD

#include "global-includes.h"

#define MAX_ERROR_BUFFER_SZ 256
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
#define USELESS_ERROR_MESSAGE_ARGUMENTS (struct ErrorMessageArguments){}

typedef unsigned char ErrorID;

struct Error{
    char *message;
    ErrorID id;
};

struct ErrorMessageArguments{
    int unknownSpecificDigitColor;
};

char* generateErrorMessage(ErrorID errorID, struct ErrorMessageArguments arguments, char* errorOutput);

#endif