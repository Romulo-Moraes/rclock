/*
 * Screen-manager module: A module for managing screen operations and states
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program can be distributed under the terms of the GNU GPL-3.0.
 * See the file COPYING.
 */

#ifndef SCREENMANAGER_PRIVATE_GUARD
#define SCREENMANAGER_PRIVATE_GUARD

#include "./../public/screen-manager.h"

void _getTerminalSize(unsigned int *width, unsigned int *height);
struct ErrorWindowsMeasures _calculateErrorWindowsMeasures(float errorWindowWidthFraction, struct WindowSize winSize);

#endif