#include "./../test-modules/print-digit.h"

int main(void){
    initscr();
    start_color();
    use_default_colors();
    init_pair(1, 0, COLOR_RED);
    raw();

    int line = 0;
    move(line, 0);

/*
    for(size_t i = 5; i < 10; i++){
        printDigit(getClockDigit(i), &line);
        line += 1;
        move(line, 0);
    }
*/

    printDigit(getClockColon(), &line);

    refresh();
    getch();
    endwin();

    return 0;
}