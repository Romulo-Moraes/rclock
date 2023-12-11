#ifndef SCREEN_MANAGER_GUARD
#define SCREEN_MANAGER_GUARD

#include "global-includes.h"
#include "arguments.h"
#include "shapes.h"
#include "errors.h"
#include "colors.h"
#include "datetime.h"

#define MINIMUM_TERMINAL_WIDTH 35
#define MINIMUM_TERMINAL_HEIGHT_WITH_DATE 12
#define MINIMUM_TERMINAL_HEIGHT_WITHOUT_DATE 7
#define MAX_CLOCK_TIME_WINDOWS 8
#define MAX_CLOCK_DIGIT_WINDOWS 6
#define WINDOWS_COUNT_WITH_HIDDEN_SECONDS 5
#define WINDOWS_COUNT_WITH_VISIBLE_SECONDS 8
#define HOURS_SEGMENT 0
#define MINUTES_SEGMENT 3
#define SECONDS_SEGMENT 6
#define FIRST_CLOCK_COLON 2
#define SECOND_CLOCK_COLON 5
#define SMALL_CLOCK 0
#define LARGE_CLOCK 1
#define ERROR_MESSAGE_WINDOW_HEIGHT 5
#define EXIT_MESSAGE_WINDOW_HEIGHT 3
#define EXIT_MESSAGE "Press any key to exit"

typedef unsigned char SegmentIndex;
typedef unsigned char ClockState;

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

struct ErrorWindows{
    WINDOW *errorWindow;
    WINDOW *exitMessageWindow;
};

struct ErrorWindowsMeasures{
    size_t errorWindowWidth;
    size_t errorWindowTop;
    size_t errorWindowLeft;
    size_t exitMessageWindowTop;
    size_t exitMessageWindowWidth;
};

ClockState hideAndShowSecondsIfTerminalsTooSmall();
bool showErrorMessageIfTerminalIsExtremelySmall(struct DatetimeScreenManagerDesignerModules userArguments);
struct ErrorWindows showProgramError(char *msg, float errorWindowWidthFraction, bool enableExitMessage);
void moveTimeWindowsToPlaceholders();
void moveDateWindowToPlaceholder();
void loadInitialTerminalSize();
bool detectTerminalResizes();
WINDOW **getClockSegment(unsigned int windowIndex);
void setDateStringLength(size_t newLength);
WINDOW *getDateWindow();
void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments);
void setPlaceHolders();
void refreshWindows();










void getTerminalSize(unsigned int *width, unsigned int *height);


#endif