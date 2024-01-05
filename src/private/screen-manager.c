/*
 * Screen-manager module: A module for managing screen operations and states
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */


#include "./../../include/public/screen-manager.h"

void _getTerminalSize(unsigned int *width, unsigned int *height){
    getmaxyx(stdscr, *height, *width);
}


struct ErrorWindowsMeasures _calculateErrorWindowsMeasures(float errorWindowWidthFraction, struct WindowSize winSize){
    struct ErrorWindowsMeasures measures;

    measures.errorWindowWidth = winSize.width * (errorWindowWidthFraction <= 0 ? 0.5 : errorWindowWidthFraction);
    measures.errorWindowTop = winSize.height / 2 - 2;
    measures.errorWindowLeft = winSize.width * (1 - errorWindowWidthFraction) / 2;
    measures.exitMessageWindowWidth = winSize.width;
    measures.exitMessageWindowTop = winSize.height / 2 + 3;

    return measures;
}