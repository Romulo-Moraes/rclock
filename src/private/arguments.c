/*
 * Arguments module: A module for command-line inputs
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#include "../../include/private/arguments.h"


ErrorID _validateHoursMinutesSecondsDaysMonthsAndYears(struct DatetimeModule *argumentsOutput, anemone_struct *anemone){
    anemone_optional_return_value argument;

    if((argument = get_optional_argument(*anemone, "--custom-hour")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customHour = atoi(argument.value);
        }else{
            return CUSTOM_HOUR_ISNT_NUMERIC;
        }
    }

    if((argument = get_optional_argument(*anemone, "--custom-minute")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customMinute = atoi(argument.value);
        }else{
            return CUSTOM_MINUTE_ISNT_NUMERIC;
        }
    }

    if((argument = get_optional_argument(*anemone, "--custom-second")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customSecond = atoi(argument.value);
        }else{
            return CUSTOM_SECOND_ISNT_NUMERIC;
        }
    }

    if((argument = get_optional_argument(*anemone, "--custom-day")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customDay = atoi(argument.value);
        }else{
            return CUSTOM_DAY_ISNT_NUMERIC;
        }
    }

    if((argument = get_optional_argument(*anemone, "--custom-month")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customMonth = atoi(argument.value);
        }else{
            return CUSTOM_MONTH_ISNT_NUMERIC;
        }
    }

    if((argument = get_optional_argument(*anemone, "--custom-year")).set == ANEMONE_TRUE){
        if(_checkIfArgumentIsNumeric(argument.value) == true){
            argumentsOutput->customYear = atoi(argument.value);
        }else{
            return CUSTOM_YEAR_ISNT_NUMERIC;
        }
    }

    return NO_ERROR;
}

bool _checkIfArgumentIsNumeric(char *argument){
    while(*argument){
        if(!isdigit(*argument)){
            return false;
        }

        argument++;
    }

    return true;
}


void _fetchColorsArguments(anemone_struct *anemone, ProgramArguments *arguments){
    anemone_optional_return_value argument;

    if((argument = get_optional_argument(*anemone, "--clock-color")).set == ANEMONE_TRUE){
        arguments->colors.clockColor = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--date-color")).set == ANEMONE_TRUE){
        arguments->colors.dateColor = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-I")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[0] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-II")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[1] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-III")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[2] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-IV")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[3] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-V")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[4] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--color-VI")).set == ANEMONE_TRUE){
        arguments->colors.digitColor[5] = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--colon-color")).set == ANEMONE_TRUE){
        arguments->colors.colonColor = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--digits-color")).set == ANEMONE_TRUE){
        arguments->colors.globalDigitsColor = argument.value;
    }
}

ErrorID _fetchDatetimeArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments){
    anemone_optional_return_value argument;
    ErrorID errorId;

    if((argument = get_optional_argument(*anemone, "--date-format")).set == ANEMONE_TRUE){
        arguments->datetime.dateFormat = argument.value;
    }

    if((errorId = _validateHoursMinutesSecondsDaysMonthsAndYears(&arguments->datetime, anemone)) != NO_ERROR){
        generateErrorMessage(errorId, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);

        return errorId;
    }

    if((argument = get_optional_argument(*anemone, "--custom-time")).set == ANEMONE_TRUE){
        arguments->datetime.customTime = argument.value;
    }

    if((argument = get_optional_argument(*anemone, "--custom-date")).set == ANEMONE_TRUE){
        arguments->datetime.customDate = argument.value;
    }

    return NO_ERROR;
}

void _fetchScreenManagementArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments){
    anemone_optional_return_value argument;

    if((argument = get_optional_argument(*anemone, "--hide-seconds")).set == ANEMONE_TRUE){
        arguments->DatetimeScreenManagerDesigner.hideTheSeconds = true;
    }

    if(get_optional_argument(*anemone, "--hide-date").set == ANEMONE_TRUE){
        arguments->DatetimeScreenManagerDesigner.hideTheDate = true;
    }
}
