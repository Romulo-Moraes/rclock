#ifndef DATETIME_HELPERS_GUARD
#define DATETIME_HELPERS_GUARD

#include <public/arguments.h>

void setCustomDateAndTime(ProgramArguments arguments, struct tm *timeStruct);
long long currentTimeInMilliseconds();

#endif