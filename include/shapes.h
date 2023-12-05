#ifndef SHAPES_GUARD
#define SHAPES_GUARD

#include "includes.h"

#define COLOR 1
#define INVIS 0
#define TIME_WINDOW_WIDTH 6
#define TIME_WINDOW_HEIGHT 5

typedef int ClockPixel;

ClockPixel (*getClockDigit(unsigned int digit))[3];
ClockPixel (*getClockColon())[3];

#endif 