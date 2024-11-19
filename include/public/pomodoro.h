#ifndef POMODORO_GUARD
#define POMODORO_GUARD

#include <inttypes.h>
#include <stdbool.h>

#define POMODORO_TIMEOUT 1
#define REST_TIMEOUT 2
#define POMODORO 3
#define REST 4

typedef uint8_t TimeoutType;
typedef uint8_t TurnType;

struct TimeoutStatus {
    bool timeout;
    TimeoutType type;
};

struct PomodoroState {
    bool hasStarted;
    TurnType turn;
    bool paused;
    struct TimeoutStatus timeoutStatus;
};

struct TimeStruct getRestTime();
struct TimeStruct getPomodoroTime();
struct PomodoroState getPomodoroState();
void togglePauseState();
void incrementIntervalsCount();
void setTimeout(TimeoutType status);
void startTimer();
void restartTimer();
void togglePomodoroTurn();

#endif