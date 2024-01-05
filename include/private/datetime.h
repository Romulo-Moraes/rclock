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
struct DateStruct _parseDate(struct DatetimeModule datetimeArguments);
struct TimeStruct _parseTime(struct DatetimeModule datetimeArguments);
void _setCustomTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput);
void _setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments);
void _setCustomDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput);
void _setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments);

#endif