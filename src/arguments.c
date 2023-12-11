#include "./../include/arguments.h"

ProgramArguments defaultProgramArguments = {
     .colors = {.clockColor = DEFAULT_CLOCK_COLOR, .colonColor = NULL, .dateColor = DEFAULT_CLOCK_COLOR , .digitColor = {NULL},
                .globalDigitsColor = NULL},

     .datetime = {.customDate = NULL, .customDay = UNDEFINED, .customHour = UNDEFINED,
                  .customMinute = UNDEFINED, .customMonth = UNDEFINED, .customSecond = UNDEFINED,
                  .customTime = NULL, .customYear = UNDEFINED, .dateFormat = NULL},

     .DatetimeScreenManagerDesigner = {.hideTheDate = false/*DEFAULT_HIDE_THE_DATE_STATE*/, .hideTheSeconds = DEFAULT_HIDE_THE_SECONDS_STATE}
 };

void createProgramArguments( ){

}

ProgramArguments fetchProgramArguments(){
    return defaultProgramArguments;
}