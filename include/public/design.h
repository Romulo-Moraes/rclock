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

void drawAllClockWindows(struct tm *timeStruct, struct DatetimeScreenManagerDesignerModulesArguments userArguments, ColorID digitBackgroundColor);
void fillClockSegment(WINDOW *clockWindows[], unsigned char numberToDraw, unsigned char windowIndex, ColorID digitBackgroundColor);
void drawDate(struct tm *theTime, struct DatetimeModuleArguments datetimeArguments, struct ColorsModuleArguments colorArguments);
void changeMainWindowBackgroundColor(int colorID);
void drawProgramErrorCallback(void *arguments);
void drawOptions(ColorID backgroundColor);
void drawPomodoroStatusWindow(ColorID backgroundColorID);

#endif