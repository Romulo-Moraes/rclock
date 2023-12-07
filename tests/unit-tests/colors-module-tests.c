#include "./../../include/global-includes.h"
#include "./../../include/arguments.h"
#include "./../../include/shapes.h"
#include "./../../include/screen-manager.h"
#include "./../../include/design.h"
#include "./../../include/errors.h"
#include "./../../include/colors.h"
#include "./../../include/datetime.h"

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