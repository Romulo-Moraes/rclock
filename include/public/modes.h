#include <public/arguments.h>

void pomodoroMode(struct tm *timeStruct, struct tm *timeStructOldValue, void (*timeoutHandler)(int));
void clockMode(struct DatetimeModuleArguments datetime, struct ColorsModuleArguments colors, struct tm *timeStruct, struct tm *timeStructOldValue);
struct tm generateTimeStructToBeRenderedBasedOnClockMode(RclockMode mode, struct tm timeStruct);