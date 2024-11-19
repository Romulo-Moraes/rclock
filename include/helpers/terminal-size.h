#ifndef TERMINAL_SIZE_GUARD
#define TERMINAL_SIZE_GUARD

#include <public/arguments.h>

void checkIfTheClockShouldBeSmaller(struct DatetimeScreenManagerDesignerModulesArguments arguments);
struct TerminalSizeError checkIfTerminalSizeIsCritical(ProgramArguments arguments);

#endif