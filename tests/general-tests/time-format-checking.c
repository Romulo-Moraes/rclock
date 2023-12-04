#include <string.h>
#include <stdio.h>

int main(void){
    char *buffer = "10;12;48";
    int a = 0,b = 0,c = 0, d = 0;

    // And checking the string length!!!

    if(strlen(buffer) == 8){
        d = sscanf(buffer, "%d:%d:%d", &a, &b, &c);

        printf("%d %d %d %d\n", a, b, c, d);
    }else{
        puts("Incorrect format!");
    }

    

    return 0;
}