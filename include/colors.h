#ifndef COLORS_GUARD
#define COLORS_GUARD

#include "includes.h"

#define DEFAULT_COLOR COLOR_BLUE

typedef int ColorID;

struct RclockColor{
    char *colorName;
    ColorID id;
};

void setComponentsColors();
ColorID getComponentColor();

#endif