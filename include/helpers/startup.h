#ifndef STARTUP_GUARD
#define STARTUP_GUARD

#include <public/arguments.h>
#include <public/screen-manager.h>

void configureNcurses();
void configureRclock(ProgramArguments arguments, char *errorBuffer, void (*signalHandler)(int signal));
void initializeTheClock(ProgramArguments arguments, struct tm *timeStruct);
void createTerminalSizeError(struct TerminalSizeError sizeError);

#endif