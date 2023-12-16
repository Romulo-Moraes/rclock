#ifndef SCREENMANAGER_PRIVATE_GUARD
#define SCREENMANAGER_PRIVATE_GUARD

#include "./../public/screen-manager.h"

void _getTerminalSize(unsigned int *width, unsigned int *height);
struct ErrorWindowsMeasures _calculateErrorWindowsMeasures(float errorWindowWidthFraction, struct WindowSize winSize);

#endif