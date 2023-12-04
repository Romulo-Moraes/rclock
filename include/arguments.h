#ifndef ARGUMENTS_GUARD
#define ARGUMENTS_GUARD

#include "includes.h"

#define UNDEFINED -1

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
    char *digitColor[6];
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
