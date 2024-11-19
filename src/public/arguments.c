/*
 * Arguments module: A module for command-line inputs
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <public/arguments.h>
#include <private/arguments.h>

ProgramArguments defaultProgramArguments = {
     .colors = {.clockColor = DEFAULT_CLOCK_COLOR, .colonColor = NULL, .dateColor = DEFAULT_CLOCK_COLOR , .digitColor = {NULL},
                .globalDigitsColor = NULL},

     .datetime = {.customDate = NULL, .customDay = UNDEFINED, .customHour = UNDEFINED,
                  .customMinute = UNDEFINED, .customMonth = UNDEFINED, .customSecond = UNDEFINED,
                  .customTime = NULL, .customYear = UNDEFINED, .dateFormat = NULL},

     .DatetimeScreenManagerDesigner = {.hideTheDate = DEFAULT_HIDE_THE_DATE_STATE, .hideTheSeconds = DEFAULT_HIDE_THE_SECONDS_STATE}
};

// This procedure uses the Anemone third-party library to define all
// user arguments that will be fetched by the fetchProgramArguments()
anemone_struct createProgramArguments(int argc, char *argv[]){
    anemone_struct anemone;

    initialize_lib(&anemone, "Rclock", "1.0", "Digital terminal clock", "Rômulo Moraes (Cypher)", NULL, NULL);

    create_optional_argument(&anemone, "--hide-date", "-h", ANEMONE_FALSE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--clock-color", "-c", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--date-color" , "-d", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-I" , "-q", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-II" , "-Q", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-III" , "-P", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-IV" , "-p", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-V" , "-K", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--color-VI" , "-k", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--colon-color", "-o", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--digits-color", "-l", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--date-format" , "-f", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-hour", "-H", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-minute", "-M", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-second", "-S", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-time", "-T", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-day", "-D", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-month", "-O", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-year", "-Y", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--custom-date", "-D", ANEMONE_TRUE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--hide-seconds", "-i", ANEMONE_FALSE, ANEMONE_FALSE);
    create_optional_argument(&anemone, "--pomodoro", "-t", ANEMONE_FALSE, ANEMONE_FALSE);

    
    compile(&anemone, argc, argv);

    return anemone;
}

// This function will fetch and return all user arguments given by command-line arguments
ProgramArguments fetchProgramArguments(anemone_struct *anemone, char *errorOutput){

    _fetchColorsArguments(anemone, &defaultProgramArguments);
    
    _fetchDatetimeArguments(anemone, errorOutput, &defaultProgramArguments);

    _fetchScreenManagementArguments(anemone, errorOutput, &defaultProgramArguments);

    _fetchRclockModeArguments(anemone, &defaultProgramArguments);

    return defaultProgramArguments;
}