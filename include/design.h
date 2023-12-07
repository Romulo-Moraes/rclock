#ifndef DESIGN_GUARD
#define DESIGN_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "datetime.h"
#include "screen-manager.h"
#include "shapes.h"
#include "colors.h"

typedef unsigned char Digit;

void normalizeSegment(unsigned char number, unsigned char segmentNumbers[2]);
void fillClockSegment(WINDOW *clockWindows[], unsigned char numberToDraw);
void drawDate(struct tm *theTime, struct DatetimeModule datetimeArguments);
void drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID);
void fillClockColons();

#endif