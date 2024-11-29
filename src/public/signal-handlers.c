#include <signal.h>
#include <public/colors.h>
#include <public/pomodoro.h>
#include <public/design.h>
#include <public/user-input.h>
#include <public/notification.h>

static bool backgroundIsRed = true;
static struct tm *timeStruct;
static uint8_t secondsElapsedSinceTimeout = 0;

void resetPomodoroWarningState() {
    backgroundIsRed = true;
}

bool checkIfClockIsInPomodoroWarningState() {
    return !backgroundIsRed;
}

void resetTimeElapsedSinceTimeout() {
    secondsElapsedSinceTimeout = 0;
}

static void blinkPomodoroClock(bool warning) {
    changeMainWindowBackgroundColor(warning);
    drawAllClockWindows(timeStruct, (struct DatetimeScreenManagerDesignerModulesArguments) {.hideTheSeconds = false}, warning);
    drawOptions(warning);
    drawPomodoroStatusWindow(warning);
}

void configureSignalHandlerModule(struct tm *time) {
    timeStruct = time;
}

void pomodoroTimeoutHandler(int signal) {
    if (signal == SIGALRM) {
        
        if (secondsElapsedSinceTimeout == 0) {
            if (getPomodoroState().turn == POMODORO) {
                sendNotification("Rclock - Pomodoro", "The pomodoro is over, time to rest!");    
            } else {
                sendNotification("Rclock - Pomodoro", "The rest time is over, time to focus!");
            }
        }

        secondsElapsedSinceTimeout = (secondsElapsedSinceTimeout + 1) % 20;

        tryToResetTheClicks();
        
        if (checkIfTerminalHeightIsCritical(POMODORO_MODE) == false && checkIfTerminalWidthIsCritical(POMODORO_MODE) == false){
            blinkPomodoroClock(backgroundIsRed);
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