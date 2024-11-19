/*
 * Datetime module: A module for date/time operations
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef DATETIME_PRIVATE_GUARD
#define DATETIME_PRIVATE_GUARD

#include "./../public/datetime.h"

char *_createZerosPaddingForTheYear(int year, char *outputPadding);
bool _checkIfDateOrTimesSegmentsAreDigits(char *customDateTime);
struct DateStruct _parseDate(struct DatetimeModuleArguments datetimeArguments);
struct TimeStruct _parseTime(struct DatetimeModuleArguments datetimeArguments);
void _setCustomTime(struct tm *datetimeStruct, struct DatetimeModuleArguments dateTimeArguments, char *errorOutput);
void _setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModuleArguments dateTimeArguments);
void _setCustomDate(struct tm *datetimeStruct, struct DatetimeModuleArguments datetimeArguments, char *errorOutput);
void _setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModuleArguments datetimeArguments);

#endif