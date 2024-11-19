#include <signal.h>
#include <public/colors.h>
#include <public/pomodoro.h>
#include <public/design.h>
#include <public/user-input.h>

static bool backgroundIsRed = false;
static struct tm *timeStruct;

static void blinkPomodoroClock(ColorID backgroundID) {
    changeMainWindowBackgroundColor(backgroundID);
    drawAllClockWindows(timeStruct, (struct DatetimeScreenManagerDesignerModulesArguments) {.hideTheSeconds = false}, backgroundID);
    drawOptions(backgroundID == BACKGROUND_TRANSPARENT_ID ? OPTIONS_BACKGROUND_TRANSPARENT_ID : OPTIONS_BACKGROUND_RED_ID);
    drawPomodoroStatusWindow(backgroundID == BACKGROUND_TRANSPARENT_ID ? OPTIONS_BACKGROUND_TRANSPARENT_ID : OPTIONS_BACKGROUND_RED_ID);
}

void configureSignalHandlerModule(struct tm *time) {
    timeStruct = time;
}

void pomodoroTimeoutHandler(int signal) {
    if (signal == SIGALRM) {
        tryToResetTheClicks();
        
        switch(backgroundIsRed) {
            case true:
                blinkPomodoroClock(BACKGROUND_TRANSPARENT_ID);
                break;
            case false:
                blinkPomodoroClock(BACKGROUND_RED_ID);
                break;
        }

        backgroundIsRed = !backgroundIsRed;
        alarm(1);
    }
}

void pomodoroSignalHandler(int signal) {
    if (signal == SIGALRM) {
        tryToResetTheClicks();
        struct PomodoroState state = getPomodoroState();

        if (getPomodoroState().paused == false && state.hasStarted == true) {
            decrementClockSecond(timeStruct);
        }

        alarm(1);
    }
}

void clockSignalHandler(int signal){
    if (signal == SIGALRM) {
        tryToResetTheClicks();
        incrementClockSecond(timeStruct);
            
        if(timeStruct->tm_sec % 5 == 0){
            tryToUpdateTheClock(timeStruct);
        }

        alarm(1);
    }
}