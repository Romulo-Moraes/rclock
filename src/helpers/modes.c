#include <helpers/modes.h>
#include <helpers/datetime.h>

// start time

void setModeData(ProgramArguments *arguments, struct tm *timeStruct){
    if (arguments->mode == CLOCK_MODE) {
        setCustomDateAndTime(*arguments, timeStruct);
    } else {
        struct TimeStruct time = getPomodoroTime();
        
        arguments->DatetimeScreenManagerDesigner.hideTheDate = true;
        timeStruct->tm_hour = time.hours;
        timeStruct->tm_min = time.minutes;
        timeStruct->tm_sec = time.seconds;
    }
}