/*
 * Shapes module: A module for managing component shapes
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef SHAPES_GUARD
#define SHAPES_GUARD

#define COLOR 1
#define INVIS 0
#define TIME_WINDOW_WIDTH 6
#define TIME_WINDOW_HEIGHT 5

typedef int ClockPixel;

ClockPixel (*getDigitShape(unsigned int digit))[3];
ClockPixel (*getColonShape())[3];

#endif 