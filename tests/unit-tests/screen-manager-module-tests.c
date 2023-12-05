#include "./../../include/includes.h"

#define DATEE "Monday, 04 Dec 2023"

int main(void){
    initscr();
    cbreak();

    getTerminalSize();
    
    struct WindowSize sz = getWinSz();

    //printw("%d %d", sz.width, sz.height);

    generateWindows((struct  DatetimeScreenManagerDesignerModules){.hideTheDate = false, .hideTheSeconds = false});

    setPlaceHolders();

    struct WindowsPlaceholders pc = getPos();

    for(int i = 0; i < 8; i++){
        //printw("%d %d\n", pc.timeWindowsPositions[i].x, pc.timeWindowsPositions[i].y);
    }


    setDateStringLength(sizeof(DATEE));

    setPlaceHolders();
    moveWindowsToPlaceholders();
    refreshWindows();

    sleep(3);

    issueAnError(MONTH_DAY_OUT_OF_RANGE);

    // while(1){
    //     sleep(1);
    //     if(detectTerminalResizes()){
    //         printw("Hello? \n");
    //         setPlaceHolders();
    //         moveWindowsToPlaceholders();
    //         refreshWindows();
    //     }

    //     refresh();
    // }

    refresh();

    getch();

    endwin();
    
    return 0;
}