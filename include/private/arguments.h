#ifndef ARGUMENTS_PRIVATE_GUARD
#define ARGUMENTS_PRIVATE_GUARD

#include "./../public/arguments.h"

ErrorID _validateHoursMinutesSecondsDaysMonthsAndYears(struct DatetimeModule *argumentsOutput, anemone_struct *anemone);
bool _checkIfArgumentIsNumeric(char *argument);
void _fetchColorsArguments(anemone_struct *anemone, ProgramArguments *arguments);
ErrorID _fetchDatetimeArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments);
void _fetchScreenManagementArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments);

#endif