#include <helpers/datetime.h>
#include <time.h>
#include <public/datetime.h>

void setCustomDateAndTime(ProgramArguments arguments, struct tm *timeStruct){
    char errorBuffer[512] = {0};

    setNewTime(timeStruct, arguments.datetime, errorBuffer);
    setNewDate(timeStruct, arguments.datetime, errorBuffer);

    verifyForDateAndTimeErrors(timeStruct, errorBuffer);

    saveInitialProgramTime(timeStruct);
}