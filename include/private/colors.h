/*
 * Colors module: A module for color customization
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef COLORS_PRIVATE_GUARD
#define COLORS_PRIVATE_GUARD

#include "./../public/colors.h"

void _setColorToTheDigits(ColorID newColor, ColorID *digitColors);
void _setColorToTheClock(ColorID newColor, ColorID *colonsColor, ColorID digitColors[]);
struct RclockColor* _searchForColor(char *colorName, struct RclockColor *availableColors, size_t sizeOfAvailableColors);
void _setGlobalDigitsColor(struct ColorsModule userArguments, char *errorOutput, struct RclockColor availableColors[], size_t sizeOfAvailableColors, ColorID digitColors[]);
void _setClockColor(struct ColorsModule userArguments, char *errorOutput, ColorID *colonsColor, ColorID digitsColor[], struct RclockColor availableColors[], size_t sizeOfAvailableColors);
void _setDateColor(struct ColorsModule userArguments, char* errorOutput, ColorID *dateColor, struct RclockColor availableColors[], size_t sizeOfAvailableColors);
void _setColonColor(struct ColorsModule userArguments, char* errorOutput, ColorID *colonsColor, struct RclockColor availableColors[], size_t sizeOfAvailableColors);
void _setColorForEachClockDigit(struct ColorsModule userArguments, char* errorOutput, ColorID digitColors[], struct RclockColor availableColors[], size_t sizeOfAvailableColors);

#endif