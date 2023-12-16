#ifndef ARGUMENTS_GUARD
#define ARGUMENTS_GUARD

#include "global-includes.h"

#define UNDEFINED -1
#define MAX_DIGIT_COLORS 6
#define DEFAULT_CLOCK_COLOR "blue"
#define DEFAULT_HIDE_THE_DATE_STATE false
#define DEFAULT_HIDE_THE_SECONDS_STATE false

struct DatetimeModule{
    short customHour;
    short customMinute;
    short customSecond;
    char *customTime;
    short customDay;
    short customMonth;
    short customYear;
    char *customDate;
    char *dateFormat;
};

struct ColorsModule{
    char *digitColor[MAX_DIGIT_COLORS];
    char *globalDigitsColor;
    char *dateColor;
    char *clockColor;
    char *colonColor;
};

struct DatetimeScreenManagerDesignerModules{
    bool hideTheDate;
    bool hideTheSeconds;
};

typedef struct{
    struct DatetimeModule datetime;
    struct ColorsModule colors;
    struct DatetimeScreenManagerDesignerModules DatetimeScreenManagerDesigner;
} ProgramArguments;

void createProgramArguments( );
ProgramArguments fetchProgramArguments( );

#endif
