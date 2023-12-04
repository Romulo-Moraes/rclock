#ifndef SHAPES_GUARD
#define SHAPES_GUARD

#define COLOR 1
#define INVIS 0

typedef int ClockPixel;

ClockPixel (*getClockDigit(unsigned int digit))[3];
ClockPixel (*getClockColon())[3];

#endif 