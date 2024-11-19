#include <inttypes.h>
#include <private/datetime.h>
#include <public/pomodoro.h>

static struct PomodoroState state = (struct PomodoroState) {
    .turn = POMODORO,
    .hasStarted = false,
    .paused = false,
    .timeoutStatus = (struct TimeoutStatus) {
        .timeout = false
    }
};

static uint8_t intervalCount = 0;

void incrementIntervalsCount() {
    intervalCount++;
}

struct TimeStruct getRestTime(){
    struct TimeStruct restTime;

    if (intervalCount < 4) {
        restTime = (struct TimeStruct) {
            .hours = 0,
            .minutes = 5,
            .seconds = 0
        };
    } else {
        restTime = (struct TimeStruct) {
            .hours = 0,
            .minutes = 15,
            .seconds = 0
        };
    }

    return restTime; 
}

struct TimeStruct getPomodoroTime(){
    struct TimeStruct taskTime;

    taskTime = (struct TimeStruct) {
        .hours = 0,
        .minutes = 25,
        .seconds = 0
    };

    return taskTime;
}

struct PomodoroState getPomodoroState() {
    return state;
}

void togglePauseState() {
    state.paused = !state.paused;
}

void setTimeout(TimeoutType status) {
    state.timeoutStatus.timeout = true;
    state.timeoutStatus.type = status;
}

void togglePomodoroTurn() {
    state.turn = state.turn == POMODORO ? REST : POMODORO;
}

void restartTimer() {
    state.hasStarted = false;
    state.timeoutStatus.timeout = false;
}

void startTimer() {
    state.hasStarted = true;
}