#include <public/colors.h>
#include <public/pomodoro.h>
#include <time.h>
#include <ctype.h>
#include <public/datetime.h>
#include <public/design.h>
#include <helpers/datetime.h>
#include <public/signal-handler.h>

#define EXIT_DELAY_THRESHOLD 350

static uint8_t clicksInOneSecond = 0;
long long clickSequenceBegin;

static void startPomodoroTimer();
static void pausePomodoroTimer();
static void unpausePomodoroTimer();
static void finishTimeoutAlert(ProgramArguments arguments, struct tm *timeStruct);

void tryToResetTheClicks() {
    long long now = currentTimeInMilliseconds();

    if (clicksInOneSecond != 0 && now - clickSequenceBegin > EXIT_DELAY_THRESHOLD) {
        clicksInOneSecond = 0;
    }
}

void handleUserInput(char input, ProgramArguments arguments, struct tm *timeStruct, struct tm *timeStructOldValue, bool *keepRunningProgram) {
    long long now;
    
    input = tolower(input);

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
                finishTimeoutAlert(arguments, timeStruct);
                break;
        }
    }

    if (input == '\n') {
        if (arguments.mode == POMODORO_MODE) {
                clicksInOneSecond++;

        if (clicksInOneSecond == 1) {
            clickSequenceBegin = currentTimeInMilliseconds();
        } else {
                now = currentTimeInMilliseconds();

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
    drawOptions(false);
    alarm(1);
}

static void pausePomodoroTimer() {
    if (getPomodoroState().paused == false) {
        togglePauseState();
        drawOptions(false);
    }
}

static void unpausePomodoroTimer() {
    if (getPomodoroState().paused == true) {
        togglePauseState();
        drawOptions(false);
    }
}

static void finishTimeoutAlert(ProgramArguments arguments, struct tm *timeStruct) {
    if (getPomodoroState().timeoutStatus.timeout == true) {
        struct tm timeStructToRender;
        togglePomodoroTurn();
        restartTimer();
        resetPomodoroWarningState();

        drawOptions(BACKGROUND_TRANSPARENT_ID);
        drawPomodoroStatusWindow(false);
        
        resetTimeElapsedSinceTimeout();
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

        drawAllClockWindows(&timeStructToRender, arguments.DatetimeScreenManagerDesigner, false);
        drawOptions(false);
        drawPomodoroStatusWindow(false);
    }
}