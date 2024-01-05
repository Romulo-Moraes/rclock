/*
 * Colors module: A module for color customization
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */


#include "./../../include/private/colors.h"

// Private functions

void _setColorToTheDigits(ColorID newColor, ColorID digitColors[]){
    for(int i = 0; i < MAX_DIGIT_COLORS; i++){
        digitColors[i] = newColor;
    }
}

void _setColorToTheClock(ColorID newColor, ColorID *colonsColor, ColorID digitColors[]){\
    _setColorToTheDigits(newColor, digitColors);

    *colonsColor = newColor;
}

struct RclockColor* _searchForColor(char *colorName, struct RclockColor *availableColors, size_t sizeOfAvailableColors){

    for(short i = 0; i < sizeOfAvailableColors; i++){
        if(strcmp(colorName, availableColors[i].colorName) == 0){
            return &availableColors[i];
        }
    }

    return NULL;
}

void _setGlobalDigitsColor(struct ColorsModule userArguments, char *errorOutput, struct RclockColor availableColors[], size_t sizeOfAvailableColors, ColorID digitColors[]){
    struct RclockColor *colorSearchResult;

   if(userArguments.globalDigitsColor != NULL){
        colorSearchResult = _searchForColor(userArguments.globalDigitsColor, availableColors, sizeOfAvailableColors);

        if(colorSearchResult != NULL){
            _setColorToTheDigits(colorSearchResult->clockID, digitColors);
        }else{
            generateErrorMessage(UNKNOWN_DIGITS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void _setClockColor(struct ColorsModule userArguments, char *errorOutput, ColorID *colonsColor, ColorID digitsColor[], struct RclockColor availableColors[], size_t sizeOfAvailableColors){
    struct RclockColor *colorSearchResult;

    if(userArguments.clockColor != NULL){
        
        colorSearchResult = _searchForColor(userArguments.clockColor, availableColors, sizeOfAvailableColors);

        if(colorSearchResult != NULL){
            _setColorToTheClock(colorSearchResult->clockID, colonsColor, digitsColor);
        }else{
            generateErrorMessage(UNKNOWN_CLOCK_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void _setDateColor(struct ColorsModule userArguments, char* errorOutput, ColorID *dateColor, struct RclockColor availableColors[], size_t sizeOfAvailableColors){
    struct RclockColor *colorSearchResult;

    if(userArguments.dateColor != NULL){
        colorSearchResult = _searchForColor(userArguments.dateColor, availableColors, sizeOfAvailableColors);

        if(colorSearchResult != NULL){
            *dateColor = colorSearchResult->dateID;
        }else{
            generateErrorMessage(UNKNOWN_DATE_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
        }
    }
}

void _setColonColor(struct ColorsModule userArguments, char* errorOutput, ColorID *colonsColor, struct RclockColor availableColors[], size_t sizeOfAvailableColors){
    struct RclockColor *colorSearchResult;

    if(userArguments.colonColor != NULL){
        colorSearchResult = _searchForColor(userArguments.colonColor, availableColors, sizeOfAvailableColors);

        if(colorSearchResult != NULL){
            *colonsColor = colorSearchResult->clockID;
        }else{
            generateErrorMessage(UNKNOWN_COLONS_COLOR, USELESS_ERROR_MESSAGE_ARGUMENTS, errorOutput);
            return;
        }
    }
}

void _setColorForEachClockDigit(struct ColorsModule userArguments, char* errorOutput, ColorID digitColors[], struct RclockColor availableColors[], size_t sizeOfAvailableColors){
    struct RclockColor *colorSearchResult;

    for(int i = 0; i < MAX_DIGIT_COLORS; i++){
        if(userArguments.digitColor[i] != NULL){
            colorSearchResult = _searchForColor(userArguments.digitColor[i], availableColors, sizeOfAvailableColors);

            if(colorSearchResult != NULL){
                digitColors[i] = colorSearchResult->clockID;
            }else{
                generateErrorMessage(UNKNOWN_SPECIFIC_DIGIT_COLOR, (struct ErrorMessageArguments){.unknownSpecificDigitColor = i + 1}, errorOutput);
            }
        }
    }
}
