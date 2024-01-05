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

#ifndef SCREEN_MANAGER_GUARD
#define SCREEN_MANAGER_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "shapes.h"
#include "datetime.h"

#define DEFAULT_CLOCK_HEIGHT 12
#define DEFAULT_CLOCK_WIDTH 60
#define MINIMUM_TERMINAL_WIDTH 35
#define MINIMUM_TERMINAL_HEIGHT 7
#define MAX_CLOCK_TIME_WINDOWS 8
#define MAX_CLOCK_DIGIT_WINDOWS 6
#define WINDOWS_COUNT_WITH_HIDDEN_SECONDS 5
#define WINDOWS_COUNT_WITH_VISIBLE_SECONDS 8
#define HOURS_SEGMENT 0
#define MINUTES_SEGMENT 3
#define SECONDS_SEGMENT 6
#define FIRST_CLOCK_COLON 2
#define SECOND_CLOCK_COLON 5
#define ERROR_MESSAGE_WINDOW_HEIGHT 5
#define EXIT_MESSAGE_WINDOW_HEIGHT 3
#define EXIT_MESSAGE "Press any key to exit"

typedef unsigned char SegmentIndex;
typedef unsigned char WindowRole;

struct WindowSize{
    unsigned int width;
    unsigned int height;
};

struct WindowPosition{
    int x;
    int y;
};

struct RclockWindow{
    WINDOW *window;
    struct WindowPosition position;
};

struct WindowsAttributes{
    short clockWindowsCount;
    short dateStringLength;
};

struct Windows{
    struct RclockWindow clockWindows[8];
    struct RclockWindow dateWindow;
    struct WindowsAttributes windowsAttributes;
};

struct ErrorWindowsMeasures{
    size_t errorWindowWidth;
    size_t errorWindowTop;
    size_t errorWindowLeft;
    size_t exitMessageWindowTop;
    size_t exitMessageWindowWidth;
};

struct ErrorWindows{
    WINDOW *errorWindow;
    WINDOW *exitMessageWindow;
    struct ErrorWindowsMeasures measures;   
};

struct TerminalSizeError{
    bool thereIsAnError;
    ErrorID errorID;
    bool (*validationCallback)(void *arguments);
};

struct ErrorUpdateCallbacksArguments{
  struct ErrorWindows windows;
  char *errorMsg;
  char *exitErrorMsg;
};

bool checkIfTheDateShouldBeInvisible();
bool checkIfTheSecondsShouldBeInvisible();
struct ErrorWindows generateErrorWindows(float errorWindowWidthFraction, bool enableExitMessage);
void moveTimeWindowsToPlaceholders();
void moveDateWindowToPlaceholder();
void loadInitialTerminalSize();
bool detectTerminalResizes();
WINDOW** getClockSegment(unsigned int windowIndex, WINDOW *output[2]);
void setDateStringLength(size_t newLength);
WINDOW *getDateWindow();
void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments);
void setPlaceHolders(ProgramArguments arguments);
void refreshWindows();
bool checkIfTerminalHeightIsCritical();
bool checkIfTerminalWidthIsCritical();
void toggleSecondsVisibility();
void toggleDatesVisibility();
void setValuesForClockStates(ProgramArguments arguments);
void destroyRclockWindows(ProgramArguments arguments);
void updateErrorMessageFrames(struct ErrorWindows windows, float errorWindowWidthFraction, char *errorMessage, void (*drawProgramErrorCallback)(void *arguments), void *drawErrorArguments, bool (*errorVerificationCallback)(), bool enableExitMessage);
bool checkIfTheSecondsIsVisible();
bool checkIfTheDateIsVisible();


#endif