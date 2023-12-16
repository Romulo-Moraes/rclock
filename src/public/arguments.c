#include "./../../include/public/arguments.h"

ProgramArguments defaultProgramArguments = {
     .colors = {.clockColor = DEFAULT_CLOCK_COLOR, .colonColor = NULL, .dateColor = DEFAULT_CLOCK_COLOR , .digitColor = {NULL},
                .globalDigitsColor = NULL},

     .datetime = {.customDate = NULL, .customDay = UNDEFINED, .customHour = UNDEFINED,
                  .customMinute = UNDEFINED, .customMonth = UNDEFINED, .customSecond = UNDEFINED,
                  .customTime = NULL, .customYear = UNDEFINED, .dateFormat = NULL},

     .DatetimeScreenManagerDesigner = {.hideTheDate = false/*DEFAULT_HIDE_THE_DATE_STATE*/, .hideTheSeconds = DEFAULT_HIDE_THE_SECONDS_STATE}
};

// This procedure uses the Anemone third-party library to define all
// user arguments that will be fetched by the fetchProgramArguments()
void createProgramArguments( ){

}

// This function will fetch and return all user arguments given by command-line arguments
ProgramArguments fetchProgramArguments(){
    return defaultProgramArguments;
}