/*
 * Copyright (c) 2024 Rômulo Peres de Moraes
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SHAPES_GUARD
#define SHAPES_GUARD

#define COLOR 1
#define INVIS 0
#define TIME_WINDOW_WIDTH 6
#define TIME_WINDOW_HEIGHT 5

typedef int ClockPixel;

ClockPixel (*getDigitShape(unsigned int digit))[3];
ClockPixel (*getColonShape())[3];

#endif 