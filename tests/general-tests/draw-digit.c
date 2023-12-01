#include <ncurses.h>

#define COLOR 1
#define INVIS 0

typedef int clockPixel;

clockPixel digitShapes[1][5][3] = {
    {
        {COLOR, COLOR, COLOR},
        {COLOR, INVIS, COLOR},
        {COLOR, INVIS, COLOR},
        {COLOR, INVIS, COLOR},
        {COLOR, COLOR, COLOR}
    }
};

int main(void){
    int line = 1;
    initscr();
    cbreak();
    start_color();
    use_default_colors();
    init_pair(1, 0, COLOR_RED);

    
    
    for(size_t i = 0; i < 1; i++){
        for(size_t j = 0; j < 5; j++){
            for(size_t k = 0; k < 3; k++){
                if(digitShapes[i][j][k] == COLOR){
                    attron(COLOR_PAIR(1));
                    printw("  ");
                    attroff(COLOR_PAIR(1));
                }else{
                    printw("  ");
                }
            }
            move(line++, 0);
        }
    }

    // printw("      ");

    // mvprintw(1,0, "  ");
    // mvprintw(1, 4, "  ");
    // mvprintw(2, 0, "  ");
    // mvprintw(2, 4, "  ");
    // mvprintw(3, 0, "  ");
    // mvprintw(3, 4, "  ");
    // mvprintw(4,0, "      ");

    // attroff(COLOR_PAIR(1));

    refresh();

    getch();
    endwin();

    return 0;
}