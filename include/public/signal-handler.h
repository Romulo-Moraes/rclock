#ifndef SIGNAL_HANDLER_GUARD
#define SIGNAL_HANDLER_GUARD

void configureSignalHandlerModule(struct tm *timeStruct);
void pomodoroTimeoutHandler(int signal);

#endif