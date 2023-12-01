#include "./print-digit.h"

void printDigit(clockPixel (*digitShapes)[3], int *line){
    for(size_t j = 0; j < 5; j++){
        for(size_t k = 0; k < 3; k++){
            if(digitShapes[j][k] == COLOR){
                attron(COLOR_PAIR(1));
                printw("  ");
                attroff(COLOR_PAIR(1));
            }else{
                printw("  ");
            }
        }
        move(*line + 1, 0);
        *line += 1;
    }
}