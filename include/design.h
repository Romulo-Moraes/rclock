#ifndef DESIGN_GUARD
#define DESIGN_GUARD

#include "includes.h"

typedef unsigned char Digit;

void normalizeSegment(unsigned char number, unsigned char segmentNumbers[2]);
void drawSegment(WINDOW *clockWindows[], unsigned short baseSegmentIndex, unsigned char numberToDraw);
void drawDate(struct tm *theTime, struct DatetimeModule datetimeArguments);

#endif