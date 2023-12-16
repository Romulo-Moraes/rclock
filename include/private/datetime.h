#ifndef DATETIME_PRIVATE_GUARD
#define DATETIME_PRIVATE_GUARD

#include "./../public/datetime.h"

bool _checkIfDateOrTimesSegmentsAreDigits(char *customDateTime);
struct DateStruct _parseDate(struct DatetimeModule datetimeArguments);
struct TimeStruct _parseTime(struct DatetimeModule datetimeArguments);
void _setCustomTime(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments, char *errorOutput);
void _setCustomHourMinuteAndSecond(struct tm *datetimeStruct, struct DatetimeModule dateTimeArguments);
void _setCustomDate(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments, char *errorOutput);
void _setCustomDayMonthAndYear(struct tm *datetimeStruct, struct DatetimeModule datetimeArguments);
void _verifyForDateAndTimeErrors(struct tm *datetimeStruct, char *errorOutput);

#endif