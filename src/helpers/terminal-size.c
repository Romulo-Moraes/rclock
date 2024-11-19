#include <helpers/terminal-size.h>
#include <public/screen-manager.h>

// Function used to generate a terminal size error, it is 
// basically a wrapper that calls two other functions that
// check both width and height. Zero or one error is given by
// a call to this function.
struct TerminalSizeError checkIfTerminalSizeIsCritical(ProgramArguments arguments){
    struct TerminalSizeError errorStruct;

    errorStruct.thereIsAnError = false;

    if(checkIfTerminalWidthIsCritical(NULL) == true){
        errorStruct = (struct TerminalSizeError){.thereIsAnError = true, .errorID = TERMINAL_WIDTH_TOO_SMALL, .validationCallback = checkIfTerminalWidthIsCritical};
    }else if(checkIfTerminalHeightIsCritical(&arguments.DatetimeScreenManagerDesigner) == true){
        errorStruct = (struct TerminalSizeError){.thereIsAnError = true, .errorID = TERMINAL_HEIGHT_TOO_SMALL, .validationCallback = checkIfTerminalHeightIsCritical};
    }

    return errorStruct;
}

// The project's requirements have a item that specifies that
// the clock shall hide the seconds or the date if the 
// terminal dimensions aren't great enough to support them.
// This procedure checks the dimentions and set control variables
void checkIfTheClockShouldBeSmaller(struct DatetimeScreenManagerDesignerModulesArguments arguments){

    // If the seconds is already not being shown
    // this is useless
    if(arguments.hideTheSeconds == false){
        if(checkIfTheSecondsShouldBeInvisible() == true){
            if(checkIfTheSecondsIsVisible() == true){
                toggleSecondsVisibility();
            }
        }else{
            if(checkIfTheSecondsIsVisible() == false){
                toggleSecondsVisibility();
            }
        }
    }

    // If the date is already not being shown
    // this is useless
    if(arguments.hideTheDate == false){
        if(checkIfTheDateShouldBeInvisible() == true){
            if(checkIfTheDateIsVisible() == true){
                toggleDatesVisibility();
            }
        }else{
            if(checkIfTheDateIsVisible() == false){
                toggleDatesVisibility();
            }
        }
    }
}
