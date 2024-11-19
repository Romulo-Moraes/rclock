#ifndef USER_INPUT_GUARD
#define USER_INPUT_GUARD

#include <public/arguments.h>

void tryToResetTheClicks();
void handleUserInput(char input, ProgramArguments arguments, struct tm *timeStruct, struct tm *timeStructOldValue, void (*pomodoroSignalHandler)(int), bool *keepRunningProgram);

#endif