#include "./../include/datetime.h"

struct tm* generateDateAndTime(){
    time_t currentTime = time(NULL);
    
    struct tm *timeStruct = localtime(&currentTime);

    return timeStruct;
}

void setNewTime(struct tm *timeStruct){
    
}