#ifndef ERRORS_GUARD
#define ERRORS_GUARD

#include "includes.h"

#define MONTH_DAY_OUT_OF_RANGE 0
#define MONTH_OUT_OF_RANGE 1
#define CUSTOM_TIME_FORMAT 2
#define CUSTOM_DATE_FORMAT 3
#define CUSTOM_TIME_RANGE 4
#define CUSTOM_DATE_RANGE 5

void issueAnError(unsigned int errorID);

#endif