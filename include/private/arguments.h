/*
 * Arguments module: A module for command-line inputs
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef ARGUMENTS_PRIVATE_GUARD
#define ARGUMENTS_PRIVATE_GUARD

#include "./../public/arguments.h"

ErrorID _validateHoursMinutesSecondsDaysMonthsAndYears(struct DatetimeModuleArguments *argumentsOutput, anemone_struct *anemone);
bool _checkIfArgumentIsNumeric(char *argument);
void _fetchColorsArguments(anemone_struct *anemone, ProgramArguments *arguments);
ErrorID _fetchDatetimeArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments);
void _fetchRclockModeArguments(anemone_struct *anemone, ProgramArguments *arguments);
void _fetchScreenManagementArguments(anemone_struct *anemone, char *errorOutput, ProgramArguments *arguments);

#endif