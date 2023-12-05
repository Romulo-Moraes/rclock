#include "./../include/errors.h"

char *errorMessages[] = {
    "The custom day was out of range",
    "The custom month was out of range",
    "The custom time format was wrong",
    "The custom date format was wrong"
};

void issueAnError(unsigned int errorID){
    showProgramError(errorMessages[errorID]);

    getch();

    endwin();
    exit(1);
}