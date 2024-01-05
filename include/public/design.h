/*
 * Design module: A module for drawing components on screen
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

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