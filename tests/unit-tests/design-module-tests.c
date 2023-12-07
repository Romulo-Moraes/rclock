#include "./../../include/global-includes.h"
#include "./../../include/arguments.h"
#include "./../../include/shapes.h"
#include "./../../include/screen-manager.h"
#include "./../../include/design.h"
#include "./../../include/errors.h"
#include "./../../include/colors.h"
#include "./../../include/datetime.h"

int main(void){
    initscr();
    cbreak();
    start_color();
    use_default_colors();

    ProgramArguments args = fetchProgramArguments();

    time_t t = time(NULL);

    getTerminalSize();

    generateWindows(args.DatetimeScreenManagerDesigner);
    setPlaceHolders();
    moveWindowsToPlaceholders();

    drawDate(localtime(&t), args.datetime);

    //setDateStringLength(sizeof("salve"));

    //setPlaceHolders();
    refreshWindows();

    refresh();

    getch();

    endwin();


    return 0;
}