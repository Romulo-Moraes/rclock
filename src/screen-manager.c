#include "./../include/screen-manager.h"

struct RclockWindows windows = {0};
struct WindowSize winSize;
struct WindowsPlaceholders windowsPositions;

struct RclockWindows getWins(){
    return windows;
}

struct WindowsPlaceholders getPos(){
    return windowsPositions;
}

struct WindowSize getWinSz(){
    return winSize;
}

void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments){
    windows.timeWindowsCount = userArguments.hideTheSeconds == true ? WINDOWS_COUNT_WITH_HIDDEN_SECONDS : WINDOWS_COUNT_WITH_VISIBLE_SECONDS;

    for(short i = 0; i < windows.timeWindowsCount; i++){
        windows.timeWindows[i] = newwin(TIME_WINDOW_HEIGHT, TIME_WINDOW_WIDTH, 0, 0);
    }

    if(userArguments.hideTheDate != true){
        windows.dateWindow = newwin(0, 0, 0, 0);
    }
}

void setPlaceHolders(){
    getTerminalSize();

    int windowsYPosition = winSize.height / 2 - (int)((TIME_WINDOW_HEIGHT / 2));
    int firstWindowXPosition;

    if(windows.timeWindowsCount == WINDOWS_COUNT_WITH_VISIBLE_SECONDS){
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_VISIBLE_SECONDS)) / 2;
    }else{
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_HIDDEN_SECONDS)) / 2;
    }

    for(int i = 0; i < windows.timeWindowsCount; i++){
        windowsPositions.timeWindowsPositions[i].y = windowsYPosition;
        windowsPositions.timeWindowsPositions[i].x = firstWindowXPosition;

        firstWindowXPosition += TIME_WINDOW_WIDTH;
    }

    // The X position of the date can't be calculated now, this value
    // depends of the date string length
    windowsPositions.dateWindowPosition.y = windowsYPosition + TIME_WINDOW_HEIGHT;
}

void getTerminalSize(){
    getmaxyx(stdscr, winSize.height, winSize.width);
}

bool detectTerminalResizes(){
    int newHeight, newWidth;

    getmaxyx(stdscr, newHeight, newWidth);

    if(winSize.width != newWidth || winSize.height != newHeight){
        return true;
    }

    return false;
}

void moveTimeWindowsToPlaceholders(){
    refresh();

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The box of each time window will be clean on each move")
        for(int i = 0; i < windows.timeWindowsCount; i++){
            wborder(windows.timeWindows[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(windows.timeWindows[i]);
        }
    #endif

    for(int i = 0; i < windows.timeWindowsCount; i++){
        mvwin(windows.timeWindows[i], windowsPositions.timeWindowsPositions[i].y,
                                    windowsPositions.timeWindowsPositions[i].x);
    }

}

void setDateStringLength(size_t newLength){
    windowsPositions.dateWindowPosition.dateStringLength = newLength;
}

void moveWindowsToPlaceholders(){
    moveTimeWindowsToPlaceholders();
    moveDateWindowToPlaceholder();
}

void refreshWindows(){
    for(int i = 0; i < windows.timeWindowsCount; i++){
        #ifdef DEBUG
        #pragma message ("DEBUG MODE ON! The clock digits have borders")
            box(windows.timeWindows[i], 0, 0);
        #endif
        wrefresh(windows.timeWindows[i]);
    }

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The date window has a border")
        box(windows.dateWindow, 0, 0);
    #endif
    wrefresh(windows.dateWindow);    
}

void moveDateWindowToPlaceholder(){
    int dateWindowXPosition = winSize.width / 2 - windowsPositions.dateWindowPosition.dateStringLength / 2;

    refresh();

    #ifdef DEBUG
    #pragma comment ("DEBUG MODE ON! The box of the date window will be clean on each move")
        wborder(windows.dateWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');   
        wrefresh(windows.dateWindow);
    #endif

    wresize(windows.dateWindow, 3, windowsPositions.dateWindowPosition.dateStringLength);
    mvwin(windows.dateWindow, windowsPositions.dateWindowPosition.y, dateWindowXPosition);
}

void showProgramError(char *msg){
    WINDOW *errorWindow, *exitMessageWindow;
    size_t errorWindowWidth = winSize.width * 0.5;

    getTerminalSize();
        
    wclear(stdscr);

    refresh();
    errorWindow = newwin(5, errorWindowWidth, winSize.height / 2 - 2, winSize.width * 0.25);
    exitMessageWindow = newwin(3, winSize.width, winSize.height / 2 + 3, 0);

    mvwprintw(errorWindow, 2, errorWindowWidth / 2 - strlen(msg) / 2, msg);
    mvwprintw(exitMessageWindow, 0, winSize.width / 2 - sizeof(EXIT_MESSAGE) / 2, EXIT_MESSAGE);
    box(errorWindow, 0, 0);

    wrefresh(errorWindow);
    wrefresh(exitMessageWindow);

    refresh();
}

WINDOW *getClockWindow(unsigned int windowIndex){
    if(windowIndex <= 7){
        return windows.timeWindows[windowIndex];
    }else{
        return NULL;
    }
}

WINDOW *getDateWindow(){
    return windows.dateWindow;
}