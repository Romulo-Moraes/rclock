#include "./../include/screen-manager.h"

struct RclockWindows windows = {0};
struct WindowSize winSize;
struct WindowsPlaceholders windowsPositions;

// Forward declarations
void getTerminalSize(unsigned int *width, unsigned int *height);
bool checkIfTerminalHeightIsCritical(void *arguments);
bool checkIfTerminalWidthIsCritical(void *arguments);
int getLastWhitespaceBeforeOverflow(char *msg, size_t maxColumns);
void writeErrorMessageOnErrorWindow(char *msg, size_t windowWidth, WINDOW *errorWindow);
struct ErrorWindowsMeasures calculateErrorWindowsMeasures(float errorWindowWidthFraction);
void updateErrorMessageFrames(struct ErrorWindows windows, float errorWindowWidthFraction, char *errorMessage, bool (*extraClearErrorParam)(void *arguments), void *extraParamArguments, bool enableExitMessage);

// Public functions

ClockState hideAndShowSecondsIfTerminalsTooSmall(){
    if(winSize.width < 55){
        windows.timeWindowsCount = WINDOWS_COUNT_WITH_HIDDEN_SECONDS;
        
        return SMALL_CLOCK;
    }else{
        windows.timeWindowsCount = WINDOWS_COUNT_WITH_VISIBLE_SECONDS;

        return LARGE_CLOCK;
    }
}

bool showErrorMessageIfTerminalIsExtremelySmall(struct DatetimeScreenManagerDesignerModules userArguments){
    struct ErrorWindows windows;
    char errorBuffer[MAX_ERROR_BUFFER_SZ + 1];
    ErrorID errorID;
    bool (*validationCallback)();
    bool stopFlag = true;
    bool error = false;

    do{
        validationCallback = NULL;

        if(winSize.width < MINIMUM_TERMINAL_WIDTH){
            validationCallback = checkIfTerminalWidthIsCritical;
            errorID = TERMINAL_WIDTH_TOO_SMALL;
        }else if((winSize.height < MINIMUM_TERMINAL_HEIGHT_WITH_DATE && userArguments.hideTheDate == false) || (winSize.height < MINIMUM_TERMINAL_HEIGHT_WITHOUT_DATE && userArguments.hideTheDate == true)){
            validationCallback = checkIfTerminalHeightIsCritical;
            errorID = TERMINAL_HEIGHT_TOO_SMALL;
        }

        if(validationCallback != NULL){
            windows = showProgramError(generateErrorMessage(errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer), 0.75, false);
            updateErrorMessageFrames(windows, 0.75, errorBuffer, validationCallback, (void*) &userArguments , false);

            error = true;
        }else{
            stopFlag = false;
        }        
    }while(stopFlag);

    return error;
}

struct ErrorWindows showProgramError(char *msg, float errorWindowWidthFraction, bool enableExitMessage){
    WINDOW *errorWindow, *exitMessageWindow;
    struct ErrorWindowsMeasures measures;

    getTerminalSize(&winSize.width, &winSize.height);

    measures = calculateErrorWindowsMeasures(errorWindowWidthFraction);
        
    wclear(stdscr);

    refresh();
    errorWindow = newwin(ERROR_MESSAGE_WINDOW_HEIGHT, measures.errorWindowWidth, measures.errorWindowTop, measures.errorWindowLeft);
    if(enableExitMessage){
        exitMessageWindow = newwin(EXIT_MESSAGE_WINDOW_HEIGHT, measures.exitMessageWindowWidth, measures.exitMessageWindowTop, 0);

        mvwprintw(exitMessageWindow, 0, measures.exitMessageWindowWidth / 2 - sizeof(EXIT_MESSAGE) / 2, EXIT_MESSAGE);
        wrefresh(exitMessageWindow);
    }

    writeErrorMessageOnErrorWindow(msg, measures.errorWindowWidth - 2, errorWindow);

    wrefresh(errorWindow);

    refresh();

    return (struct ErrorWindows){.errorWindow = errorWindow, .exitMessageWindow = exitMessageWindow};
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

void loadInitialTerminalSize(){
    getTerminalSize(&winSize.width, &winSize.height);
}

bool detectTerminalResizes(){
    int newHeight, newWidth;

    getmaxyx(stdscr, newHeight, newWidth);

    if(winSize.width != newWidth || winSize.height != newHeight){
        return true;
    }

    return false;
}

WINDOW **getClockSegment(unsigned int windowIndex){
    if(windowIndex <= 7){
        return &windows.timeWindows[windowIndex];
    }else{
        return NULL;
    }
}

void setDateStringLength(size_t newLength){
    windowsPositions.dateWindowPosition.dateStringLength = newLength;
}

WINDOW *getDateWindow(){
    return windows.dateWindow;
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
    getTerminalSize(&winSize.width, &winSize.height);

    int windowsYPosition = winSize.height / 2 - (int)((TIME_WINDOW_HEIGHT / 2));
    int firstWindowXPosition;

    if(windows.timeWindowsCount == WINDOWS_COUNT_WITH_VISIBLE_SECONDS){
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_VISIBLE_SECONDS)) / 2 - 3;
    }else{
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_HIDDEN_SECONDS)) / 2 - 2;
    }

    for(int i = 0; i < windows.timeWindowsCount; i++){
        windowsPositions.timeWindowsPositions[i].y = windowsYPosition;
        windowsPositions.timeWindowsPositions[i].x = firstWindowXPosition;

        firstWindowXPosition += TIME_WINDOW_WIDTH + 1;
    }

    // The X position of the date can't be calculated now, this value
    // depends of the date string length
    windowsPositions.dateWindowPosition.y = windowsYPosition + TIME_WINDOW_HEIGHT;
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

// Private functions

void getTerminalSize(unsigned int *width, unsigned int *height){
    getmaxyx(stdscr, *height, *width);
}

bool checkIfTerminalHeightIsCritical(void *arguments){
    if(((struct DatetimeScreenManagerDesignerModules*)arguments)->hideTheDate == true){
        return winSize.height >= MINIMUM_TERMINAL_HEIGHT_WITHOUT_DATE;  
    }else{
        return winSize.height >= MINIMUM_TERMINAL_HEIGHT_WITH_DATE;
    }
}

bool checkIfTerminalWidthIsCritical(void *arguments){
    return winSize.width >= MINIMUM_TERMINAL_WIDTH;
}

int getLastWhitespaceBeforeOverflow(char *msg, size_t maxColumns){
    size_t stringLenUntilWhitespace = 0;

    for(size_t i = 0; i < maxColumns; i++){
        if(msg[i] == ' ' || msg[i] == '\0'){
            stringLenUntilWhitespace = i;
        }

        if(msg[i] == '\0'){
            break;
        }
    }

    return stringLenUntilWhitespace == 0 ? maxColumns : stringLenUntilWhitespace;
}

void writeErrorMessageOnErrorWindow(char *msg, size_t windowWidth, WINDOW *errorWindow){
    char *lines[ERROR_MESSAGE_WINDOW_HEIGHT];
    unsigned short requiredLines;
    unsigned short lastLineLeftPadding;
    size_t msgLen = strlen(msg);
    size_t i = 0, strLenToWrite, line = 0;

    calculateErrorMessageLinesAndPositions(msg, lines, &requiredLines, &lastLineLeftPadding, windowWidth);

    wclear(errorWindow);
    wrefresh(errorWindow);

    wattron(errorWindow, COLOR_PAIR(ERROR_MESSAGE_RED_ID));    

    while(i < msgLen){
        strLenToWrite = getLastWhitespaceBeforeOverflow(msg, windowWidth);
        mvwaddnstr(errorWindow, line++ + 1, windowWidth / 2 - strLenToWrite / 2, msg, strLenToWrite);

        msg += (strLenToWrite + 1);
        i += strLenToWrite;
    }
    
    wattroff(errorWindow, COLOR_PAIR(ERROR_MESSAGE_RED_ID));

    wrefresh(errorWindow);
    refresh();
}

struct ErrorWindowsMeasures calculateErrorWindowsMeasures(float errorWindowWidthFraction){
    struct ErrorWindowsMeasures measures;

    measures.errorWindowWidth = winSize.width * (errorWindowWidthFraction <= 0 ? 0.5 : errorWindowWidthFraction);
    measures.errorWindowTop = winSize.height / 2 - 2;
    measures.errorWindowLeft = winSize.width * (1 - errorWindowWidthFraction) / 2;
    measures.exitMessageWindowWidth = winSize.width;
    measures.exitMessageWindowTop = winSize.height / 2 + 3;

    return measures;
}

void updateErrorMessageFrames(struct ErrorWindows windows, float errorWindowWidthFraction, char *errorMessage, bool (*extraClearErrorParam)(void *arguments), void *extraParamArguments, bool enableExitMessage){
    struct ErrorWindowsMeasures measures;

    timeout(250);

    while(true){

        if(detectTerminalResizes()){
            wclear(windows.errorWindow);
            wrefresh(windows.errorWindow);
            
            if(enableExitMessage){
                wclear(windows.exitMessageWindow);
                wrefresh(windows.exitMessageWindow);
            }

            refresh();

            getTerminalSize(&winSize.width, &winSize.height);

            measures = calculateErrorWindowsMeasures(errorWindowWidthFraction);

            mvwin(windows.errorWindow, measures.errorWindowTop, measures.errorWindowLeft);
            wresize(windows.errorWindow, 5, measures.errorWindowWidth);

            if(enableExitMessage){
                mvwin(windows.exitMessageWindow, measures.exitMessageWindowTop, 0);
                wresize(windows.exitMessageWindow, 3, measures.exitMessageWindowWidth);
            }

            writeErrorMessageOnErrorWindow(errorMessage, measures.errorWindowWidth - 2, windows.errorWindow);

            wrefresh(windows.errorWindow);
            if(enableExitMessage)
                wrefresh(windows.exitMessageWindow);

            refresh();
        }

        if(extraClearErrorParam(extraParamArguments)){
            delwin(windows.errorWindow);
            if(enableExitMessage)
                delwin(windows.exitMessageWindow);
            break;
        }


        getch();
        /*if(getch() != ERR && (extraClearErrorParam != NULL ? extraClearErrorParam() : true)){
            break;
        }*/
    }
}