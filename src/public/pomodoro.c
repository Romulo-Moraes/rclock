#include <inttypes.h>
#include <private/datetime.h>

static uint8_t rounds = 0;

struct TimeStruct getRestTime(){
    struct TimeStruct restTime;

    if (rounds < 4) {
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