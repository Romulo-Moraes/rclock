#define _POSIX_C_SOURCE 200809L

#include <public/colors.h>
#include <public/pomodoro.h>
#include <time.h>
#include <stdio.h>
#include <public/datetime.h>
#include <public/design.h>

#define EXIT_DELAY_THRESHOLD 350

static uint8_t clicksInOneSecond = 0;
long long clickSequenceBegin;

static void startPomodoroTimer();
static void pausePomodoroTimer();
static void unpausePomodoroTimer();
static void finishTimeoutAlert(ProgramArguments arguments, struct tm *timeStruct, void (*pomodoroSignalHandler)(int));


long long current_time_in_milliseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    // Convert seconds to milliseconds and add nanoseconds as milliseconds
    return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

void tryToResetTheClicks() {
    long long now = current_time_in_milliseconds();

    if (clicksInOneSecond != 0 && now - clickSequenceBegin > EXIT_DELAY_THRESHOLD) {
        clicksInOneSecond = 0;
    }
}

void handleUserInput(char input, ProgramArguments arguments, struct tm *timeStruct, struct tm *timeStructOldValue, void (*pomodoroSignalHandler)(int), bool *keepRunningProgram) {
    long long now;
    if (arguments.mode == POMODORO_MODE) {
        switch (input) {
            case 's':
                startPomodoroTimer();
                break;
            case 'p':
                pausePomodoroTimer();
                break;
            case 'u':
                unpausePomodoroTimer();
                break;
            case 'o':
                finishTimeoutAlert(arguments, timeStruct, pomodoroSignalHandler);
                break;
        }
    }

    if (input == '\n') {
        if (arguments.mode == POMODORO_MODE) {
                clicksInOneSecond++;

        if (clicksInOneSecond == 1) {
            clickSequenceBegin = current_time_in_milliseconds();
        } else {
                now = current_time_in_milliseconds();

                if (clicksInOneSecond == 3) {
                    if (now - clickSequenceBegin < EXIT_DELAY_THRESHOLD) {
                        *keepRunningProgram = false;
                    } else {
                        clicksInOneSecond = 0;
                    }
                }
            }
        } else {
            *keepRunningProgram = false;
        }
    }
}


static void startPomodoroTimer() {
    startTimer();
    drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    alarm(1);
}

static void pausePomodoroTimer() {
    if (getPomodoroState().paused == false) {
        togglePauseState();
        drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    }
}

static void unpausePomodoroTimer() {
    if (getPomodoroState().paused == true) {
        togglePauseState();
        drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    }
}

static void finishTimeoutAlert(ProgramArguments arguments, struct tm *timeStruct, void (*pomodoroSignalHandler)(int)) {
    if (getPomodoroState().timeoutStatus.timeout == true) {
        struct tm timeStructToRender;
        togglePomodoroTurn();
        restartTimer();

        drawOptions(BACKGROUND_TRANSPARENT_ID);
        drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        signal(SIGALRM, pomodoroSignalHandler);
        struct TimeStruct time;

        if (getPomodoroState().turn == POMODORO) {
            time = getPomodoroTime();
        } else {
            incrementIntervalsCount();
            time = getRestTime();
        }

        timeStruct->tm_min = time.minutes;
        timeStruct->tm_sec = time.seconds;

        bkgd(COLOR_PAIR(BACKGROUND_TRANSPARENT_ID));
        refresh();

        if (arguments.mode == POMODORO_MODE && checkIfTheSecondsIsVisible() == false) {
            timeStructToRender = (struct tm) {
                .tm_hour = time.minutes,
                .tm_min = time.seconds
            };
        } else {
            timeStructToRender = *timeStruct;
        }

        drawAllClockWindows(&timeStructToRender, arguments.DatetimeScreenManagerDesigner, BACKGROUND_TRANSPARENT_ID);
        drawOptions(OPTIONS_BACKGROUND_TRANSPARENT_ID);
        drawPomodoroStatusWindow(OPTIONS_BACKGROUND_TRANSPARENT_ID);
    }
}