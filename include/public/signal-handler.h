#ifndef SIGNAL_HANDLER_GUARD
#define SIGNAL_HANDLER_GUARD

void clockSignalHandler(int signal);
void configureSignalHandlerModule(struct tm *timeStruct);
void pomodoroTimeoutHandler(int signal);
void resetTimeElapsedSinceTimeout();
void pomodoroSignalHandler(int signal);
bool checkIfClockIsInPomodoroWarningState();
void resetPomodoroWarningState();

#endif