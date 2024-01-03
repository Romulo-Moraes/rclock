#ifndef DESIGN_PRIVATE_GUARD
#define DESIGN_PRIVATE_GUARDA

#include "./../public/design.h"

void _normalizeSegment(unsigned char number, Digit segmentDigits[2]);
void _drawClockWindow(WINDOW *targetWindow, ClockPixel (*shapeToBeDrawn)[3], ColorID digitColorID);
void _fillClockColons(struct DatetimeScreenManagerDesignerModules userArguments);
void _writeErrorMessageOnErrorWindow(char *msg, size_t windowWidth, WINDOW *errorWindow);

#endif