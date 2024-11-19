#include <helpers/modes.h>
#include <helpers/datetime.h>

void setModeData(ProgramArguments *arguments, struct tm *timeStruct){
    if (arguments->mode == CLOCK_MODE) {
        setCustomDateAndTime(*arguments, timeStruct);
    } else {
        struct TimeStruct time = getPomodoroTime();
        
        arguments->DatetimeScreenManagerDesigner.hideTheDate = true;
        timeStruct->tm_hour = time.hours;
        timeStruct->tm_min = 0;
        timeStruct->tm_sec = 2;
    }
}