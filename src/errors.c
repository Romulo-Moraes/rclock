#include "./../include/errors.h"

char *errorMessages[] = {
    "The custom day was out of range",
    "The custom month was out of range",
    "The custom time format was wrong",
    "The custom date format was wrong",
    "",
    "",
    "The given clock color doesn't exist",
    "The given digits color doesn't exist",
    "The given colons color doesn't exist",
    "The given date color doesn't exist"
};

void issueAnError(unsigned int errorID){
    showProgramError(errorMessages[errorID]);

    getch();

    endwin();
    exit(1);
}