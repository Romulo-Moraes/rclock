#ifndef DESIGN_HELPERS_GUARD
#define DESIGN_HELPERS_GUARD

#include <public/arguments.h>

void redrawTheEntireClock(ProgramArguments arguments, bool destroyTheWindows, struct tm *timeStruct);
void updateClock(struct tm timeStruct, struct tm timeStructOldValue, RclockMode mode);

#endif