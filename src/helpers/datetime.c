#define _POSIX_C_SOURCE 200809L

#include <helpers/datetime.h>
#include <time.h>
#include <public/datetime.h>

long long currentTimeInMilliseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    // Convert seconds to milliseconds and add nanoseconds as milliseconds
    return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

void setCustomDateAndTime(ProgramArguments arguments, struct tm *timeStruct){
    char errorBuffer[512] = {0};

    setNewTime(timeStruct, arguments.datetime, errorBuffer);
    setNewDate(timeStruct, arguments.datetime, errorBuffer);

    verifyForDateAndTimeErrors(timeStruct, errorBuffer);

    saveInitialProgramTime(timeStruct);
}