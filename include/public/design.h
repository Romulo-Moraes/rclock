#ifndef DESIGN_GUARD
#define DESIGN_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "datetime.h"
#include "screen-manager.h"
#include "shapes.h"
#include "colors.h"

typedef unsigned char Digit;

void drawAllClockWindows(struct tm *timeStruct, struct DatetimeScreenManagerDesignerModules userArguments);
void fillClockSegment(WINDOW *clockWindows[], unsigned char numberToDraw, unsigned char windowIndex);
void drawDate(struct tm *theTime, struct DatetimeModule datetimeArguments, struct ColorsModule colorArguments);
void drawProgramErrorCallback(void *arguments);

#endif