#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);

    struct tm now_tm = *localtime(&now);

    now_tm.tm_mday = 32;
    now_tm.tm_min = 69;

    struct tm test = now_tm;

    time_t aa = mktime(&now_tm);


    printf("%d %d | %d %d\n", now_tm.tm_mday, test.tm_mday, now_tm.tm_min, test.tm_min);
	
    return 0;
}
