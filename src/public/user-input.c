#include <public/colors.h>
#include <public/pomodoro.h>
#include <time.h>
#include <public/datetime.h>
#include <public/design.h>

static void startPomodoroTimer();
static void pausePomodoroTimer();
static void unpausePomodoroTimer();
static void finishTimeoutAlert(ProgramArguments arguments, struct tm *timeStruct, void (*pomodoroSignalHandler)(int));

void handleUserInput(char input, ProgramArguments arguments, struct tm *timeStruct, struct tm *timeStructOldValue, void (*pomodoroSignalHandler)(int), bool *keepRunningProgram) {
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
        *keepRunningProgram = false;
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