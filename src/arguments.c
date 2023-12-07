#include "./../include/arguments.h"

ProgramArguments defaultProgramArguments = {
     .colors = {.clockColor = NULL, .colonColor = UNDEFINED, .dateColor = UNDEFINED, .digitColor = {NULL},
                .globalDigitsColor = UNDEFINED},

     .datetime = {.customDate = NULL, .customDay = UNDEFINED, .customHour = UNDEFINED,
                  .customMinute = UNDEFINED, .customMonth = UNDEFINED, .customSecond = UNDEFINED,
                  .customTime = NULL, .customYear = UNDEFINED, .dateFormat = NULL},

     .DatetimeScreenManagerDesigner = {.hideTheDate = false, .hideTheSeconds = false}
 };

void createProgramArguments( ){

}

ProgramArguments fetchProgramArguments(){
    return defaultProgramArguments;
}