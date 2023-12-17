#include "./../../include/public/errors.h"

struct Error errors[] = {
    (struct Error){.message = "The custom day was out of range", .id = MONTH_DAY_OUT_OF_RANGE},
    (struct Error){.message = "The custom month was out of range", .id = MONTH_OUT_OF_RANGE},
    (struct Error){.message = "The custom time format was wrong", .id = CUSTOM_TIME_FORMAT},
    (struct Error){.message = "The custom date format was wrong", .id = CUSTOM_DATE_FORMAT},
    (struct Error){.message = "The given custom time wasn't in a correct range", .id = CUSTOM_TIME_RANGE},
    (struct Error){.message = "The given custom date wasn't in a correct range", .id = CUSTOM_DATE_RANGE},
    (struct Error){.message = "The given clock color doesn't exist", .id = UNKNOWN_CLOCK_COLOR},
    (struct Error){.message = "The given digits color doesn't exist", .id = UNKNOWN_DIGITS_COLOR},
    (struct Error){.message = "The given colons color doesn't exist", .id = UNKNOWN_COLONS_COLOR},
    (struct Error){.message = "The given date color doesn't exist", .id = UNKNOWN_DATE_COLOR},
    (struct Error){.message = "The terminal width is extremely small", .id = TERMINAL_WIDTH_TOO_SMALL},
    (struct Error){.message = "The terminal height is extremely small", .id = TERMINAL_HEIGHT_TOO_SMALL},
    (struct Error){.message = "The provided custom hour wasn't numeric", .id = CUSTOM_HOUR_ISNT_NUMERIC},
    (struct Error){.message = "The provided custom minute wasn't numeric", .id = CUSTOM_MINUTE_ISNT_NUMERIC},
    (struct Error){.message = "The provided custom second wasn't numeric", .id = CUSTOM_SECOND_ISNT_NUMERIC},
};

struct Error specificDigitColorError = (struct Error){.message = "The given color of the digit %d doesn't exist", .id = UNKNOWN_SPECIFIC_DIGIT_COLOR};

// Forward declarations

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