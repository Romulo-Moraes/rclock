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
    "The given date color doesn't exist",
    "The given color of the digit %d doesn't exist"
};

/*
void issueAnError(char *errorMsg){
    showProgramError(errorMsg);

    getch();

    endwin();
    exit(1);
}
*/

void generateErrorMessage(unsigned int errorID, struct ErrorMessageArguments arguments, char* errorOutput){
    if(errorID == UNKNOWN_SPECIFIC_DIGIT_COLOR){
        sprintf(errorOutput, errorMessages[UNKNOWN_SPECIFIC_DIGIT_COLOR], arguments.unknownSpecificDigitColor);
    }else{
        strcpy(errorOutput, errorMessages[errorID]);
    }
}