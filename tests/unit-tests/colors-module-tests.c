#include "./../../include/includes.h"

int main(void){
    setComponentsColors((struct ColorsModule){.clockColor = "green",
                                               .colonColor = "black",
                                               .dateColor = "white",
                                               .digitColor = {NULL},
                                               .globalDigitsColor = "magenta"});

    for(int i = 0; i < 6; i++){
        printf("%d ", getDigitColor(i));
    }

    puts("");

    printf("%d | %d\n", getColonColor(), getDateColor());

    return 0;
}