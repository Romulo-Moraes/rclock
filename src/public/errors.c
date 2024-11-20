/*
 * Errors module: A module for generating program errors
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include <public/errors.h>

struct Error errors[] = {
    (struct Error){.message = "The custom day was out of range", .id = MONTH_DAY_OUT_OF_RANGE},
    (struct Error){.message = "The custom month was out of range", .id = MONTH_OUT_OF_RANGE},
    (struct Error){.message = "Custom time format was incorrectly formatted", .id = CUSTOM_TIME_FORMAT},
    (struct Error){.message = "Custom date format was incorrectly formatted", .id = CUSTOM_DATE_FORMAT},
    (struct Error){.message = "Incorrect custom time value", .id = CUSTOM_TIME_RANGE},
    (struct Error){.message = "Incorrect custom date value", .id = CUSTOM_DATE_RANGE},
    (struct Error){.message = "Unknown clock color", .id = UNKNOWN_CLOCK_COLOR},
    (struct Error){.message = "Unknown digits color", .id = UNKNOWN_DIGITS_COLOR},
    (struct Error){.message = "Unknown colons color", .id = UNKNOWN_COLONS_COLOR},
    (struct Error){.message = "Unknown date color", .id = UNKNOWN_DATE_COLOR},
    (struct Error){.message = "The terminal width is extremely small", .id = TERMINAL_WIDTH_TOO_SMALL},
    (struct Error){.message = "The terminal height is extremely small", .id = TERMINAL_HEIGHT_TOO_SMALL},
    (struct Error){.message = "Custom hour value is not numeric", .id = CUSTOM_HOUR_ISNT_NUMERIC},
    (struct Error){.message = "Custom minute value is not numeric", .id = CUSTOM_MINUTE_ISNT_NUMERIC},
    (struct Error){.message = "Custom second value is not numeric", .id = CUSTOM_SECOND_ISNT_NUMERIC},
    (struct Error){.message = "Unknown color of pomodoro labels", .id = UNKNOWN_POMODORO_LABELS_COLOR},
};

struct Error specificDigitColorError = (struct Error){.message = "Unknown color of digit %d", .id = UNKNOWN_SPECIFIC_DIGIT_COLOR};

// Public functions

char* generateErrorMessage(ErrorID errorID, struct ErrorMessageArguments arguments, char* errorOutput){
    size_t errorsLength = sizeof(errors) / sizeof(errors[0]);

    for(short i = 0; i < errorsLength; i++){
        if(errors[i].id == errorID){
            strcpy(errorOutput, errors[i].message);

            return errorOutput;
        }
    }

    sprintf(errorOutput, specificDigitColorError.message, arguments.unknownSpecificDigitColor);

    return errorOutput;
}