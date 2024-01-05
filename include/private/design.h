/*
 * Design module: A module for drawing components on screen
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef DESIGN_PRIVATE_GUARD
#define DESIGN_PRIVATE_GUARDA

#include "./../public/design.h"

void _normalizeSegment(unsigned char number, Digit segmentDigits[2]);
void _drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID);
void _fillClockColons(struct DatetimeScreenManagerDesignerModules userArguments);
void _writeErrorMessageOnErrorWindow(char *msg, size_t windowWidth, WINDOW *errorWindow);

#endif