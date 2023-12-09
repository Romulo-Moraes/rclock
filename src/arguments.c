#include "./../include/arguments.h"

ProgramArguments defaultProgramArguments = {
     .colors = {.clockColor = NULL, .colonColor = NULL, .dateColor = NULL, .digitColor = {NULL},
                .globalDigitsColor = NULL},

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