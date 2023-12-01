#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);

    struct tm now_tm = *localtime(&now);

    puts(asctime(&now_tm));

    now_tm.tm_sec += 55;

    mktime(&now_tm);

    puts(asctime(&now_tm));

    struct tm my = {0};

    my.tm_isdst = -1;
    my.tm_hour = 26;
    my.tm_min = 61;
    my.tm_sec = 90;
    my.tm_year = 2004 - 1900;
    my.tm_mon = 23;
    my.tm_mday = 3;

    mktime(&my);

    char buffer[1024] = {0};
    
    strftime(buffer, 1024, "%a %A %b %B %c %d %H %I %j %m %M %p %S %U %w %W %x %X %y %Y %Z", &my);

    puts(buffer);
	
    return 0;
}
