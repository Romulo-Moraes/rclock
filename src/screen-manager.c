#include "./../include/screen-manager.h"

struct Windows programWindows;
struct WindowSize winSize;
bool theClocksSecondsIsVisible;
bool theClocksDateIsVisible;

// Forward declarations
void getTerminalSize(unsigned int *width, unsigned int *height);
struct ErrorWindowsMeasures calculateErrorWindowsMeasures(float errorWindowWidthFraction);

// Public functions

void destroyRclockWindows(ProgramArguments arguments){
    for(size_t i = 0; i < programWindows.windowsAttributes.clockWindowsCount; i++){
        delwin(programWindows.clockWindows[i].window);
    }

    if(arguments.DatetimeScreenManagerDesigner.hideTheDate == false){
        delwin(programWindows.dateWindow.window);
    }

    wclear(stdscr);
    refresh();
}   

void setValuesForClockStates(ClockState *widthState, ClockState *heightState){
    if(checkIfTheSecondsShouldBeInvisible() == true){
        *widthState = SMALL_CLOCK;
        theClocksSecondsIsVisible = false;
    }else{
        *widthState = NORMAL_CLOCK;
        theClocksSecondsIsVisible = true;
    }

    if(checkIfTheDateShouldBeInvisible() == true){
        *heightState = SMALL_CLOCK;
        theClocksDateIsVisible = false;
    }else{
        *heightState = NORMAL_CLOCK;
        theClocksDateIsVisible = true;
    }
}

void toggleDatesVisibility(){
    theClocksDateIsVisible ^= 1;
}

void toggleSecondsVisibility(){
    theClocksSecondsIsVisible ^= 1;
}

bool checkIfTheDateShouldBeInvisible(){
    // The default height follows the premise
    // that the date isn't hidden
    return winSize.height < DEFAULT_CLOCK_HEIGHT;
}

bool checkIfTheSecondsShouldBeInvisible(){
    // The default width follows the premise
    // that the seconds isn't hidden
    return winSize.width < DEFAULT_CLOCK_WIDTH;
}

/*
bool showTerminalIsExtremelySmallErrorMessage(struct DatetimeScreenManagerDesignerModules userArguments, struct TerminalSizeError errorStruct){
    struct ErrorWindows windows;
    char errorBuffer[MAX_ERROR_BUFFER_SZ + 1];

    windows = showProgramError(generateErrorMessage(errorStruct.errorID, USELESS_ERROR_MESSAGE_ARGUMENTS, errorBuffer), 0.75, false);

    updateErrorMessageFrames(windows, 0.75, errorBuffer, errorStruct.validationCallback, (void*) &userArguments , false);

    return true;
}
*/

struct ErrorWindows generateErrorWindows(char *msg, float errorWindowWidthFraction, bool enableExitMessage){
    struct ErrorWindows errorWindows;

    getTerminalSize(&winSize.width, &winSize.height);

    errorWindows.measures = calculateErrorWindowsMeasures(errorWindowWidthFraction);

    errorWindows.errorWindow = newwin(ERROR_MESSAGE_WINDOW_HEIGHT, errorWindows.measures.errorWindowWidth, errorWindows.measures.errorWindowTop, errorWindows.measures.errorWindowLeft);
    if(enableExitMessage){
        errorWindows.exitMessageWindow = newwin(EXIT_MESSAGE_WINDOW_HEIGHT, errorWindows.measures.exitMessageWindowWidth, errorWindows.measures.exitMessageWindowTop, 0);
    }

    return errorWindows;
}

void moveTimeWindowsToPlaceholders(){
    size_t windowsLimit = (theClocksSecondsIsVisible == true ? WINDOWS_COUNT_WITH_VISIBLE_SECONDS : WINDOWS_COUNT_WITH_HIDDEN_SECONDS);

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The box of each time window will be clean on each move")
        for(int i = 0; i < windowsLimit; i++){
            wborder(programWindows.clockWindows[i].window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(programWindows.clockWindows[i].window);
        }
    #endif

    for(int i = 0; i < windowsLimit; i++){
        mvwin(programWindows.clockWindows[i].window, programWindows.clockWindows[i].position.y,
                                    programWindows.clockWindows[i].position.x);
    }
}

void moveDateWindowToPlaceholder(){
    int dateWindowXPosition = winSize.width / 2 - programWindows.windowsAttributes.dateStringLength / 2;

    refresh();

    #ifdef DEBUG
    #pragma comment ("DEBUG MODE ON! The box of the date window will be clean on each move")
        wborder(programWindows.dateWindow.window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');   
        wrefresh(programWindows.dateWindow.window);
    #endif

    wresize(programWindows.dateWindow.window, 3, programWindows.windowsAttributes.dateStringLength);
    mvwin(programWindows.dateWindow.window, programWindows.dateWindow.position.y, dateWindowXPosition);
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

WINDOW** getClockSegment(unsigned int windowIndex, WINDOW *output[2]){
    if(windowIndex <= 7){
        output[0] = programWindows.clockWindows[windowIndex].window;
        output[1] = programWindows.clockWindows[windowIndex + 1].window;

        return output;
    }else{
        return NULL;
    }
}

void setDateStringLength(size_t newLength){
    programWindows.windowsAttributes.dateStringLength = newLength;
}

WINDOW *getDateWindow(){
    return programWindows.dateWindow.window;
}

void generateWindows(struct DatetimeScreenManagerDesignerModules userArguments){
    programWindows.windowsAttributes.clockWindowsCount = userArguments.hideTheSeconds == true ? WINDOWS_COUNT_WITH_HIDDEN_SECONDS : WINDOWS_COUNT_WITH_VISIBLE_SECONDS;

    for(short i = 0; i < programWindows.windowsAttributes.clockWindowsCount; i++){
        programWindows.clockWindows[i].window = newwin(TIME_WINDOW_HEIGHT, TIME_WINDOW_WIDTH, 0, 0);
    }

    if(userArguments.hideTheDate != true){
        programWindows.dateWindow.window = newwin(0, 0, 0, 0);
    }
}

void setPlaceHolders(ProgramArguments arguments){
    getTerminalSize(&winSize.width, &winSize.height);
    size_t windowsLimit;

    int windowsYPosition = winSize.height / 2 - (int)((TIME_WINDOW_HEIGHT / 2));
    int firstWindowXPosition;

    if(theClocksSecondsIsVisible == true){
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_VISIBLE_SECONDS)) / 2 - 3;
        windowsLimit = WINDOWS_COUNT_WITH_VISIBLE_SECONDS;
    }else{
        firstWindowXPosition = (winSize.width - (TIME_WINDOW_WIDTH * WINDOWS_COUNT_WITH_HIDDEN_SECONDS)) / 2 - 2;
        windowsLimit = WINDOWS_COUNT_WITH_HIDDEN_SECONDS;
    }

    for(int i = 0; i < windowsLimit; i++){
        programWindows.clockWindows[i].position.y = windowsYPosition;
        programWindows.clockWindows[i].position.x = firstWindowXPosition;

        firstWindowXPosition += TIME_WINDOW_WIDTH + 1;
    }

    if(theClocksDateIsVisible == true && arguments.DatetimeScreenManagerDesigner.hideTheDate == false){
        // The X position of the date can't be calculated now, this value
        // depends of the date string length
        programWindows.dateWindow.position.y = windowsYPosition + TIME_WINDOW_HEIGHT;
    }
    
}

void refreshWindows(){
    size_t windowsLimit = (theClocksSecondsIsVisible == true ? WINDOWS_COUNT_WITH_VISIBLE_SECONDS : WINDOWS_COUNT_WITH_HIDDEN_SECONDS);

    for(int i = 0; i < windowsLimit; i++){
        #ifdef DEBUG
        #pragma message ("DEBUG MODE ON! The clock digits have borders")
            box(programWindows.clockWindows[i].window, 0, 0);
        #endif
        wrefresh(programWindows.clockWindows[i].window);
    }

    #ifdef DEBUG
    #pragma message ("DEBUG MODE ON! The date window has a border")
        box(programWindows.dateWindow.window, 0, 0);
    #endif

    if(theClocksDateIsVisible == true)
        wrefresh(programWindows.dateWindow.window);

    refresh();
}

bool checkIfTerminalHeightIsCritical(){
    return !(winSize.height >= MINIMUM_TERMINAL_HEIGHT);
}

bool checkIfTerminalWidthIsCritical(){
    return !(winSize.width >= MINIMUM_TERMINAL_WIDTH);
}


// Private functions

void getTerminalSize(unsigned int *width, unsigned int *height){
    getmaxyx(stdscr, *height, *width);
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

void updateErrorMessageFrames(struct ErrorWindows windows, float errorWindowWidthFraction, char *errorMessage, void (*drawProgramErrorCallback)(void *arguments), void *drawErrorArguments, bool (*errorVerificationCallback)(), bool enableExitMessage){
    struct ErrorWindowsMeasures measures;
    bool firstLoop = true;

    timeout(1000);

    while(true){

        if(detectTerminalResizes() || firstLoop == true){
            firstLoop = false;

            getTerminalSize(&winSize.width, &winSize.height);

            measures = calculateErrorWindowsMeasures(errorWindowWidthFraction);

            mvwin(windows.errorWindow, measures.errorWindowTop, measures.errorWindowLeft);
            wresize(windows.errorWindow, 5, measures.errorWindowWidth);

            if(enableExitMessage){
                mvwin(windows.exitMessageWindow, measures.exitMessageWindowTop, 0);
                wresize(windows.exitMessageWindow, 3, measures.exitMessageWindowWidth);
            }

            wrefresh(windows.errorWindow);

            if(enableExitMessage)
                wrefresh(windows.exitMessageWindow);

            refresh();

            // Update the measures for each loop
            ((struct UpdateErrorFramesCallbackArguments*) drawErrorArguments)->windows.measures = measures;

            drawProgramErrorCallback(drawErrorArguments);

            if(!errorVerificationCallback()){
                delwin(windows.errorWindow);
                if(enableExitMessage)
                    delwin(windows.exitMessageWindow);

                break;
            }
        }


        getch();

        /*if(getch() != ERR && (extraClearErrorParam != NULL ? extraClearErrorParam() : true)){
            break;
        }*/
    }
}