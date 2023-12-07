#ifndef ERRORS_GUARD
#define ERRORS_GUARD

#include "global-includes.h"

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
#define USELESS_ERROR_MESSAGE_ARGUMENTS (struct ErrorMessageArguments){}

struct ErrorMessageArguments{
    int unknownSpecificDigitColor;
};

//void issueAnError(char *errorMsg);
void generateErrorMessage(unsigned int errorID, struct ErrorMessageArguments argumentsg, char* errorOutput);

#endif