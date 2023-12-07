#ifndef SCREEN_MANAGER_GUARD
#define SCREEN_MANAGER_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "shapes.h"

#define MAX_CLOCK_TIME_WINDOWS 8
#define MAX_CLOCK_DIGIT_WINDOWS 6
#define WINDOWS_COUNT_WITH_HIDDEN_SECONDS 5
#define WINDOWS_COUNT_WITH_VISIBLE_SECONDS 8
#define HOURS_SEGMENT 0
#define MINUTES_SEGMENT 3
#define SECONDS_SEGMENT 6
#define FIRST_CLOCK_COLON 2
#define SECOND_CLOCK_COLON 5
#define EXIT_MESSAGE "Press any key to exit"

typedef unsigned char SegmentIndex;

struct RclockWindows{
    WINDOW *dateWindow;
    WINDOW *timeWindows[MAX_CLOCK_TIME_WINDOWS];
    unsigned short timeWindowsCount;
};

struct WindowSize{
    unsigned int width;
    unsigned int height;
};

struct TimeWindowPosition{
    int x;
    int y;
};

struct DateWindowPosition{
    int y;
    size_t dateStringLength;
};

struct WindowsPlaceholders{
    struct TimeWindowPosition timeWindowsPositions[MAX_CLOCK_TIME_WINDOWS];
    struct DateWindowPosition dateWindowPosition;
};

void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments);
void setPlaceHolders();
void getTerminalSize();
bool detectTerminalResizes();
void moveTimeWindowsToPlaceholders();
void setDateStringLength(size_t newLength);
void moveDateWindowToPlaceholder();
void moveWindowsToPlaceholders();
void refreshWindows();
void showProgramError(char *msg);
WINDOW **getClockSegment(unsigned int windowIndex);
WINDOW *getDateWindow();

struct RclockWindows getWins();
struct WindowsPlaceholders getPos();
struct WindowSize getWinSz();

#endif