#ifndef COLORS_GUARD
#define COLORS_GUARD

// #include "includes.h"
#include "global-includes.h"
#include "errors.h"
#include "screen-manager.h"
#include "arguments.h"

#define BLACK_ID 1
#define RED_ID 2
#define GREEN_ID 3
#define YELLOW_ID 4
#define BLUE_ID 5
#define MAGENTA_ID 6 
#define CYAN_ID 7
#define WHITE_ID 8
#define DEFAULT_COLOR BLUE_ID

typedef int ColorID;

struct RclockColor{
    char *colorName;
    ColorID id;
};

void setComponentsColors(struct ColorsModule userArguments, char* errorOutput);
ColorID getDigitColor(unsigned char digitIndex);
ColorID getColonColor();
ColorID getDateColor();
void loadBuiltinColors();

#endif